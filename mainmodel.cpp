#include "mainmodel.h"
#include <QtCore/qdebug.h>
#include "quizhandler.h"
#include <iostream>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
    quizHandler = new QuizHandler(this);

    currentMoney = 0;
    creditScore = 650;
    currentYear = 1;

    savingsAccount = new SavingsAccount(0.004);

    checkingAccount = new MoneyContainer();

    cdAccounts.push_back(CDAccount(0.035, 2, 500));
    cdAccounts.push_back(CDAccount(0.040, 4, 750));
    cdAccounts.push_back(CDAccount(0.045, 5, 1000));

    loans.push_back(Loan(0.36, 10000, 0, 5));
    loans.push_back(Loan(0.067, 10000, 650, 7));
    loans[0].setAvailable(creditScore);
    loans[1].setAvailable(creditScore);

    stocks.push_back(Stock(70.76, 0.33, 1.20)); // E-Cola
    stocks.push_back(Stock(190.42, 0.40, 1.29)); // Pear
    stocks.push_back(Stock(27.18, 0.65, 1.08)); // CineKarl

}

void MainModel::quizRequested(QuizCategory category, uint length)
{
    this->quizHandler->createQuiz(category, length);
    getNextQuestion();
    getQuizInfo();
}

void MainModel::getNextQuestion()
{
    if (quizHandler->hasMoreQuestions()) {
        emit sendQuestion(quizHandler->getNextQuestion());
    } else {
        emit quizFinished(quizHandler->getQuestionsAnsweredCorrectly());
    }
}

void MainModel::getQuizInfo(){
    emit sendQuizInfo(quizHandler->getQuizInfo());
}

void MainModel::checkAnswer(std::string selectedChoice)
{
    bool result = quizHandler->checkAnswer(selectedChoice);
    std::string why = quizHandler->getCurrentQuestionWhy();
    emit quizProgress(quizHandler->quizProgress());
    emit quizProgress(quizHandler->quizProgress());
    emit sendResult(result, why);
    if (result) {
        addFunds(quizHandler->getCurrentQuestionReward());
        emit updateBalance(currentMoney);
    }
}

void MainModel::depositToSavings(double amount)
{
    if (amount <= currentMoney && savingsAccount->deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    } else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::depositToChecking(double amount)
{
    if (amount <= currentMoney && checkingAccount->deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateChecking(checkingAccount->getBalance());
    } else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::depositToCD(double amount, int cdNumber)
{
    if (amount <= currentMoney && cdAccounts[cdNumber].deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateCD(cdNumber,
                      cdAccounts[cdNumber].getBalance(),
                      cdAccounts[cdNumber].getInterestRate(),
                      cdAccounts[cdNumber].getTermLength(),
                      cdAccounts[cdNumber].getMinimumDeposit(),
                      cdAccounts[cdNumber].getYearsRemaining());
    } else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::buyStock(int numberOfShares, int stockNumber)
{
    double amount = numberOfShares * stocks[stockNumber].getValue();
    if (amount <= currentMoney && stocks[stockNumber].deposit(numberOfShares)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateStock(stockNumber, stocks[stockNumber].getMoneyBalance());
        emit numberOfStocksOwned(stocks[stockNumber].getBalance(), stockNumber);
    } else
        emit showErrorMessage("Input amount cannot be bought");
}

void MainModel::sendPriceOfXStocks(int numberOfShares, int stockNumber)
{
    double amount = numberOfShares * stocks[stockNumber].getValue();
    emit sendPriceOfStocks(amount, stockNumber);
}

void MainModel::sendSellingPriceOfXStocks(int numberOfShares, int stockNumber)
{
    double amount = numberOfShares * stocks[stockNumber].getValue();
    bool tooMany = numberOfShares > stocks[stockNumber].getBalance();
    emit sendSellingPriceOfStocks(amount, stockNumber, tooMany);
}

void MainModel::depositToLoan(double amount, int loanNumber)
{
    if (amount <= currentMoney && loans[loanNumber].deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit updateLoan(loanNumber,
                        loans[loanNumber].getBalance(),
                        loans[loanNumber].getInterestRate(),
                        loans[loanNumber].getAvailable(),
                        loans[loanNumber].getActive(),
                        loans[loanNumber].getYearsLeft());
    } else
        emit showErrorMessage("Input amount cannot be removed from the loan");
}

void MainModel::withdrawFromSavings(double amount)
{
    if (savingsAccount->withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    } else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::withdrawFromChecking(double amount)
{
    if (checkingAccount->withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateChecking(checkingAccount->getBalance());
    } else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::withdrawFromCD(int cdNumber)
{
    double amount = cdAccounts[cdNumber].getBalance();

    if (cdAccounts[cdNumber].withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateCD(cdNumber,
                      cdAccounts[cdNumber].getBalance(),
                      cdAccounts[cdNumber].getInterestRate(),
                      cdAccounts[cdNumber].getTermLength(),
                      cdAccounts[cdNumber].getMinimumDeposit(),
                      cdAccounts[cdNumber].getYearsRemaining());
    } else {
        emit showErrorMessage("Cannot withdraw from CD - still in term period");
    }
}

void MainModel::updateCDInformation(int cdNumber)
{
    emit updateCD(cdNumber,
                  cdAccounts[cdNumber].getBalance(),
                  cdAccounts[cdNumber].getInterestRate(),
                  cdAccounts[cdNumber].getTermLength(),
                  cdAccounts[cdNumber].getMinimumDeposit(),
                  cdAccounts[cdNumber].getYearsRemaining());
}

void MainModel::sellStock(int numberOfShares, int stockNumber)
{
    double amount = numberOfShares * stocks[stockNumber].getValue();
    if (stocks[stockNumber].withdraw(numberOfShares)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit updateStock(stockNumber, stocks[stockNumber].getMoneyBalance());
        emit numberOfStocksOwned(stocks[stockNumber].getBalance(), stockNumber);
    } else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::activateLoan(int loanNumber)
{
    if (loans[loanNumber].activate()) {
        currentMoney += -loans[loanNumber].getBalance();
        emit updateBalance(currentMoney);
        emit updateLoan(loanNumber,
                        loans[loanNumber].getBalance(),
                        loans[loanNumber].getInterestRate(),
                        loans[loanNumber].getAvailable(),
                        loans[loanNumber].getActive(),
                        loans[loanNumber].getYearsLeft());
    } else
        emit showErrorMessage("The loan cannot be activated");
}

void MainModel::nextYear()
{
    currentYear++;

    QVector<double> initialTotals;
    QVector<double> newTotals;
    double initialCounter;
    double newCounter;
    double tempCounter;
    bool loanOverdue = false;

    initialTotals.push_back(savingsAccount->getBalance());
    savingsAccount->nextYear();
    newTotals.push_back(savingsAccount->getBalance());
    emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());

    initialTotals.push_back(checkingAccount->getBalance());
    newTotals.push_back(checkingAccount->getBalance());

    initialCounter = 0;
    newCounter = 0;
    for (int i = 0; i < cdAccounts.count(); i++) {
        initialCounter += cdAccounts[i].getBalance();
        cdAccounts[i].nextYear();
        newCounter += cdAccounts[i].getBalance();
        emit updateCD(i,
                      cdAccounts[i].getBalance(),
                      cdAccounts[i].getInterestRate(),
                      cdAccounts[i].getTermLength(),
                      cdAccounts[i].getMinimumDeposit(),
                      cdAccounts[i].getYearsRemaining());
    }
    initialTotals.push_back(initialCounter);
    newTotals.push_back(newCounter);

    initialCounter = 0;
    newCounter = 0;
    // NEED TO ADD SOME CODE HERE TO EMIT A SIGNAL TO THE VIEW TO TELL IT TO UPDATE THE IMAGES OF STOCKS IF STOCKS WENT DOWN OR UP.
    QVector<double> initialStocks;
    QVector<double> afterYearEndStocks;
    for (int i = 0; i < stocks.count(); i++) {
        initialStocks.push_back(stocks[i].getValue());
        initialCounter += stocks[i].getMoneyBalance();
        stocks[i].nextYear();
        newCounter += stocks[i].getMoneyBalance();
        afterYearEndStocks.push_back(stocks[i].getValue());
        emit updateStock(i, stocks[i].getMoneyBalance());
    }

    emit stockChange(initialStocks.at(0) <= afterYearEndStocks.at(0), initialStocks.at(1) <= afterYearEndStocks.at(1), initialStocks.at(2) <= afterYearEndStocks.at(2));
    initialTotals.push_back(initialCounter);
    newTotals.push_back(newCounter);

    initialCounter = 0;
    newCounter = 0;
    for (int i = 0; i < loans.count(); i++) {
        if (loans[i].getActive()) {
            tempCounter = loans[i].getBalance();
            loans[i].nextYear();
            if (loans[i].getActive()) {
                initialCounter += tempCounter;
                newCounter += loans[i].getBalance();
            }
        }
        if (loans[i].getYearsLeft() < 0)
            loanOverdue = true;
        loans[i].setAvailable(creditScore);
        emit updateLoan(i,
                        loans[i].getBalance(),
                        loans[i].getInterestRate(),
                        loans[i].getAvailable(),
                        loans[i].getActive(),
                        loans[i].getYearsLeft());
    }
    initialTotals.push_back(initialCounter);
    newTotals.push_back(newCounter);

    // Calculate net worths
    initialTotals.push_back(initialTotals[0] + initialTotals[1] + initialTotals[2]
                            + initialTotals[3]+ initialTotals[4]);
    newTotals.push_back(newTotals[0] + newTotals[1] + newTotals[2] + newTotals[3]+ initialTotals[4]);

    // Calculate changes between years
    for (int i = 0; i < 6; i++)
        initialTotals[i] = -(initialTotals[i] - newTotals[i]);

    emit newYear(newTotals, initialTotals, currentYear);

    if (currentYear == 16 || loanOverdue) {
        endGame();
    }

    //Reseats Bonus quiz number
    remainingQuizzes = 3;
    emit quizzesRemainingChanged(remainingQuizzes);
}

void MainModel::settingsOpened(QWidget *currentWidget)
{
    this->currentWidget = currentWidget;
}

void MainModel::settingsClosed()
{
    emit returnToGame(this->currentWidget);
}

void MainModel::addFunds(double amount)
{
    currentMoney += amount;
    emit updateBalance(currentMoney);
}

void MainModel::handleLoanInfoRequest(int loanNumber) {
    Loan &loan = loans[loanNumber];
    emit updateLoan(loanNumber,
                    loan.getBalance(),
                    loan.getInterestRate(),
                    loan.getAvailable(),
                    loan.getActive(),
                    loan.getYearsLeft());
}

void MainModel::handleExtraQuizRequest() {

    if (remainingQuizzes <= 0) {
        emit showErrorMessage("No bonus quizzes remaining!");
        return;
    }
    remainingQuizzes--;
    emit quizzesRemainingChanged(remainingQuizzes);
    quizRequested(QuizCategory::mixOfAll, 5);
    emit quizStarted();
}

void MainModel ::endGame() {
    emit gameEnded();
}
