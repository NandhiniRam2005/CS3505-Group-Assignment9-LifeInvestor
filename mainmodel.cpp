#include "mainmodel.h"
#include "quizhandler.h"
#include <iostream>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    quizHandler = new QuizHandler(this);

    currentMoney = 0;
    creditScore = 0;
    currentYear = 0;

    savingsAccount = new SavingsAccount(0);

    cdAccount = new CDAccount(0);

    stocks.push_back(Stock());
    stocks.push_back(Stock());
    stocks.push_back(Stock());
}

void MainModel::requestQuiz()
{
    this->quizHandler->parseQuizFile("example");
    getNextQuestion();
}

void MainModel::getNextQuestion()
{
    if (quizHandler->hasMoreQuestions()) {
        emit sendQuestion(quizHandler->getNextQuestion());
    } else {
        emit quizFinished(quizHandler->getQuestionsAnsweredCorrectly());
    }
}

void MainModel::checkAnswer(std::string selectedChoice)
{
    bool result = quizHandler->checkAnswer(selectedChoice);
    std::string why = quizHandler->getCurrentQuestionWhy();
    emit quizProgress(quizHandler->quizProgress());
    emit sendResult(result, why);
}

void MainModel::depositToSavings(double amount) {
    emit updateSavingsBalance(0);
}

void MainModel::depositToCD(double amount) {
    emit updateCDBalance(0);
}

void MainModel::buyStock(double amount, int stockNumber) {
    emit updateStockBalances({});
}

void MainModel::depositToLoan(double amount, int loanNumber) {
    emit updateLoanBalances({});
}

void MainModel::withdrawFromSavings(double amount) {
    emit updateSavingsBalance(0);
}

void MainModel::withdrawFromCD(double amount) {
    emit updateCDBalance(0);
}

void MainModel::sellStock(double amount, int stockNumber) {
    emit updateStockBalances({});
}

void MainModel::withdrawFromLoan(double amount, int loanNumber) {
    emit updateLoanBalances({});
}

void MainModel::nextYear() {

}

void MainModel::settingsOpened(QWidget* currentWidget) {
    this->currentWidget = currentWidget;
}

void MainModel::settingsClosed() {
    emit returnToGame(this->currentWidget);
}
