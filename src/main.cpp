#include "mainwindow.h"
#include "myglwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_CompressHighFrequencyEvents, false);
    a.setAttribute(Qt::AA_CompressTabletEvents, false);
    MainWindow w;
    w.show();

    return a.exec();
}
