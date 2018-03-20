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

    private slots:
        void updateDisplayName(QString display_name);

};

#endif // GIIMAIN_H
