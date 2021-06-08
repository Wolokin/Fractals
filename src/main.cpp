#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_CompressHighFrequencyEvents, false);
    QApplication::setAttribute(Qt::AA_CompressTabletEvents, false);
    MainWindow w;
    w.show();

    return QApplication::exec();
}
