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

    connect(exec_process, SIGNAL(finished(int)), this, SLOT(updateProgress(int)));

}


void Process::go(){
    //emit the display name signal
    emit updateDisplayName(process_config["Display Name"].toString());
    this->process_count = process_config["Actions"].toArray().count();

    QJsonArray process_array = process_config["Actions"].toArray();
    foreach (const QJsonValue & p, process_array){
        emit updateProcessName(p.toObject()["Action"].toString());
    }
    emit finished();
}

int Process::exec_msi(QString msi_command){
    exec_process->start("msiexec.exe " + msi_command);
    return 0;
}

int Process::exec_bat(QString batch_command){
    exec_process->start("cmd.exe /c \"" + batch_command + "\"");
    return 0;
}

int Process::exec_ps(QString powershell_command){
    exec_process->start("PowerShell -Command \"& {" + powershell_command + "}\"");
    return 0;
}

int Process::exec(QString command){
    exec_process->start(command);
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
