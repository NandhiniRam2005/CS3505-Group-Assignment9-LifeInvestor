/*
The source file for MainModel.

This class represents the main model for the LifeInvesting application. It tracks the programs state, including things like
stocks owned, loans, cash, deposits, etc. It also handles things like sending quiz questions and life events to the view.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include "mainmodel.h"
#include <QtCore/qdebug.h>
#include "quizhandler.h"
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRandomGenerator>
#include <QDir>

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{

    restartGame();
}

double MainModel::calculateNetWorth()
{
    double total = currentMoney;
    total += savingsAccount->getBalance();

    // CDs
    for (CDAccount cd : cdAccounts)
        total += cd.getBalance();

    // Stocks
    for (Stock stock : stocks)
        total += stock.getMoneyBalance();

    // Only includes acrive loans
    for (Loan loan : loans) {
        if (loan.getActive()) {
            total += loan.getBalance();
        }
    }
    return total;
}

void MainModel::randomLifeEvent() {
    LifeEvent lifeEvent = this->lifeEventHandler->getRandomLifeEvent();
    if (checkInsurance(lifeEvent.category)) {
        lifeEvent.price = -75;
    }
    emit displayLifeEvent(lifeEvent);
    currentMoney = currentMoney + lifeEvent.price;
    emit updateBalance(currentMoney);
    emit netWorthChanged(calculateNetWorth());
}

bool MainModel::checkInsurance(std::string category) {
    for (ShopItem shopItem: shopItems) {
        if (shopItem.getName() == category && shopItem.isPurchased()) {
            return true;
        }
    }

    return false;
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
        if(quizHandler->getQuestionsAnsweredCorrectly() > 4){
            creditScore += 15;
            if (creditScore > 850)
                creditScore = 850;
            emit creditScoreChanged(creditScore);
        }
        emit quizFinished(quizHandler->getQuestionsAnsweredCorrectly(), quizHandler->getAmountEarned());
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
        setCreditScore(creditScore + 5);
        emit creditScoreChanged(creditScore);
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
    }
}

void MainModel::depositToSavings(double amount)
{
    if (amount <= currentMoney && savingsAccount->deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
        emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    } else
        emit showErrorMessage("Input amount cannot be deposited");
}

void MainModel::depositToCD(double amount, int cdNumber)
{
    if (amount <= currentMoney && cdAccounts[cdNumber].deposit(amount)) {
        currentMoney -= amount;
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
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
        emit netWorthChanged(calculateNetWorth());
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
        emit netWorthChanged(calculateNetWorth());
        emit updateLoan(loanNumber,
                        loans[loanNumber].getBalance(),
                        loans[loanNumber].getInterestRate(),
                        loans[loanNumber].getAvailable(),
                        loans[loanNumber].getActive(),
                        loans[loanNumber].getYearsLeft());
        if(loans[loanNumber].getBalance() == -10000){
            creditScore+=100;
        }
        if (creditScore > 850)
            creditScore = 850;
        emit creditScoreChanged(creditScore);
    } else
        emit showErrorMessage("Input amount cannot be removed from the loan");
}

void MainModel::withdrawFromSavings(double amount)
{
    if (savingsAccount->withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
        emit updateSavings(savingsAccount->getBalance(), savingsAccount->getInterestRate());
    } else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::withdrawFromCD(int cdNumber)
{
    double amount = cdAccounts[cdNumber].getBalance();

    if (cdAccounts[cdNumber].withdraw(amount)) {
        currentMoney += amount;
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
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
        emit netWorthChanged(calculateNetWorth());
        emit updateStock(stockNumber, stocks[stockNumber].getMoneyBalance());
        emit numberOfStocksOwned(stocks[stockNumber].getBalance(), stockNumber);
    } else
        emit showErrorMessage("Input amount cannot be withdrawn");
}

void MainModel::activateLoan(int loanNumber)
{
    if (!loans[loanNumber].getAvailable()) {
        emit showErrorMessage("Credit score too low for this loan!");
        return;
    }

    if (loans[loanNumber].activate()) {
        currentMoney += -loans[loanNumber].getBalance();
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
        emit updateLoan(loanNumber,
                        loans[loanNumber].getBalance(),
                        loans[loanNumber].getInterestRate(),
                        loans[loanNumber].getAvailable(),
                        loans[loanNumber].getActive(),
                        loans[loanNumber].getYearsLeft());
        setCreditScore(creditScore - 75);
        emit creditScoreChanged(creditScore);
    } else
        emit showErrorMessage("The loan cannot be activated");
}

void MainModel::nextYear()
{
    currentYear++;
    currentMoney-=yearlyBills;
    yearlyBills+=300;
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

    initialCounter = 0;
    newCounter = 0;
    for (int i = 0; i < cdAccounts.count(); i++) {
        if (cdAccounts[i].getYearsRemaining() == 0)
            withdrawFromCD(i);
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
    bool billWarningEmitted = false;
    for (int i = 0; i < loans.count(); i++) {
        if (loans[i].getActive()) {
            tempCounter = loans[i].getBalance();
            loans[i].nextYear();
            if (loans[i].getActive()) {
                initialCounter += tempCounter;
                newCounter += loans[i].getBalance();
            }
        }
        if(loans[i].getYearsLeft() == 0 && !billWarningEmitted){
            billWarningEmitted = true;
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

    // Calculate changes between years
    for (int i = 0; i < 4; i++)
        initialTotals[i] = -(initialTotals[i] - newTotals[i]);

    emit newYear(newTotals, initialTotals, currentYear, yearlyBills);
    bool gameOver = false;
    if (currentYear == 16) {
        endGame("You successfully played for 15 years!", "retired.png");
        gameOver = true;
    }
    if(loanOverdue){
        endGame("You failed to pay off your loan and the bill collector came for you!" , "angryBillCollector.png");
        gameOver = true;
    }

    if(currentMoney < 0){
        yearsBeingBroke++;
        if(yearsBeingBroke == 3 && !gameOver){
            emit displayWarning("You have been in debt for a while now... A raccoon has took notice and thinks he can do better than you in life. GET OUT OF DEBT!", "plottingRaccoon.png");
        }
        setCreditScore(creditScore - 25);
        emit creditScoreChanged(creditScore);
    }
    else{
        yearsBeingBroke = 0;
    }
    if(yearsBeingBroke > 0){
        endGame("You’ve been broke for so long (3 years), a raccoon claimed your identity and is doing better than you.", "broke.png");
        gameOver = true;
    }

    if(!gameOver && billWarningEmitted){
        emit displayWarning("One or more loans from BillDog is about to be due. Make sure you pay it on time", "annoyedBill.png");
    }

    //Resets Bonus quiz number
    remainingQuizzes = 3;
    emit quizzesRemainingChanged(remainingQuizzes);

    emit updateBalance(currentMoney);
    emit netWorthChanged(calculateNetWorth());
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
    emit netWorthChanged(calculateNetWorth());
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

bool MainModel::purchaseShopItem(int index)
{
    ShopItem& item = shopItems[index];
    if(!item.isPurchased() && currentMoney >= item.getCost()) {
        currentMoney -= item.getCost();
        item.setPurchased(true);
        emit shopItemPurchased(index);
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
        return true;
    }
    return false;
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

void MainModel::setCreditScore(int newScore) {
    creditScore = newScore;
    for(Loan &loan : loans) {
        loan.setAvailable(creditScore);
    }
    emit creditScoreChanged(creditScore);
}

void MainModel::startGamble()
{
    if (currentMoney >= 1000 && !isGamblingActive) {
        currentMoney -= 1000;
        isGamblingActive = true;
        correctCup = QRandomGenerator::global()->bounded(3);
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
        int newScore = creditScore - 10;
        creditScore = creditScore - 10;
        emit creditScoreChanged(newScore);
        emit shuffleStarted();
    }
}

void MainModel::checkCup(int cupNumber)
{
    isGamblingActive = false;
    if (cupNumber == correctCup) {
        int winnings = 2000;
        currentMoney += winnings;
        emit updateBalance(currentMoney);
        emit netWorthChanged(calculateNetWorth());
        emit gambleResult(true, winnings);
    } else {
        emit gambleResult(false, 0);
    }
    correctCup = -1;
}

void MainModel::endGame(QString reasonForEnd, QString imageName) {
    emit gameEnded(reasonForEnd, imageName);
}

void MainModel::getLeaderboard(){
    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection))
    {
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("scores.db");

    if (!db.open()) {
        std::cout << "Error: Could not open database -" << std::endl;
        return;
    }
    QSqlQuery selection(db);
    QVector<QString> data;
    QVector<QString> names;
    QVector<QString> credit;
    QVector<QString> rank;
    data.push_back("Name                    Credit                    Rank");
    if (selection.exec("Select name, credit, rank from scores order by credit desc")){
        while(selection.next()){
            int nameLength = selection.value(0).toString().length();
            int numberSpaces = 28 - nameLength;
            QString spaces = "";
            for(int i = 0; i < numberSpaces; i++){
                spaces.append(" ");
            }
            names.push_back(selection.value(0).toString());
            credit.push_back(selection.value(1).toString());
            rank.push_back(selection.value(2).toString());
        }
    }
    else{
        qDebug() << "Error occurred while selecting data RIP";
    }
    db.close();
    emit showLeaderBoard(names, credit, rank);
}

void MainModel::saveGame(QString name, QString rank){
    if(name.length() > 9 || name.isEmpty()){
        emit invalidName();
        return;
    }

    // Removes the connection if it already exists.
    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection))
    {
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("scores.db");
    if (!db.open()) {
        std::cout << "Error: Could not open database -" << std::endl;
        return;
    }
    QSqlQuery createTable(db);

    if(!createTable.exec("CREATE TABLE IF NOT EXISTS scores (scoreId INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, credit INTEGER NOT NULL, rank TEXT NOT NULL)")){
        std::cout<< "Error executing create table query" << std::endl;
    }

    // protected from injection attacks
    QString insertQuery = "INSERT INTO scores (name, credit, rank) VALUES (:name, :credit, :rank)";
    QSqlQuery insertScore(db);
    insertScore.prepare(insertQuery);
    insertScore.bindValue(":name", name);
    insertScore.bindValue(":credit", creditScore);
    insertScore.bindValue(":rank", rank);
    if(!insertScore.exec()){
        std::cout<< "Error executing insert query" << std::endl;
    }
    db.close();
    emit saved();
}

void MainModel::restartGame(){
    std::cout<<"resetting"<< std::endl;

    if(quizHandler != nullptr){
        delete quizHandler;
    }
    if(lifeEventHandler != nullptr){
        delete lifeEventHandler;
    }
    if(savingsAccount != nullptr){
        delete savingsAccount;
    }

    quizHandler = new QuizHandler(this);
    lifeEventHandler = new LifeEventHandler(this);

    currentMoney = 0;
    creditScore = 650;
    currentYear = 1;
    tempYear = 1;
    yearlyBills = 500;
    yearsBeingBroke = 0;

    savingsAccount = new SavingsAccount(0.004);
    emit updateSavings(0, savingsAccount->getInterestRate());

    cdAccounts.clear();
    cdAccounts.push_back(CDAccount(0.035, 2, 500));
    cdAccounts.push_back(CDAccount(0.040, 4, 750));
    cdAccounts.push_back(CDAccount(0.045, 5, 1000));
    for(int i = 0; i<cdAccounts.size(); i++){
        emit updateCD(i,
                      cdAccounts[i].getBalance(),
                      cdAccounts[i].getInterestRate(),
                      cdAccounts[i].getTermLength(),
                      cdAccounts[i].getMinimumDeposit(),
                      cdAccounts[i].getYearsRemaining());
    }
    loans.clear();

    loans.push_back(Loan(0.36, 10000, 0, 5));
    loans.push_back(Loan(0.067, 10000, 750, 7));
    loans[0].setAvailable(creditScore);
    loans[1].setAvailable(creditScore);
    for(int i = 0; i<loans.size(); i++){
        emit updateLoan(i,
                        loans[i].getBalance(),
                        loans[i].getInterestRate(),
                        loans[i].getAvailable(),
                        loans[i].getActive(),
                        loans[i].getYearsLeft());
    }

    stocks.clear();
    stocks.push_back(Stock(190.42, 0.40, 1.29)); // Pear
    stocks.push_back(Stock(70.76, 0.33, 1.20)); // Coma-Cola
    stocks.push_back(Stock(27.18, 0.65, 1.08)); // CineKarl
    for(int i = 0; i<stocks.size(); i++){
        updateStock(i, 0);
        sendPriceOfStocks(0, i);
        emit numberOfStocksOwned(0, i);
    }
    shopItems.clear();
    shopItems.append(ShopItem("Auto Insurance", 5000));
    shopItems.append(ShopItem("Health Insurance", 7000));
    shopItems.append(ShopItem("Pet Insurance", 2000));
    shopItems.append(ShopItem("Home Insurance", 10000));

    emit updateBalance(0);
    emit creditScoreChanged(650);
    emit netWorthChanged(0);
}
