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

    stocks.push_back(Stock(20, 0.5, 1.2));
    stocks.push_back(Stock(100, 0.1, 1.1));
    stocks.push_back(Stock(500, 0.3, 0.9));

}

void MainModel::requestQuiz()
{
    this->quizHandler->createQuiz(QuizCategory::example, 2);
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
    if (amount <= currentMoney && savingsAccount->deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    }
    else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::depositToCD(double amount, int cdNumber) {
    if (amount <= currentMoney && cdAccounts[cdNumber].deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateCD(cdNumber, cdAccounts[cdNumber].getBalance(), cdAccounts[cdNumber].getInterestRate(), cdAccounts[cdNumber].getTermLength(), cdAccounts[cdNumber].getMinimumDeposit(), cdAccounts[cdNumber].getYearsRemaining());
    }
    else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::buyStock(int numberOfShares, int stockNumber) {
    double amount = numberOfShares * stocks[stockNumber].getValue();
    if (amount <= currentMoney && stocks[stockNumber].deposit(numberOfShares)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateStock(stockNumber, stocks[stockNumber].getMoneyBalance());
    }
    else
        emit showErrorMessage("Input amount cannot be bought");
}

void MainModel::sendPriceOfXStocks(int numberOfShares, int stockNumber){
    double amount = numberOfShares * stocks[stockNumber].getValue();
    emit sendPriceOfStocks(amount, stockNumber);
}

void MainModel::sendSellingPriceOfXStocks(int numberOfShares, int stockNumber){
    double amount = numberOfShares * stocks[stockNumber].getValue();
    bool tooMany = numberOfShares > stocks[stockNumber].getBalance();
    emit sendSellingPriceOfStocks(amount, stockNumber, tooMany);
}

void MainModel::depositToLoan(double amount, int loanNumber) {
    if (amount <= currentMoney && loans[loanNumber].deposit(amount)) {
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

void MainModel::withdrawFromCD(int cdNumber) {
    double amount = cdAccounts[cdNumber].getBalance();

    if(cdAccounts[cdNumber].withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateCD(cdNumber, cdAccounts[cdNumber].getBalance(), cdAccounts[cdNumber].getInterestRate(), cdAccounts[cdNumber].getTermLength(), cdAccounts[cdNumber].getMinimumDeposit(), cdAccounts[cdNumber].getYearsRemaining());
    } else {
        emit showErrorMessage("Cannot withdraw from CD - still in term period");
    }
}

void MainModel::updateCDInformation(int cdNumber) {
    emit updateCD(cdNumber, cdAccounts[cdNumber].getBalance(), cdAccounts[cdNumber].getInterestRate(), cdAccounts[cdNumber].getTermLength(), cdAccounts[cdNumber].getMinimumDeposit(), cdAccounts[cdNumber].getYearsRemaining());
}

void MainModel::sellStock(int numberOfShares, int stockNumber) {
    double amount = numberOfShares * stocks[stockNumber].getValue();
    if (stocks[stockNumber].withdraw(numberOfShares)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateStock(stockNumber, stocks[stockNumber].getMoneyBalance());
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
    emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    for (int i = 0; i < cdAccounts.count(); i++) {
        cdAccounts[i].nextYear();
        emit updateCD(i, cdAccounts[i].getBalance(), cdAccounts[i].getInterestRate(), cdAccounts[i].getTermLength(), cdAccounts[i].getMinimumDeposit(), cdAccounts[i].getYearsRemaining());
    }
    for (int i = 0; i < stocks.count(); i++) {
        stocks[i].nextYear();
        emit updateStock(i, stocks[i].getMoneyBalance());
    }
    for (int i = 0; i < loans.count(); i++) {
        loans[i].nextYear();
        loans[i].setAvailable(creditScore);
        if (loans[i].getYearsLeft() < 0)
            endGame();
        emit updateLoan(i, loans[i].getBalance(), loans[i].getInterestRate(), loans[i].getAvailable(), loans[i].getYearsLeft());
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
