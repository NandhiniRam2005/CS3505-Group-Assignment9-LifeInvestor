#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showQuizData(const std::string &question, const  std::vector<std::string> &choices, const std::string &answer, int reward)
{
    // update quiz.ui's labels/buttons
}
