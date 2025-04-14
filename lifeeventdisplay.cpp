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
