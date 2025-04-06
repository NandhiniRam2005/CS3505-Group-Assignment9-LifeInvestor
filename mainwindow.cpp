#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"

MainWindow::MainWindow(MainModel* model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->choice1);
    buttonGroup->addButton(ui->choice2);
    buttonGroup->addButton(ui->choice3);
    buttonGroup->addButton(ui->choice4);


    connect(model, &MainModel::sendQuestion, this, &MainWindow::showQuizData);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->startButton, &QPushButton::clicked, model, &MainModel::requestQuiz);
    connect(ui->nextButton, &QPushButton::clicked, model, &MainModel::getNextQuestion);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::submitHelper);
    connect(this, &MainWindow::sendAnswer, model, &MainModel::checkAnswer);
    connect(model, &MainModel::sendResult, this, &MainWindow::displayResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showQuizData(Question question)
{
    ui->resultLabel->setText("");

    if(buttonGroup->checkedButton()){
        buttonGroup->setExclusive(false);  // Temporarily allow no selection so that we can unselect the prev radio button.
        buttonGroup->checkedButton()->setChecked(false);
        buttonGroup->setExclusive(true);
    }

    ui->labelQuestion->setText(QString::fromStdString(question.text));

    ui->choice1->setText(QString::fromStdString(question.choices[0]));
    ui->choice2->setText(QString::fromStdString(question.choices[1]));
    ui->choice3->setText(QString::fromStdString(question.choices[2]));
    ui->choice4->setText(QString::fromStdString(question.choices[3]));

    ui->labelReward->setText("Reward: " + QString::number(question.reward));
}

void MainWindow::onStartClicked() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::submitHelper(){
    QAbstractButton* selected = buttonGroup->checkedButton();
    std::string selectedText = (selected->text()).toStdString();
    emit sendAnswer(selectedText);
}

void MainWindow::displayResult(bool result){
    if(result){
        ui->resultLabel->setText("CORRECT!!");
    }
    else{
        ui->resultLabel->setText("Incorrect!!!");
    }
}
