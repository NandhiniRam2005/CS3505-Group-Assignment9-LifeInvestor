#include "mainwindow.h"
#include "iostream"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MainModel *model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->Start);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->choice1);
    buttonGroup->addButton(ui->choice2);
    buttonGroup->addButton(ui->choice3);
    buttonGroup->addButton(ui->choice4);

    confettiView = new ConfettiView(this);
    confettiView->hide();

    // connections for buttons to enable submitting
    connect(ui->choice1, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice2, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice3, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);
    connect(ui->choice4, &QRadioButton::toggled, this, &MainWindow::enableSubmitButton);

    connect(model, &MainModel::sendQuestion, this, &MainWindow::showQuizData);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->startButton, &QPushButton::clicked, model, &MainModel::requestQuiz);
    connect(ui->nextButton, &QPushButton::clicked, model, &MainModel::getNextQuestion);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::submitHelper);
    connect(this, &MainWindow::sendAnswer, model, &MainModel::checkAnswer);
    connect(model, &MainModel::sendResult, this, &MainWindow::displayResult);
    connect(model, &MainModel::quizProgress, this, &MainWindow::updateProgress);

    connect(model, &MainModel::quizFinished, this, &MainWindow::showEndScreen);

    // connection for nextYear
    connect(this, &MainWindow::nextYear, model, &MainModel::nextYear);

    // connections for depositing
    connect(this, &MainWindow::depositToSavings, model, &MainModel::depositToSavings);
    connect(this, &MainWindow::depositToCD, model, &MainModel::depositToCD);
    connect(this, &MainWindow::depositToLoan, model, &MainModel::depositToLoan);
    connect(this, &MainWindow::buyStock, model, &MainModel::buyStock);

    // connections for withdrawing
    connect(this, &MainWindow::withdrawFromSavings, model, &MainModel::withdrawFromSavings);
    connect(this, &MainWindow::withdrawFromCD, model, &MainModel::withdrawFromCD);
    connect(this, &MainWindow::withdrawFromLoan, model, &MainModel::withdrawFromLoan);
    connect(this, &MainWindow::sellStock, model, &MainModel::sellStock);

    // connections for updating MainWindow values
    connect(model, &MainModel::updateSavingsBalance, this, &MainWindow::updateSavingsBalance);
    connect(model, &MainModel::updateCDBalance, this, &MainWindow::updateCDBalance);
    connect(model, &MainModel::updateStockBalances, this, &MainWindow::updateStockBalances);
    connect(model, &MainModel::updateLoanBalances, this, &MainWindow::updateLoanBalances);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showQuizData(Question question)
{
    ui->resultLabel->setText("");

    ui->choice1->setEnabled(true);
    ui->choice2->setEnabled(true);
    ui->choice3->setEnabled(true);
    ui->choice4->setEnabled(true);

    if (buttonGroup->checkedButton()) {
        buttonGroup->setExclusive(
            false); // Temporarily allow no selection so that we can unselect the prev radio button.
        buttonGroup->checkedButton()->setChecked(false);
        buttonGroup->setExclusive(true);
    }

    ui->submitButton->setEnabled(false);
    ui->nextButton->setEnabled(false);

    ui->labelQuestion->setText(QString::fromStdString(question.text));

    ui->choice1->setText(QString::fromStdString(question.choices[0]));
    ui->choice2->setText(QString::fromStdString(question.choices[1]));
    ui->choice3->setText(QString::fromStdString(question.choices[2]));
    ui->choice4->setText(QString::fromStdString(question.choices[3]));

    ui->labelReward->setText("Reward: " + QString::number(question.reward));
}

void MainWindow::onStartClicked()
{
     ui->stackedWidget->setCurrentWidget(ui->Quiz);
}

void MainWindow::submitHelper()
{
    QAbstractButton *selected = buttonGroup->checkedButton();
    std::string selectedText = (selected->text()).toStdString();
    emit sendAnswer(selectedText);

    ui->choice1->setEnabled(false);
    ui->choice2->setEnabled(false);
    ui->choice3->setEnabled(false);
    ui->choice4->setEnabled(false);

    ui->submitButton->setEnabled(false);
    ui->nextButton->setEnabled(true);
}

void MainWindow::displayResult(bool result)
{
    if (result) {
        ui->resultLabel->setText("CORRECT!!");
        confettiView->startAnimation();
    } else {
        ui->resultLabel->setText("Incorrect!!!");
    }
}

void MainWindow::updateProgress(uint progress)
{
    ui->quizProgress->setValue(progress);
}

void MainWindow::updateCurrentMoney(double newAmount) {
    currentMoney = newAmount;
}

void MainWindow::updateSavingsBalance(double newBalance) {
    savingsBalance = newBalance;
}

void MainWindow::updateCDBalance(double newBalance) {
    cdBalance = newBalance;
}

void MainWindow::updateStockBalances(QVector<double> newBalances) {
    stockBalances = newBalances;
}

void MainWindow::updateLoanBalances(QVector<double> newBalances) {
    loanBalances = newBalances;
}

void MainWindow::enableSubmitButton(bool checked) {
    if (checked) {
        ui->submitButton->setEnabled(true);
    }
}

void MainWindow::showEndScreen() {
    ui->stackedWidget->setCurrentWidget(ui->quizEnd);
    ui->endLabel->setText("Quiz done! yay");
}

