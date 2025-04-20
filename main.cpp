/*
The main application for Life Investor.

This file initializes the Qt application, sets up styling and theme, and launches
the main window tied to the application model.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include <QApplication>
#include "mainmodel.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Life Investor");

    // Set palette and default font
    QPalette palette;
    QApplication::setStyle("Fusion");
    QApplication::setFont(QFont("Segoe UI", 11));

    // Set custom colors
    palette.setColor(QPalette::Window, QColor(43, 106, 116));
    palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
    palette.setColor(QPalette::Button, QColor(220, 156, 0));
    palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    palette.setColor(QPalette::Disabled, QPalette::Button, QColor(165, 139, 77));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(70, 70, 70));

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
