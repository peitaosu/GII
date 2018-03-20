#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "giimain.h"

class Process : public QObject
{
        Q_OBJECT
    public:
        explicit Process(QObject *parent = 0);
        int init();
        int start();

    private:
        GIIMain *main_window;
        QJsonObject process_config;

    signals:
        void updateDisplayName(QString);

    public slots:

};

#endif // PROCESS_H
