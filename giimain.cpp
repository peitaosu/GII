// MIT License
// 
// Copyright (c) 2018-2019 Tony Su
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
