/// dReam Tables Five Card Draw Poker
#include "mainwindow.h"
#include "menu.h"
#include "QApplication"


QThread Worker::workThread;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer timer;
    Worker worker;

    Menu m;
    m.setModal(true);
    m.exec();

    MainWindow w;
    w.show();

    QObject::connect(&timer, SIGNAL(timeout()), &worker, SLOT(onTimeout()));
    timer.start(6000);
    QObject::connect(&timer, SIGNAL(timeout()), &w, SLOT(refresh()));

    worker.moveToThread(&Worker::workThread);
    Worker::workThread.start();

    return a.exec();
}
