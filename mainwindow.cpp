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
    ui->balance->hide();

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
    connect(ui->continueButton, &QPushButton::clicked, this, [this] () {ui->stackedWidget->setCurrentWidget(ui->mainGame); ui->balance->show();});
    connect(ui->App1, &QPushButton::clicked, this, [this] () {ui->stackedWidget->setCurrentWidget(ui->Stocks);});
    connect(ui->stocksBackButton, &QPushButton::clicked, this, [this] () {ui->stackedWidget->setCurrentWidget(ui->mainGame);});
    connect(model, &MainModel::returnToGame, this, &MainWindow::returnToGame);
    connect(this, &MainWindow::settingsOpened, model, &MainModel::settingsOpened);
    connect(ui->settingsButton, &QPushButton::clicked, this, [this] () {
        ui->settingsButton->hide();
        ui->balance->hide();
        emit settingsOpened(ui->stackedWidget->currentWidget());
        ui->stackedWidget->setCurrentWidget(ui->Settings);
    });
    connect(ui->settingsBackButton, &QPushButton::clicked, model, &MainModel::settingsClosed);

    // phone connections
    connect(ui->openPhoneButton, &QPushButton::clicked, this, &MainWindow::displayPhone);
    connect(ui->closePhoneButton, &QPushButton::clicked, this, &MainWindow::hidePhone);

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
    connect(model, &MainModel::updateBalance, this, &MainWindow::updateBalance);

    // connections for withdrawing
    connect(this, &MainWindow::withdrawFromSavings, model, &MainModel::withdrawFromSavings);
    connect(this, &MainWindow::withdrawFromCD, model, &MainModel::withdrawFromCD);
    connect(this, &MainWindow::withdrawFromLoan, model, &MainModel::withdrawFromLoan);
    connect(this, &MainWindow::sellStock, model, &MainModel::sellStock);

    // connections for updating MainWindow values
    connect(model, &MainModel::updateSavings, this, &MainWindow::updateSavings);
    connect(model, &MainModel::updateCD, this, &MainWindow::updateCD);
    connect(model, &MainModel::updateStock, this, &MainWindow::updateStock);
    connect(model, &MainModel::updateLoan, this, &MainWindow::updateLoan);

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

void MainWindow::displayPhone()
{
    ui->openPhoneButton->hide();
    ui->Phone->show();
    ui->closePhoneButton->show();
    ui->Apps->show();
}

void MainWindow::hidePhone()
{
    ui->Phone->hide();
    ui->closePhoneButton->hide();
    ui->Apps->hide();
    ui->openPhoneButton->show();
}

void MainWindow::returnToGame(QWidget* currentWidget)
{
    QString returnPage = currentWidget->objectName();
    if(returnPage == "Start") {
        ui->stackedWidget->setCurrentWidget(ui->Start);
    } else if(returnPage == "Quiz") {
        ui->stackedWidget->setCurrentWidget(ui->Quiz);
    } else if(returnPage == "quizEnd") {
        ui->stackedWidget->setCurrentWidget(ui->quizEnd);
    } else if(returnPage == "mainGame") {
        ui->stackedWidget->setCurrentWidget(ui->mainGame);
    } else if(returnPage == "Stocks") {
        ui->stackedWidget->setCurrentWidget(ui->Stocks);
    } else {
        throw std::runtime_error("return page could not be found.");
    }
    ui->settingsButton->show();
    if(returnPage != "Start" && returnPage != "quizEnd")
        ui->balance->show();
}

void MainWindow::onStartClicked()
{
    hidePhone();
    ui->balance->show();
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

void MainWindow::displayResult(bool result, std::string explanation)
{
    if (result) {
        ui->resultLabel->setText("<span style='color: green; font-weight: bold;'>CORRECT!!</span>");
        confettiView->startConfettiAnimation();
    } else {
        QString formattedText = "<span style='color: red; font-weight: bold;'>Incorrect!!!</span><br>"
                                "<span style='color: black;'>Explanation: " + QString::fromStdString(explanation) + "</span>";
        ui->resultLabel->setText(formattedText);
        confettiView->startRainAnimation();
    }
}

void MainWindow::updateProgress(uint progress)
{
    ui->quizProgress->setValue(progress);
}

void MainWindow::updateBalance(double newAmount) {
    currentMoney = newAmount;
    ui->balance->setText("$"+QString::number(currentMoney));
}

void MainWindow::updateSavings(double newBalance, double interestRate) {

}

void MainWindow::updateCD(int cdNumber, double newBalance, double interestRate, int termlength, double minimumDeposit, int yearsLeft) {

}

void MainWindow::updateStock(int stockNumber, double newBalance) {

}

void MainWindow::updateLoan(int loanNumber, double newBalance, double interestRate) {

}


void MainWindow::enableSubmitButton(bool checked) {
    if (checked) {
        ui->submitButton->setEnabled(true);
    }
}

void MainWindow::showEndScreen() {
    ui->balance->hide();
    ui->stackedWidget->setCurrentWidget(ui->quizEnd);
    ui->endLabel->setText("Quiz done! yay\n here is the recap (there is no recap)");
}

