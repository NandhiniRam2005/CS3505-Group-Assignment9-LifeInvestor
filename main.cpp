#include <QApplication>
#include "mainmodel.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create a custom palette
    QPalette palette;

    QApplication::setStyle("Fusion");

    // Set custom colors (you can customize these)
    palette.setColor(QPalette::Window, QColor(0, 0, 0));  // White background
    palette.setColor(QPalette::WindowText, QColor(255, 255, 255));    // Black text

    // Apply the palette to the application
    a.setPalette(palette);

    qRegisterMetaType<Question>("Question");
    qRegisterMetaType<QuizInfo>("QuizInfo");

    MainModel model;
    MainWindow window(&model);
    QIcon icon(":///icons/icons/lifeInvestIcon.png");
    a.setWindowIcon(icon);
    window.show();
    return a.exec();
}
