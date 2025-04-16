#include <QApplication>
#include "mainmodel.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Life Investor");

    // Create a custom palette
    QPalette palette;

    QApplication::setStyle("Fusion");

    QApplication::setFont(QFont("Segoe UI", 11)); // Set default font

    // Set custom colors (you can customize these)
    palette.setColor(QPalette::Window, QColor(43, 106, 116));  // Greenish background
    palette.setColor(QPalette::WindowText, QColor(255, 255, 255));    // White text

    palette.setColor(QPalette::Button, QColor(220, 156, 0));  // Yellow button background
    palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));    // Black button text
    palette.setColor(QPalette::Disabled, QPalette::Button, QColor(165, 139, 77)); // Lighter button disabled background
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(70, 70, 70));    // Lighter button disabled baground

    // Apply the palette to the application
    a.setPalette(palette);

    qRegisterMetaType<Question>("Question");
    qRegisterMetaType<QuizInfo>("QuizInfo");

    MainModel model;
    MainWindow window(&model);
    QIcon icon(":///icons/icons/lifeInvestIcon.png");
    a.setWindowIcon(icon);
    window.setWindowTitle("Life Investor");
    window.show();
    return a.exec();
}
