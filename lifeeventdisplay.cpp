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
    ui->lifeEventLabel->setText(QString::fromStdString(lifeEvent.text));

    if (lifeEvent.type == "Good") {
        ui->lifeEventPrice->setStyleSheet("QLabel { color: #85bb65; font-weight: bold; font-size: 30px; }");
    } else if (lifeEvent.type == "Neutral") {
        ui->lifeEventPrice->setStyleSheet("QLabel { color: black; font-weight: bold; font-size: 30px; }");
    } else if (lifeEvent.type == "Bad") {
        ui->lifeEventPrice->setStyleSheet("QLabel { color: red; font-weight: bold; font-size: 30px; }");
    }

    ui->lifeEventPrice->setText(QString::number(lifeEvent.price));
    QPixmap pixmap(QString::fromStdString(lifeEvent.image));

    ui->lifeEventPic->setPixmap(pixmap);
}

