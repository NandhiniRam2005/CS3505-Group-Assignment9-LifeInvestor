#include <QApplication>
#include "mainmodel.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainModel m;
    MainWindow w;
    w.show();
    return a.exec();
}
