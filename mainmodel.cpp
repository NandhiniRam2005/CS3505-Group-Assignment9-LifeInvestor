#include "mainmodel.h"
#include "quizhandler.h"
#include <QtCore/qdebug.h>
#include <iostream>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    quizHandler = new QuizHandler(this);

    currentMoney = 0;
    creditScore = 750;
    currentYear = 0;

    savingsAccount = new SavingsAccount(0.0041);

    cdAccounts.push_back(CDAccount(0.041, 2, 1000));
    cdAccounts.push_back(CDAccount(0.039, 3, 500));
    cdAccounts.push_back(CDAccount(0.036, 5, 500));

    loans.push_back(Loan(0.067, 100, 0, 5));
    loans.push_back(Loan(0.067, 1000, 600, 5));

    stocks.push_back(Stock(20, 0.5, 0.2));
    stocks.push_back(Stock(100, 0.1, 0.1));
    stocks.push_back(Stock(500, 0.3, -0.1));
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
    emit quizProgress(quizHandler->quizProgress());
    emit sendResult(result, why);
    if(result) {
        addFunds(quizHandler->getCurrentQuestionReward());
        emit updateBalance(currentMoney);
    }
}

void MainModel::depositToSavings(double amount) {
    if (savingsAccount->deposit(amount) && amount <= currentMoney) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    }
    else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::depositToCD(double amount, int cdNumber) {
    if (cdAccounts[cdNumber].deposit(amount) && amount <= currentMoney) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateCD(cdNumber, cdAccounts[cdNumber].getBalance(), cdAccounts[cdNumber].getInterestRate(), cdAccounts[cdNumber].getTermLength(), cdAccounts[cdNumber].getMinimumDeposit(), cdAccounts[cdNumber].getYearsRemaining());
    }
    else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::buyStock(int numberOfShares, int stockNumber) {
    double amount = numberOfShares * stocks[stockNumber].getValue();
    if (stocks[stockNumber].deposit(amount) && amount <= currentMoney) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateStock(stockNumber, stocks[stockNumber].getBalance());
    }
    else
        emit showErrorMessage("Input amount cannot be bought");
}

void MainModel::sendPriceOfXStocks(int numberOfShares, int stockNumber){
    double stockValue = stocks[stockNumber].getValue();
    qDebug() << stockValue;
    double amount = numberOfShares * stocks[stockNumber].getValue();
    emit sendPriceOfStocks(amount, stockNumber);
}

void MainModel::depositToLoan(double amount, int loanNumber) {
    if (loans[loanNumber].deposit(amount) && amount <= currentMoney) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateLoan(loanNumber, loans[loanNumber].getBalance(), loans[loanNumber].getInterestRate(), loans[loanNumber].getAvailable(), loans[loanNumber].getYearsLeft());
    }
    else
        emit showErrorMessage("Input amount cannot be removed from the loan");
}

void MainModel::withdrawFromSavings(double amount) {
    if (savingsAccount->withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    }
    else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::withdrawFromCD(double amount, int cdNumber) {
    if (cdAccounts[cdNumber].withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateCD(cdNumber, cdAccounts[cdNumber].getBalance(), cdAccounts[cdNumber].getInterestRate(), cdAccounts[cdNumber].getTermLength(), cdAccounts[cdNumber].getMinimumDeposit(), cdAccounts[cdNumber].getYearsRemaining());
    }
    else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::sellStock(int numberOfShares, int stockNumber) {
    double amount = numberOfShares * stocks[stockNumber].getValue();
    if (stocks[stockNumber].withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateStock(stockNumber, stocks[stockNumber].getBalance());
    }
    else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::activateLoan(int loanNumber) {
    if (loans[loanNumber].activate()) {
        currentMoney += -loans[loanNumber].getBalance();
        emit updateBalance(currentMoney);
        emit updateLoan(loanNumber, loans[loanNumber].getBalance(), loans[loanNumber].getInterestRate(), loans[loanNumber].getAvailable(), loans[loanNumber].getYearsLeft());
    }
    else
        emit showErrorMessage("The loan cannot be activated");
}

void MainModel::nextYear() {
    savingsAccount->nextYear();
    for (MoneyContainer container : cdAccounts)
        container.nextYear();
    for (MoneyContainer container : stocks)
        container.nextYear();
    for (Loan loan : loans) {
        loan.nextYear();
        loan.setAvailable(creditScore);
        if (loan.getYearsLeft() < 0)
            endGame();
    }
}

void MainModel::settingsOpened(QWidget* currentWidget) {
    this->currentWidget = currentWidget;
}

void MainModel::settingsClosed() {
    emit returnToGame(this->currentWidget);
}

void MainModel::addFunds(double amount) {
    currentMoney += amount;
    emit updateBalance(currentMoney);
}

void MainModel ::endGame() {

}
