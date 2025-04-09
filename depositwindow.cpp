#include "depositwindow.h"
#include "ui_depositwindow.h"
#include <QMessageBox>

DepositWindow::DepositWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DepositWindow)
{
    ui->setupUi(this);
    currentCdNumber = 0;

    connect(ui->pushButton, &QPushButton::clicked, this, &DepositWindow::handleOkButton);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &DepositWindow::handleCancelButton);
}

DepositWindow::~DepositWindow()
{
    delete ui;
}

void DepositWindow::handleOkButton() {
    QString input = ui->plainTextEdit->toPlainText().trimmed();
    bool ok;
    double amount = input.toDouble(&ok);

    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid positive number.");
        return;
    }

    emit depositRequested(amount, currentCdNumber);
    this->hide();
}

void DepositWindow::handleCancelButton() {
    this->hide();
}
