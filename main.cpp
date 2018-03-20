
#include "process.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Process process;
    process.init();
    process.start();
    return a.exec();
}
