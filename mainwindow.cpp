#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainModel* model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(model, &MainModel::newQuizData, this, &MainWindow::showQuizData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// tryna print to mainwindow for now to test
void MainWindow::showQuizData(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward)
{
    ui->labelQuestion->setText(QString::fromStdString(question));

    if (choices.size() >= 4) {
        ui->radioButton->setText(QString::fromStdString(choices[0]));
        ui->radioButton_2->setText(QString::fromStdString(choices[1]));
        ui->radioButton_3->setText(QString::fromStdString(choices[2]));
        ui->radioButton_4->setText(QString::fromStdString(choices[3]));
    }

    ui->labelReward->setText("Reward: " + QString::number(reward));
}
