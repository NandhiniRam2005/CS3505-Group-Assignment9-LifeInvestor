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
    ui->lifeEventLabel->setText(QString::fromStdString(lifeEvent.text) + QString::number(lifeEvent.price));
}
