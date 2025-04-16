#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
     * @brief startQuiz
     * @param category
     * @param questionAmount
     */
    void startQuiz(QuizCategory category, uint questionAmount);

    /**
     * @brief showQuizData
     * @param q
     */
    void showQuizData(Question q);

    /**
     * @brief onStartClicked
     */
    void onStartClicked();

    /**
     * @brief submitHelper
     */
    void submitHelper();

    /**
     * @brief displayResult
     * @param result
     * @param explanation
     */
    void displayResult(bool result, std::string explanation);

    /**
     * @brief updateProgress
     * @param progress
     */
    void updateProgress(uint progress);

    /**
     * @brief updateQuizInfo
     * @param qI
     */
    void updateQuizInfo(QuizInfo qI);

    /**
     * @brief updateNetWorth
     * @param netWorth
     */
    void updateNetWorth(double netWorth);

    /**
     * @brief updateSavings
     * @param newBalance
     * @param interestRate
     */
    void updateSavings(double newBalance, double interestRate);

    //void updateChecking(double newBalance);

    /**
     * @brief updateCD
     * @param cdNumber
     * @param newBalance
     * @param interestRate
     * @param termlength
     * @param minimumDeposit
     * @param yearsLeft
     */
    void updateCD(int cdNumber,
                  double newBalance,
                  double interestRate,
                  int termlength,
                  double minimumDeposit,
                  int yearsLeft);

    /**
     * @brief updateStock
     * @param stockNumber
     * @param newBalance
     */
    void updateStock(int stockNumber, double newBalance);

    /**
     * @brief updateStockImage
     * @param stockOneUp
     * @param stockTwoUp
     * @param stockThreeUp
     */
    void updateStockImage(bool stockOneUp, bool stockTwoUp, bool stockThreeUp);

    /**
     * @brief updateLoan
     * @param loanNumber
     * @param newBalance
     * @param interestRate
     * @param available
     * @param active
     * @param yearsLeft
     */
    void updateLoan(
        int loanNumber, double newBalance, double interestRate, bool available, bool active, int yearsLeft);

    /**
     * @brief updateBalance
     * @param newAmount
     */
    void updateBalance(double newAmount);

    /**
     * @brief updateStockPriceDisplay
     * @param amount
     * @param stockNumber
     */
    void updateStockPriceDisplay(double amount, int stockNumber);

    /**
     * @brief updateSellingStockPriceDisplay
     * @param amount
     * @param stockNumber
     * @param tooMany
     */
    void updateSellingStockPriceDisplay(double amount, int stockNumber, bool tooMany);

    /**
     * @brief updateStockAmountOwned
     * @param amount
     * @param stockNumber
     */
    void updateStockAmountOwned(uint amount, int stockNumber);

    /**
     * @brief showEndScreen
     * @param questionsAnsweredCorrectly
     * @param moneyEarned
     */
    void showEndScreen(uint questionsAnsweredCorrectly, int moneyEarned);

    /**
     * @brief enableSubmitButton
     * @param checked
     */
    void enableSubmitButton(bool checked);

    /**
     * @brief displayPhone
     */
    void displayPhone();

    /**
     * @brief hidePhone
     */
    void hidePhone();

    /**
     * @brief returnToGame
     * @param currentWidget
     */
    void returnToGame(QWidget *currentWidget);

    /**
     * @brief showErrorMessage
     * @param errorMessage
     */
    void showErrorMessage(QString errorMessage);

    /**
     * @brief revalidateAllStockDisplays
     */
    void revalidateAllStockDisplays();

    /**
     * @brief newYear
     * @param newTotals
     * @param changes
     * @param currentYear
     * @param yearlyBills
     */
    void newYear(QVector<double> newTotals, QVector<double> changes, int currentYear, double yearlyBills);

    /**
     * @brief gameEnded
     * @param reason
     * @param imageName
     */
    void gameEnded(QString reason, QString imageName);

    /**
     * @brief showLifeEvent
     * @param lifeEvent
     */
    void showLifeEvent(LifeEvent lifeEvent);

    /**
     * @brief showWarning
     * @param warning
     * @param image
     */
    void showWarning(QString warning, QString image);

    /**
     * @brief updateCreditScore
     * @param score
     */
    void updateCreditScore(int score);

signals:

    /**
     * @brief requestQuiz
     * @param category
     * @param questionAmount
     */
    void requestQuiz(QuizCategory category, uint questionAmount);

    /**
     * @brief sendAnswer
     * @param answer
     */
    void sendAnswer(std::string answer);

    /**
     * @brief depositToSavings
     * @param amount
     */
    void depositToSavings(double amount);

    /**
     * @brief depositToChecking
     * @param amount
     */
    void depositToChecking(double amount);

    /**
     * @brief depositToCD
     * @param amount
     * @param cdNumber
     */
    void depositToCD(double amount, int cdNumber);

    /**
     * @brief buyStock
     * @param numberOfShares
     * @param stockNumber
     */
    void buyStock(int numberOfShares, int stockNumber);

    /**
     * @brief depositToLoan
     * @param amount
     * @param loanNumber
     */
    void depositToLoan(double amount, int loanNumber);

    /**
     * @brief withdrawFromSavings
     * @param amount
     */
    void withdrawFromSavings(double amount);

    /**
     * @brief withdrawFromChecking
     * @param amount
     */
    void withdrawFromChecking(double amount);

    /**
     * @brief withdrawFromCD
     * @param cdNumber
     */
    void withdrawFromCD(int cdNumber);

    /**
     * @brief sellStock
     * @param numberOfShares
     * @param stockNumber
     */
    void sellStock(int numberOfShares, int stockNumber);

    /**
     * @brief activateLoan
     * @param loanNumber
     */
    void activateLoan(int loanNumber);

    /**
     * @brief nextYear
     */
    void nextYear();

    /**
     * @brief requestPriceOfXStocks
     * @param numberOfShares
     * @param stockNumber
     */
    void requestPriceOfXStocks(int numberOfShares, int stockNumber);

    /**
     * @brief requestSellingPriceOfXStocks
     * @param numberOfShares
     * @param stockNumber
     */
    void requestSellingPriceOfXStocks(int numberOfShares, int stockNumber);

    /**
     * @brief revalidateStockDisplay
     */
    void revalidateStockDisplay();

    /**
     * @brief revalidateSpecificStockDisplay
     * @param amount
     * @param stockNumber
     */
    void revalidateSpecificStockDisplay(int amount, int stockNumber);

    /**
     * @brief settingsOpened
     * @param currentWidget
     */
    void settingsOpened(QWidget *currentWidget);

    /**
     * @brief requestCDInfo
     * @param cdNumber
     */
    void requestCDInfo(int cdNumber);

    /**
     * @brief savingsDepositAmountRead
     * @param amount
     */
    void savingsDepositAmountRead(double amount);

    /**
     * @brief savingsWithdrawAmountRead
     * @param amount
     */
    void savingsWithdrawAmountRead(double amount);

    /**
     * @brief requestLoanInfo
     * @param loanNumber
     */
    void requestLoanInfo(int loanNumber);

    /**
     * @brief requestLifeEvent
     */
    void requestLifeEvent();
};
#endif // MAINWINDOW_H
