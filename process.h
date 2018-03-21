#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QProcess>
#include <QDebug>

class Process : public QObject
{
        Q_OBJECT
    public:
        explicit Process(QObject *parent = 0);
        void setProcessCount(int count);

    private:
        QProcess *exec_process;
        QJsonObject process_config;
        QThread *thread;

        int process_count = 0;
        int processing = 0;
        int current_finished = 0;

        int exec_msi(QString);
        int exec_bat(QString);
        int exec_ps(QString);
        int exec(QString);

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
