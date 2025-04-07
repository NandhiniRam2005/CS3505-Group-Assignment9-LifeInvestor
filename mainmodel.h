#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "quizhandler.h"
#include "savingsaccount.h"
#include "loan.h"
#include "cdaccount.h"
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

    void buyStock(double amount, int stockNumber);

    void depositToLoan(double amount, int loanNumber);

    void withdrawFromSavings(double amount);

    void withdrawFromCD(double amount, int cdNumber);

    void sellStock(double amount, int stockNumber);

    void withdrawFromLoan(double amount, int loanNumber);

    void nextYear();

    void settingsOpened(QWidget* currentWidget);

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

    void updateSavingsBalance(double newBalance);

    void updateCDBalances(QVector<double> newBalances);

    void updateStockBalances(QVector<double> newBalances);

    void updateLoanBalances(QVector<double> newBalances);

    void updateCurrentMoney(double newAmount);

    void returnToGame(QWidget* currentWidget);

private:
    QuizHandler *quizHandler;

    double currentMoney;
    int creditScore;
    int currentYear;
    QWidget* currentWidget;

    SavingsAccount* savingsAccount;

    QVector<CDAccount> cdAccounts;

    QVector<Loan> loans;

    QVector<Stock> stocks;
};

#endif // MAINMODEL_H
