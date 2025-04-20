/*
The source file for WarningDisplay.

This class represents a pop-up warning dialog that displays
a warning message to the user.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include "warningdisplay.h"
#include "ui_warningdisplay.h"

warningdisplay::warningdisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::warningdisplay)
{
    ui->setupUi(this);
}

warningdisplay::~warningdisplay()
{
    delete ui;
}

void warningdisplay::showWarning(QString warning, QString image){
    ui->warning->setText(warning);
    QPixmap pixmap(":///icons/icons/" + image);
    ui->imageWarning->setPixmap(pixmap);
}
