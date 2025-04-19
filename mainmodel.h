/*
The header file for MainModel.

This class represents the main model for the LifeInvesting application. It tracks the programs state, including things like
stocks owned, loans, cash, deposits, etc. It also handles things like sending quiz questions and life events to the view.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#ifndef MAINMODEL_H
#define MAINMODEL_H

#include <QObject>
#include "cdaccount.h"
#include "loan.h"
#include "quizhandler.h"
#include "savingsaccount.h"
#include "stock.h"
#include "shopitem.h"
#include "lifeeventhandler.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


class MainModel : public QObject
{
    Q_OBJECT

public:

    /**
     * Constructs the MainModel widget.
     * @param parent - the Parent widget.
     */
    explicit MainModel(QObject *parent = nullptr);

    /**
     * Checks whether insurance is purchased for that specific category
     * @param category the type of insurance
     * @return true if insurance is purchased; false otherwise
     */
    bool checkInsurance(std::string category);


public slots:

    /**
     * Purchases a shop item
     * @param index the item to purchase
     * @return true if the item was successfully purchased, false otherwise
     */
    bool purchaseShopItem(int index);

    /**
     * Calculate and return the current net worth of the user
     * @return The current net worth of the user
     */
    double calculateNetWorth();

    /**
     * Generate a quiz from a given category with a given length
     * @param category the category of the quiz
     * @param length the length of the quiz
     */
    void quizRequested(QuizCategory category, uint length);

    /**
     * Check if the answer to a given quiz question is correct
     * @param selectedChoice The answer the is selected
     */
    void checkAnswer(std::string selectedChoice);

    /**
     * Move on to the next question of the quiz
     */
    void getNextQuestion();

    /**
     * Get the information about the current Quiz Category
     */
    void getQuizInfo();

    /**
     * Deposit a certain amount into the savings account
     * @param amount the amount to deposit
     */
    void depositToSavings(double amount);

    /**
     * Deposit a certain amount into a CD
     * @param amount the amount to deposit
     * @param cdNumber the CD to deposit into
     */
    void depositToCD(double amount, int cdNumber);

    /**
     * Buy a certain number of stocks
     * @param numberOfShares the number of shares to buy
     * @param stockNumber The stock to buy shares of
     */
    void buyStock(int numberOfShares, int stockNumber);

    /**
     * Pay off a certain amount of a loan
     * @param amount The amount to pay on the loan
     * @param loanNumber The loan to pay on
     */
    void depositToLoan(double amount, int loanNumber);

    /**
     * Withdraw a certain amount from the savings account
     * @param amount the amount to withdraw
     */
    void withdrawFromSavings(double amount);

    /**
     * Withdraw the total balance of a given CD
     * @param cdNumber The CD to withdraw from
     */
    void withdrawFromCD(int cdNumber);

    /**
     * Sell a certain amount of stock
     * @param numberOfShares the number of shares to sell
     * @param stockNumber the stock to sell
     */
    void sellStock(int numberOfShares, int stockNumber);

    /**
     * Take out a loan
     * @param loanNumber the loan to take out
     */
    void activateLoan(int loanNumber);

    /**
     * Advance to the next year
     */
    void nextYear();

    /**
     * Open the settings page
     * @param currentWidget the widget / page that was selected when the settings button was clicked
     */
    void settingsOpened(QWidget *currentWidget);

    /**
     * Emit a sendPriceOfXStocks signal with the price it would take to purchase a certain number of shares of a stock
     * @param numberOfStocks the number of shares to purchase
     * @param stockNumber the stock to purchase
     */
    void sendPriceOfXStocks(int numberOfStocks, int stockNumber);

    /**
     * Emit a sendSellingPriceOfXStocks signal with the price it would take to purchase a certain number of shares of a stock
     * @param numberOfStocks the number of shares to purchase
     * @param stockNumber the stock to purchase
     */
    void sendSellingPriceOfXStocks(int numberOfStocks, int stockNumber);

    /**
     * Update the information on a given CD for the current year
     * @param cdNumber the CD to update
     */
    void updateCDInformation(int cdNumber);

    /**
     * Close the settings page and return to the previous widget
     */
    void settingsClosed();

    /**
     * Request info on a given loan
     * @param loanNumber the loan requested
     */
    void handleLoanInfoRequest(int loanNumber);

    /**
     * Request an extra quiz for the year
     */
    void handleExtraQuizRequest();

    /**
     * Give the user a random life event
     */
    void randomLifeEvent();

    /**
     * Set the users credit score to a new amount
     * @param newScore the new credit score
     */
    void setCreditScore(int newScore);

    /**
     * Starts the cup gamble game functionality.
     */
    void startGamble();

    /**
     * Checks if the cup selected contains the ball.
     *
     * @param cupNumber - The cup to be checked
     */
    void checkCup(int cupNumber);

    /**
     * Queries our database to get the leaderboard as a collection of strings. Eventually returns that to the view.
     */
    void getLeaderboard();

    /**
     * Called when the user attempts to save their name, score, and rank to our leaderboard database. Database uses Sqlite
     *
     * @param name - The name that should be stored in the database.
     * @param rank - The rank the player recieved
     */
    void saveGame(QString name, QString rank);


signals:
    /**
     * Sends a question out for the view to display
     *
     * @param q - The question to be displayed
     */
    void sendQuestion(Question q);

    /**
     * Sends out information about the current Quiz Category
     * @param qI - The Information about the current Quiz Category
     */
    void sendQuizInfo(QuizInfo qI);

    /**
     * Sends out the result of the current quiz question
     *
     * @param result - true if the correct answer was selected, otherwise false
     * @param explaination - An explanation for why the correct answer is correct
     */
    void sendResult(bool result, std::string explanation);

    /**
     * Sends out additional information when the quiz is completed
     *
     * @param numberCorrect - The number of correctly answered quiz questions.
     * @param moneyEarned - The total amount of money the user earned taking this quiz
     */
    void quizFinished(uint numberCorrect, int moneyEarned);

    /**
     * Sends out the current amount of progress that has been made on this quiz
     * @param progress a number 0-100 representing the percentage of the quiz that has been completed
     */
    void quizProgress(uint progress);

    /**
     * Emitted whenever the user's net worth changes
     * @param newNetWorth the user's new net worth
     */
    void netWorthChanged(double newNetWorth);

    /**
     * Emitted whenever the savings account updates
     * @param newBalance the new balance of the savings account
     * @param interestRate the interest rate of the savings account
     */
    void updateSavings(double newBalance, double interestRate);

    /**
     * Emitted whenever the checking account updates
     * @param newBalance the new balance of the checking account
     */
    void updateChecking(double newBalance);

    /**
     * Emitted whenever a CD updates
     * @param cdNumber the CD that updated
     * @param newBalance the CD's new balance
     * @param interestRate the CD's interest rate
     * @param termlength The length left on the CD's term
     * @param minimumDeposit The minimum amount that can be deposited in the CD
     * @param yearsLeft The number of years left on the CD's term
     */
    void updateCD(int cdNumber,
                  double newBalance,
                  double interestRate,
                  int termlength,
                  double minimumDeposit,
                  int yearsLeft);

    /**
     * Emmitted whenever a Stock updates
     * @param stockNumber The stock that updated
     * @param newBalance The number of shares the user owns of this stock
     */
    void updateStock(int stockNumber, double newBalance);

    /**
     * Emitted whenever a Loan updates
     * @param loanNumber the loan that updated
     * @param newBalance The new balance on the loan
     * @param interestRate the loan's interest rate
     * @param available whether or not the loan is available to take out
     * @param active whether or not the loan is active
     * @param yearsLeft The number of years left to pay this loan off
     */
    void updateLoan(
        int loanNumber, double newBalance, double interestRate, bool available,  bool active, int yearsLeft);

    /**
     * Sends the price it would take to purchase the number of shares requested in this signal's corresponding slot
     * @param price the price to purchase those shares
     * @param stockNumber the stock to purchase
     */
    void sendPriceOfStocks(double price, int stockNumber);

    /**
     * Sends the amount you would make selling the number of shares requested in this signal's corresponding slot
     * @param price the amount you would make selling those shares
     * @param stockNumber the stock to sell
     * @param tooMany true if the user does not own this many shares, otherwise false
     */
    void sendSellingPriceOfStocks(double price, int stockNumber, bool tooMany);

    /**
     * Sends the number of shares of a particular stock owned by the user
     * @param amount the number of shares owned
     * @param stockNumber the stock the user owns shares of
     */
    void numberOfStocksOwned(uint amount, int stockNumber);

    /**
     * Emitted when the user wants to go back to a previous page / widget
     * @param currentWidget The widget / page the user was previously on
     */
    void returnToGame(QWidget *currentWidget);

    /**
     * Emitted when the user's balance updates
     * @param newBalance the new balance of the user
     */
    void updateBalance(double newBalance);

    /**
     * Emitted when an error message should be shown
     * @param errorMessage The error message to show
     */
    void showErrorMessage(QString errorMessage);

    /**
     * Emitted when a new year ocurrs
     * @param newTotals A vector of doubles holding the balances of the checking account, credit score, etc.
     * @param changes The change of the totals between the current year and this year
     * @param currentYear The current year that it is
     * @param yearlyBills The yearly bill the user has
     */
    void newYear(QVector<double> newTotals, QVector<double> changes, int currentYear, double yearlyBills);

    /**
     * Emitted when the prices of the stocks change
     * @param stockOneUp whether or not stock one increased in value
     * @param stockTwoUp whether or not stock two increased in value
     * @param stockThreeUp whether or not stock three increased in value
     */
    void stockChange(bool stockOneUp, bool stockTwoUp, bool stockThreeUp);

    /**
     * Emitted when the game ends
     * @param reasonForEnd A string with information for why the game ended
     * @param imageName The image to display when the game ends
     */
    void gameEnded(QString reasonForEnd, QString imageName);

    /**
     * Emitted when the amount of quizzes the User has remaining changes
     * @param remaining the amount of quizzes the user has remaining
     */
    void quizzesRemainingChanged(int remaining);

    /**
     * Emmitted when a quiz starts
     */
    void quizStarted();

    /**
     * Emmitted when a life event happens
     * @param lifeEvent the life event that occurred
     */
    void displayLifeEvent(LifeEvent lifeEvent);

    /**
     * Emitted when a warning ocurrs
     * @param warning A string describing the warning
     * @param image An image to display with the warning
     */
    void displayWarning(QString warning, QString image);

    /**
     * Emitted when the User's credit score changes
     * @param newScore the new credit score of the user
     */
    void creditScoreChanged(int newScore);

    /**
     * Emmitted when the cups start shuffling
     */
    void shuffleStarted();

    /**
     * emitted once a cup is selected
     * @param won if the player one the gamble
     * @param amount the amount that was won
     */
    void gambleResult(bool won, int amount);

    /**
     * Emmitted when the items in the shop change
     */
    void shopItemPurchased(int index);

    /*
     * Alerts the view that the leaderboard should be displayed
     *
     * @param data - The data that should be displayed in the leaderboard box.
     */
    void showLeaderBoard(QVector<QString> names, QVector<QString> credit, QVector<QString> rank);

    /*
     * Alerts the view that the name provided in the save name input is invalid (no name or name longer than 9 chars).
     */
    void invalidName();

    /*
     * Alerts the view that the name score and credit was succesfully saved.
     */
    void saved();

private:
    QuizHandler *quizHandler;
    LifeEventHandler *lifeEventHandler;

    double currentMoney;
    int creditScore;
    int currentYear;
    int tempYear;
    int remainingQuizzes = 3;
    double yearlyBills;
    int yearsBeingBroke = 0;
    int correctCup = -1;
    bool isGamblingActive = false;

    QWidget *currentWidget;

    SavingsAccount *savingsAccount;

    QVector<CDAccount> cdAccounts;

    QVector<Loan> loans;

    QVector<Stock> stocks;

    /**
     * Adds money to the user's balance
     * @param amount the amount of money to add
     */
    void addFunds(double amount);

    /**
     * Handles logic for ending the game
     * @param reasonForEnd the reason the game ended
     * @param imageName an image to display when the game ends
     */
    void endGame(QString reasonForEnd, QString imageName);

    QVector<ShopItem> shopItems;

};

#endif
