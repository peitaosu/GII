#include "giimain.h"
#include "ui_giimain.h"
#include <QDebug>
GIIMain::GIIMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GIIMain)
{
    ui->setupUi(this);
    process = new Process();
    thread = new QThread();
    process->moveToThread(thread);
    connect(thread, SIGNAL(started()), process, SLOT(go()));
    connect(process, SIGNAL(finished()), thread, SLOT(quit()));
    connect(process ,SIGNAL(updateDisplayName(QString)), this, SLOT(updateDisplayName(QString)));
    connect(process, SIGNAL(updateProgressBar(int)), this, SLOT(updateProgressBar(int)));
    connect(process, SIGNAL(updateProcessName(QString)), this, SLOT(updateProcessName(QString)));
    this->show();
    thread->start();
}

GIIMain::~GIIMain()
{
    delete ui;
}

void GIIMain::updateDisplayName(QString display_name){
    this->setWindowTitle(display_name);
    ui->display_name->setText(display_name);
}

void GIIMain::updateProgressBar(int progress){
    ui->progress_bar->setValue(progress);
}

void GIIMain::updateProcessName(QString process_name){
    ui->process_message->setText("Processing " + process_name);
}
