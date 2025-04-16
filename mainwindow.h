#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*
The header file for MainWindow.

This class represents the main window for the LifeInvesting application. It consistenly asks the model for information
to display and displays the information to the user. The view is an interactive location for the user to interact with
our game.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/
#include <QButtonGroup>
#include <QMainWindow>
#include <QSoundEffect>
#include "animationview.h"
#include "mainmodel.h"
#include "quizhandler.h"
#include "startscreenview.h"
#include "lifeeventdisplay.h"
#include "warningdisplay.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(MainModel *model, QWidget *parent = nullptr);
    ~MainWindow();
    
    /**
     * Sets up connections for the life events
     * @param model - the main model of the program
     */
    void lifeEventsConnections(MainModel *model);
    
private:
    /**
     * The main windows ui as a pointer
     */
    Ui::MainWindow *ui;

    /**
     * A pointer to a group of buttons (quiz question selections)
     */
    QButtonGroup *buttonGroup;

    /**
     * The question that needs to be currently displayed in the view
     */
    Question currentQuestion;

    /**
     * The amount of money that needs to be currenly displayed in the view (temporary and not stored in view)
     * this is only here for displayign purposes.
     */
    double currentMoney;

    /**
     * The stock balances that should be displayed in the view (this is not managed by main window,
     * it is simply here to make code cleaner)
     */
    QVector<double> stockBalances;

    /**
     * The loan balances that should be displayed in the view (this is not managed by main window,
     * it is simply here to make code cleaner)
     */
    QVector<double> loanBalances;

    /**
     * The savings balances that should be displayed in the view (this is not managed by main window,
     * it is simply here to make code cleaner)
     */
    double savingsBalance;

    /**
     * The cd balances that should be displayed in the view (this is not managed by main window,
     * it is simply here to make code cleaner)
     */
    QVector<double> cdBalances;

    /**
     * Animation view pointer used to display animations in our application.
     */
    AnimationView *animationView;

    /**
     * A pointer to a start screen used to display the start screen.
     */
    StartScreenView *startScreenView;

    /**
     * The sound to be played when a quiz has been answered correctly
     */
    QSoundEffect *levelPassSound;

    /**
     * The sound to be played when a quiz has been answered incorrectly
     */
    QSoundEffect *levelFailSound;

    /**
     * The sound to be played when a money is deposited into an account.
     */
    QSoundEffect *depositSound;

    /**
     * The life event display pointer used to display changing life events.
     */
    LifeEventDisplay lifeEventDisplay;

    /**
     * A warning display pointer used to display changing warnings.
     */
    warningdisplay warningDisplay;

    /**
     * Generates a string that represents the changes in the past year fiscally speaking.
     *
     * @param newTotals - The new amount of moeny in different investments.
     * @param changes - The amount of change since the previous fiscal year.
     * @return  - A string which represents the changes.
     */
    QString generateReportString(QVector<double> newTotals, QVector<double> changes);

    /**
     * The quiz which should be requested of the model.
     */
    QuizCategory quizCategory;

    /**
     * The length of the quiz which should be requested from the model.
     */
    uint quizLength;

    /**
     * Represents if the user has clicked start once in the view. Not to be stored in the model
     * as it is something that pertains solely to dynamic loading of the view.
     */
    bool firstStart;

    /**
     * Represents if the view has displayed a lifeEvent. Only used in main winodw for view related
     * purposes has nothing to do with the model or any underlying data.
     */
    bool lifeEventShown;

    /**
     * Sets up the general ui at the beginning of the game.
     */
    void generalUISetup();

    /**
     *  Sets up the gifs at the beginning of the game.
     */
    void setUpGifs();

    /**
     * Sets up the audio at the beginning of the game.
     */
    void setupAudio();

    /**
     * Enables quiz submissions at the beginning of the game.
     */
    void enableQuizSubmission();

    /**
     * Connections for depositing to different investments.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void depositingConnectionWindowToModel(MainModel *model);

    /**
     * Connections for withdrawing from different investments.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void withdrawingConnectionsWindowToModel(MainModel *model);

    /**
     * Connections for buying stock.
     */
    void buyingStockUIConnections();

    /**
     * Connections for selling stock.
     */
    void sellingStockUIConnections();

    /**
     * Connections for making visual updates to the Stock page.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void visualIUpdatesStockConnections(MainModel *model);

    /**
     * Connections for the cdPage
     *
     * @param model - a reference to the model used to make these connections.
     */
    void cdPageConnections(MainModel *model);

    /**
     * Connections for the savings page.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void savingsPageConnections(MainModel *model);

    /**
     * Connections for the loan page.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void loansPageConnections(MainModel *model);

    /**
     * Connections for the casino page.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void casinoPageConnections(MainModel *model);

    /**
     * Connections for advancing the game.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void nextYearConnections(MainModel *model);

    /**
     * @brief phoneConnections
     */
    void phoneConnections();

    /**
     * Connections for the settings page
     *
     * @param model - a reference to the model used to make these connections.
     */
    void settingsConnections(MainModel *model);

    /**
     * Connections for the extra quizzes app.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void extraQuizesPageConnections(MainModel *model);

    /**
     * General connections for a quiz
     *
     * @param model - a reference to the model used to make these connections.
     */
    void quizConnections(MainModel *model);

    /**
     * Connections for ensuring updating values of view credit and networth.
     *
     * @param model - a reference to the model used to make these connections.
     */
    void mainWindowValueUpdateConnections(MainModel *model);

public slots:

    /**
     * Starts a quiz in the view
     *
     * @param category - The category of the quiz to be started
     * @param questionAmount - How many questions should be in the quiz
     */
    void startQuiz(QuizCategory category, uint questionAmount);

    /**
     * Shows each question individually one by one.
     *
     * @param q - The question to be displayed
     */
    void showQuizData(Question q);

    /**
     * What should occur each time a new year starts.
     */
    void onStartClicked();

    /**
     * helper slot for submitting responses to a quiz.
     */
    void submitHelper();

    /**
     * Displays the result of a quiz question. Whether the user was correct or not.
     *
     * @param result - Incorrect/Correct
     * @param explanation - Why the correct answer is correct.
     */
    void displayResult(bool result, std::string explanation);

    /**
     * Updates the progress bar of the quiz.
     *
     * @param progress - The current progress of the quiz.
     */
    void updateProgress(uint progress);

    /**
     * Recieves information about a quiz so that the user can learn. These are learning materials!
     *
     * @param qI - The information about the quiz
     */
    void updateQuizInfo(QuizInfo qI);

    /**
     * Updates the networth view label
     *
     * @param netWorth - The new networth to display.
     */
    void updateNetWorth(double netWorth);

    /**
     * Displays updates to the savings display.
     *
     * @param newBalance - The new savings amount.
     * @param interestRate - The rate of interest on the account.
     */
    void updateSavings(double newBalance, double interestRate);

    //void updateChecking(double newBalance);

    /**
     * Updates the cd display to display new values.
     *
     * @param cdNumber - The specific cd to update
     * @param newBalance - The new balance that the cd should have.
     * @param interestRate - The interest that the cd is accuring
     * @param termlength - How long the cd will last for.
     * @param minimumDeposit - How much money must be deposited
     * @param yearsLeft - How many years the user has left on the cd if applicable.
     */
    void updateCD(int cdNumber,
                  double newBalance,
                  double interestRate,
                  int termlength,
                  double minimumDeposit,
                  int yearsLeft);

    /**
     * Updates a specific stock in the view
     *
     * @param stockNumber - The specific stock
     * @param newBalance - The new amount of money invested in the stock.
     */
    void updateStock(int stockNumber, double newBalance);

    /**
     * Updates all stock graphs to reflect growth/fall.
     *
     * @param stockOneUp - Did stock one go up in the past year?
     * @param stockTwoUp - Did stock two go up in the past year?
     * @param stockThreeUp - Did stock three go up in the past year?
     */
    void updateStockImage(bool stockOneUp, bool stockTwoUp, bool stockThreeUp);

    /**
     * Updates a specific loan in the view.
     *
     * @param loanNumber - The specific loan to update.
     * @param newBalance - The new balance of the loan.
     * @param interestRate - The rate of interest on the loan.
     * @param available - According to the user's credit score is the loan available.
     * @param active - Is the loan active?
     * @param yearsLeft - How many years does the user have left to pay it off if applicable.
     */
    void updateLoan(
        int loanNumber, double newBalance, double interestRate, bool available, bool active, int yearsLeft);

    /**
     * Update the checking account balance.
     *
     * @param newAmount - The new checking account balance recieved from the model.
     */
    void updateBalance(double newAmount);

    /**
     * Updates the stock price to display as the view dynamically shows how much the player will spend.
     *
     * @param amount - The amount it will cost.
     * @param stockNumber - The specific stock they are adding to their cart.
     */
    void updateStockPriceDisplay(double amount, int stockNumber);

    /**
     * Updates the the stock selling price that the user is adding to their sell cart.
     *
     * @param amount - The amount it will sell for.
     * @param stockNumber - The stock they are selling.
     * @param tooMany - If they are attempting to sell too many stocks!
     */
    void updateSellingStockPriceDisplay(double amount, int stockNumber, bool tooMany);

    /**
     * Updates a label which shows how many stocks are owned by the user.
     *
     * @param amount - How many shares owned.
     * @param stockNumber - The specific stock that should be updated
     */
    void updateStockAmountOwned(uint amount, int stockNumber);

    /**
     * Displays the final quiz screen the end of quiz screen.
     *
     * @param questionsAnsweredCorrectly - The number of questions answered correctly.
     * @param moneyEarned - How many money was earned throughout the quiz.
     */
    void showEndScreen(uint questionsAnsweredCorrectly, int moneyEarned);

    /**
     * Enabales submit button.
     *
     * @param checked - If a response has been logged.
     */
    void enableSubmitButton(bool checked);

    /**
     * Displays the phone widget.
     */
    void displayPhone();

    /**
     * Hides the phone widget.
     */
    void hidePhone();

    /**
     * Return to the game screen.
     *
     * @param currentWidget - What widget we are currently on.
     */
    void returnToGame(QWidget *currentWidget);

    /**
     * Shows an error message to the user.
     *
     * @param errorMessage - The error message to display.
     */
    void showErrorMessage(QString errorMessage);

    /**
     * Revalidates all stock displays to show if the user is trying to purchase/sell bad amounts of stock.
     */
    void revalidateAllStockDisplays();

    /**
     * Creates a new year in the view.
     *
     * @param newTotals - Totals to update the view
     * @param changes - The change in money since last year.
     * @param currentYear - What year it is.
     * @param yearlyBills - The bills that must be paid this year.
     */
    void newYear(QVector<double> newTotals, QVector<double> changes, int currentYear, double yearlyBills);

    /**
     * Displays the game ending screen.
     *
     * @param reason - The reason for the game ending.
     * @param imageName - The image to display in the screen.
     */
    void gameEnded(QString reason, QString imageName);

    /**
     * Displays a new life event.
     *
     * @param lifeEvent - The life event to display.
     */
    void showLifeEvent(LifeEvent lifeEvent);

    /**
     * Shows a new warning to the user.
     *
     * @param warning - The warning.
     * @param image - The image to go with the warning.
     */
    void showWarning(QString warning, QString image);

    /**
     * Updates the credit score in the view.
     *
     * @param score - The new score to display.
     */
    void updateCreditScore(int score);

signals:

    /**
     * Requests the model for a quiz.
     *
     * @param category - The category for the quiz.
     * @param questionAmount - The number of questions to request.
     */
    void requestQuiz(QuizCategory category, uint questionAmount);

    /**
     * Asks the model if the answer is correct.
     *
     * @param answer - The selected answer.
     */
    void sendAnswer(std::string answer);

    /**
     * Tells the model to deposit some money into savings.
     *
     * @param amount - The amount of money to deposit
     */
    void depositToSavings(double amount);

    /**
     * Tells the model to deposit some money into checking.
     *
     * @param amount - The amount of money to deposit
     */
    void depositToChecking(double amount);

    /**
     * Tells the model to deposit some money into savings.
     *
     * @param amount - The amount of money to deposit
     * @param cdNumber - The cd to deposit into.
     */
    void depositToCD(double amount, int cdNumber);

    /**
     * Tells the model to buy some stock
     *
     * @param numberOfShares - How many shares to buy.
     * @param stockNumber - Which stock to buy.
     */
    void buyStock(int numberOfShares, int stockNumber);

    /**
     * Tells the model to deposit some money into a loan.
     *
     * @param amount - The amount of money to deposit
     * @param loanNumber - The loan to payoff
     */
    void depositToLoan(double amount, int loanNumber);

    /**
     * Tells the model to withdraw some money from savings.
     *
     * @param amount - The amount of money to withdraw.
     */
    void withdrawFromSavings(double amount);

    /**
     * Tells the model to withdraw some money from checkings.
     *
     * @param amount - The amount of money to withdraw.
     */
    void withdrawFromChecking(double amount);

    /**
     * Tells the model to withdraw all money from a cd.
     *
     * @param cdNumber - The cd to withdraw from.
     */
    void withdrawFromCD(int cdNumber);

    /**
     * Alerts the model to sell some stock.
     *
     * @param numberOfShares - How many shares to sell.
     * @param stockNumber - Which stock to sell.
     */
    void sellStock(int numberOfShares, int stockNumber);

    /**
     * Alerts the model that a loan has been activated.
     *
     * @param loanNumber - Which loan to activate.
     */
    void activateLoan(int loanNumber);

    /**
     * Alerts the model to advance the year.
     */
    void nextYear();

    /**
     * Asks the model for the purchasing price of x stocks.
     *
     * @param numberOfShares - How many shares to ask for price of
     * @param stockNumber - Which stock price.
     */
    void requestPriceOfXStocks(int numberOfShares, int stockNumber);

    /**
     * Asks the model for the selling price of x stocks.
     *
     * @param numberOfShares - How many shares to ask for price of
     * @param stockNumber - Which stock price.
     */
    void requestSellingPriceOfXStocks(int numberOfShares, int stockNumber);

    /**
     * Asks the model for information on revalidating the stock display.
     */
    void revalidateStockDisplay();

    /**
     * Revalidates a specific stocks display.
     *
     * @param amount - How many the user was trying to purchase/sell.
     * @param stockNumber - Which stock to revalidate.
     */
    void revalidateSpecificStockDisplay(int amount, int stockNumber);

    /**
     * Asks the model to do what must be done when opening settings.
     *
     * @param currentWidget - What widget the user is currently on.
     */
    void settingsOpened(QWidget *currentWidget);

    /**
     * Asks the model for some cd info.
     *
     * @param cdNumber - Which cd to get info on.
     */
    void requestCDInfo(int cdNumber);

    /**
     * How many money to deposit to model.
     *
     * @param amount - The amount to deposit.
     */
    void savingsDepositAmountRead(double amount);

    /**
     * How many money to withdraw to model.
     *
     * @param amount - The amount to withdraw.
     */
    void savingsWithdrawAmountRead(double amount);

    /**
     * Gets info on a loan.
     *
     * @param loanNumber - The loan to get info on.
     */
    void requestLoanInfo(int loanNumber);

    /**
     * Asks the model for a life event.
     */
    void requestLifeEvent();
};
#endif // MAINWINDOW_H
