#include <QApplication>
#include "mainmodel.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Question>("Question");
    MainModel model;
    MainWindow window(&model);
    QIcon icon(":///icons/icons/lifeInvestIcon.png");
    a.setWindowIcon(icon);
    window.show();
    return a.exec();
}
