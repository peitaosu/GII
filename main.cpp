
#include "giimain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GIIMain main;
    return a.exec();
}
