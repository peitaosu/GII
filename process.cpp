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

}
