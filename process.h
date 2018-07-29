// MIT License
// 
// Copyright (c) 2018 Tony Su
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
