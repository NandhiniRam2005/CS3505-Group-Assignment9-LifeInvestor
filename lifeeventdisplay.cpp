/*
The source file for LifeEventHandler.

This class represents the view for a life event. It will diplay a life event when requested.
Life events have text information about the event, the amount of money the user's balance should change by, the type of the event
and the image to display when the event happens.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include "lifeeventdisplay.h"
#include "ui_lifeeventdisplay.h"

LifeEventDisplay::LifeEventDisplay(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LifeEventDisplay)
{
    ui->setupUi(this);
}

LifeEventDisplay::~LifeEventDisplay()
{
    delete ui;
}

void LifeEventDisplay::showLifeEvent(LifeEvent lifeEvent) {
    if (lifeEvent.type == "Good") {
        ui->lifeEventPrice->setStyleSheet("QLabel { color: #85bb65; font-weight: bold; font-size: 30px; }");
    } else if (lifeEvent.type == "Neutral") {
        ui->lifeEventPrice->setStyleSheet("QLabel { color: black; font-weight: bold; font-size: 30px; }");
    } else if (lifeEvent.type == "Bad") {
        ui->lifeEventPrice->setStyleSheet("QLabel { color: red; font-weight: bold; font-size: 30px; }");
    }

    if (lifeEvent.price == -75) {
        ui->lifeEventLabel->setText(QString::fromStdString("Covered by insurance"));
    }

    ui->lifeEventPrice->setText(QString::number(lifeEvent.price));
    QPixmap pixmap(QString::fromStdString(lifeEvent.image));

    ui->lifeEventPic->setPixmap(pixmap);
}
