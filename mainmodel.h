#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "cdaccount.h"
#include "loan.h"
#include "quizhandler.h"
#include "savingsaccount.h"
#include "stock.h"

class MainModel : public QObject
{
    Q_OBJECT
public:
    explicit MainModel(QObject *parent = nullptr);

public slots:
    //TEMPORARY SLOT ADDED FOR TESTING.
    void requestQuiz();

    void checkAnswer(std::string selectedChoice);

    void getNextQuestion();

    void depositToSavings(double amount);

    void depositToCD(double amount, int cdNumber);

    void buyStock(int numberOfShares, int stockNumber);

    void depositToLoan(double amount, int loanNumber);

    void withdrawFromSavings(double amount);

    void withdrawFromCD(int cdNumber);

    void sellStock(int numberOfShares, int stockNumber);

    void activateLoan(int loanNumber);

    void nextYear();

    void settingsOpened(QWidget *currentWidget);

    void sendPriceOfXStocks(int numberOfStocks, int stockNumber);

    void sendSellingPriceOfXStocks(int numberOfStocks, int stockNumber);

    void updateCDInformation(int cdNumber);

    void settingsClosed();

signals:
    /**
     * Sends a question out for the view to display
     *
     * @param q - The question to be displayed
     */
    void sendQuestion(Question q);

    /**
     * Alerts the view as to whether the quiz question is correct.
     *
     * @param correct
     */
    void sendResult(bool result, std::string explanation);

    /**
     * Alerts the view that the quiz has been completed as well as how many were answered correctly
     *
     * @param numberCorrect - The number of correctly answered quizQuestions.
     */
    void quizFinished(uint numberCorrect);

    void quizProgress(uint progess);

    void updateSavings(double newBalance, double interestRate);

    void updateCD(int cdNumber,
                  double newBalance,
                  double interestRate,
                  int termlength,
                  double minimumDeposit,
                  int yearsLeft);

    void updateStock(int stockNumber, double newBalance);

    void updateLoan(
        int loanNumber, double newBalance, double interestRate, bool available, int yearsLeft);

    void sendPriceOfStocks(double price, int stockNumber);

    void sendSellingPriceOfStocks(double price, int stockNumber, bool tooMany);

    void numberOfStocksOwned(uint amount, int stockNumber);

    void returnToGame(QWidget *currentWidget);

    void updateBalance(double newBalance);

    void showErrorMessage(QString errorMessage);

    void newYear(QVector<double> newTotals, QVector<double> changes, int currentYear);

private:
    QuizHandler *quizHandler;

    double currentMoney;
    int creditScore;
    int currentYear;
    QWidget *currentWidget;

    SavingsAccount *savingsAccount;

    QVector<CDAccount> cdAccounts;

    QVector<Loan> loans;

    QVector<Stock> stocks;

    void addFunds(double amount);

    void endGame();
};

#endif // MAINMODEL_H
