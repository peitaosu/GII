#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QRegExp>
#include <QDebug>

#ifdef Q_OS_WIN32
#include <Windows.h>
#pragma comment(lib, "Advapi32.lib")
#endif

class Process : public QObject
{
        Q_OBJECT
    public:
        explicit Process(QObject *parent = 0);
        void setProcessCount(int count);
        bool isSilent();

    private:
        QProcess *exec_process;
        QJsonObject process_config;
        QThread *thread;

        int process_count = 0;
        int processing = 0;
        int current_finished = 0;

        int exec(QString);
        int copy(QString, QString);
        int del(QString);
        #ifdef Q_OS_WIN32
        int reg(QString, QString, QString, QString, QString, QString);
        #endif

        bool silent = false;

        QString expandEnvironmentVariables(QString);

    signals:
        void start();
        void finished();
        void updateDisplayName(QString);
        void updateProgressBar(int);
        void updateProcessName(QString);

    public slots:
        void go();
        void updateProgress(int);

};

#endif // PROCESS_H
