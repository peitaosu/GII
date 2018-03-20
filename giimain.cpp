#include "giimain.h"
#include "ui_giimain.h"

GIIMain::GIIMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GIIMain)
{
    ui->setupUi(this);
}

GIIMain::~GIIMain()
{
    delete ui;
}

void GIIMain::updateDisplayName(QString display_name){
    this->setWindowTitle(display_name);
    ui->display_name->setText(display_name);
}
