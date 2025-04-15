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
