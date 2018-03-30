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
            result = exec(expandEnvironmentVariables(p.toObject()["Command"].toString()));
        }else if(process_type == "Copy"){
            result = copy(expandEnvironmentVariables(p.toObject()["Source"].toString()), expandEnvironmentVariables(p.toObject()["Destination"].toString()));
        }else if(process_type == "Delete"){
            result = del(expandEnvironmentVariables(p.toObject()["Path"].toString()));
        }
        #ifdef Q_OS_WIN32
        if(process_type == "Registry"){
            result = reg(p.toObject()["Func"].toString(), p.toObject()["Root"].toString(), p.toObject()["Key"].toString(), p.toObject()["Name"].toString(), p.toObject()["Type"].toString(), p.toObject()["Value"].toString());
        }
        #endif
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

#ifdef Q_OS_WIN32
int Process::reg(QString func, QString rootKey, QString key, QString name, QString type, QString value){
    HKEY hRootKey;
    HKEY hKey;
    if(rootKey == "HKLM"){
        hRootKey = HKEY_LOCAL_MACHINE;
    }else if(rootKey == "HKCU"){
        hRootKey = HKEY_CURRENT_USER;
    }else if(rootKey == "HKCR"){
        hRootKey = HKEY_CLASSES_ROOT;
    }
    LPCWSTR strKey = (const wchar_t*) key.utf16();
    RegOpenKeyEx(hRootKey, strKey, NULL, KEY_ALL_ACCESS, &hKey);
    if(func == "Set"){
        if(type == "SZ"){
            RegSetValueEx(hKey, (const wchar_t*)name.utf16(), 0, REG_SZ, (BYTE*)(const wchar_t*)value.utf16(), ((DWORD)wcslen((const wchar_t*)value.utf16()) + 1)*sizeof(wchar_t));
        }
        RegCloseKey(hKey);
    }else if(func == "Delete"){
        RegDeleteValue(hKey, (const wchar_t*)name.utf16());
        RegCloseKey(hKey);
    }
    return 0;
}
#endif

void Process::setProcessCount(int count){
    this->process_count = count;
}

void Process::updateProgress(int){
    this->current_finished += 1;
    float progress = (float)this->current_finished / (float)this->process_count;
    int progress_value = (int)(progress * 100);
    emit updateProgressBar(progress_value);
}

QString Process::expandEnvironmentVariables( QString original )
{
    QString str(original);
    QRegExp env_var("\\$\\(env\\.([A-Za-z0-9_]+)\\)");
    int iter;

    while((iter = env_var.indexIn(str)) != -1) {
        QByteArray value(qgetenv(env_var.cap(1).toLatin1().data()));
        if(value.size() > 0) {
            str.remove(iter, env_var.matchedLength());
            str.insert(iter, value);
        } else
            break;
    }
    return str;
}
