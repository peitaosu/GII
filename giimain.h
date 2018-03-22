#ifndef GIIMAIN_H
#define GIIMAIN_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include "process.h"

namespace Ui {
    class GIIMain;
}

class GIIMain : public QMainWindow
{
        Q_OBJECT

    public:
        explicit GIIMain(QWidget *parent = 0);
        ~GIIMain();

    private:
        Ui::GIIMain *ui;
        Process *process;
        QThread *thread;

    private slots:
        void updateDisplayName(QString display_name);
        void updateProgressBar(int progress);
        void updateProcessName(QString process_name);
        void quit();

};

#endif // GIIMAIN_H
