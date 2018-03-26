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

    //move the process to another thread then it won't block the UI
    process->moveToThread(thread);

    //call go() while thread start
    connect(thread, SIGNAL(started()), process, SLOT(go()));

    //process finished() will make the thread quit
    connect(process, SIGNAL(finished()), thread, SLOT(quit()));

    //update UI
    connect(process ,SIGNAL(updateDisplayName(QString)), this, SLOT(updateDisplayName(QString)));
    connect(process, SIGNAL(updateProgressBar(int)), this, SLOT(updateProgressBar(int)));
    connect(process, SIGNAL(updateProcessName(QString)), this, SLOT(updateProcessName(QString)));
    
    //silent mode
    if(!process->isSilent()){
        this->show();
    }else{
        connect(process, SIGNAL(finished()), this, SLOT(quit()));
    }

    //start the process thread
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

void GIIMain::quit(){
    QApplication::quit();
}
