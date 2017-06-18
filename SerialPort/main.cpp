#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    SerialPort port;
    QThread Portthread;
    port.moveToThread(&Portthread);

    w.show();

    return a.exec();
}
