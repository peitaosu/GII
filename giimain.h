#ifndef GIIMAIN_H
#define GIIMAIN_H

#include <QMainWindow>

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
};

#endif // GIIMAIN_H
