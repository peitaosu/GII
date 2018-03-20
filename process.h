#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class Process : public QObject
{
        Q_OBJECT
    public:
        explicit Process(QObject *parent = 0);

    private:
        QJsonObject process_config;

    signals:

    public slots:
};

#endif // PROCESS_H