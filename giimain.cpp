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
