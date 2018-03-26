#include "process.h"

Process::Process(QObject *parent) : QObject(parent)
{
    //load the process.json
    QString process_string;
    QFile process_file;
    process_file.setFileName("process.json");
    //set QIODevice RO and read as text
    process_file.open(QIODevice::ReadOnly | QIODevice::Text);
    process_string = process_file.readAll();
    process_file.close();
    //convert file to variant map
    QJsonDocument process_json = QJsonDocument::fromJson(process_string.toUtf8());
    process_config = process_json.object();

    exec_process = new QProcess(this);

    //connect(exec_process, SIGNAL(finished(int)), this, SLOT(updateProgress(int)));

    //get the silent mode config
    if(process_config.contains("Silent") && process_config["Silent"].toString().toLower() == "yes"){
        this->silent = true;
    }

}

bool Process::isSilent(){
    return this->silent;
}

void Process::go(){
    //emit the display name signal
    emit updateDisplayName(process_config["Display Name"].toString());
    this->process_count = process_config["Actions"].toArray().count();

    // foreach action, call function related to action type
    QJsonArray process_array = process_config["Actions"].toArray();
    foreach (const QJsonValue & p, process_array){
        //update the process name
        emit updateProcessName(p.toObject()["Action"].toString());
        QString process_type = p.toObject()["Type"].toString();
        int result = -1;
        if(process_type == "Command"){
            result = exec(p.toObject()["Command"].toString());
        }else if(process_type == "Copy"){
            result = copy(p.toObject()["Source"].toString(), p.toObject()["Destination"].toString());
        }else if(process_type == "Delete"){
            result = del(p.toObject()["Path"].toString());
        }
        //update the progress
        this->updateProgress(result);
    }
    emit finished();
}


int Process::exec(QString command){
    exec_process->start(command);
    exec_process->waitForFinished();
    return 0;
}


int Process::copy(QString source, QString destination){
    QFileInfo src_info(source);
    if (src_info.isDir()) {
        QDir dest_dir(destination);
        if (!dest_dir.exists()){
            dest_dir.cdUp();
            if (!dest_dir.mkdir(QFileInfo(destination).fileName()))
                return -1;
        }
        QDir source_dir(source);
        QStringList file_names = source_dir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        foreach (const QString &file_name, file_names) {
            QString new_source = source + QLatin1Char('/') + file_name;
            QString new_destination = destination + QLatin1Char('/') + file_name;
            if (copy(new_source, new_destination) != 0)
                return -1;
        }
    } else {
        if (!QFile::copy(source, destination))
            return -1;
    }
    return 0;
}

int Process::del(QString path){
    QFileInfo path_info(path);
    if (path_info.isDir()){
        QDir path_dir(path);
        if (!path_dir.removeRecursively())
            return -1;
    } else {
        QFile path_file(path);
        if (!path_file.remove())
            return -1;
    }
    return 0;
}

void Process::setProcessCount(int count){
    this->process_count = count;
}

void Process::updateProgress(int){
    this->current_finished += 1;
    float progress = (float)this->current_finished / (float)this->process_count;
    int progress_value = (int)(progress * 100);
    emit updateProgressBar(progress_value);
}
