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
    Ui::MainWindow *ui;
    QButtonGroup *buttonGroup;
    Question currentQuestion;

    double currentMoney;

    QVector<double> stockBalances;
    QVector<double> loanBalances;
    double savingsBalance;
    QVector<double> cdBalances;
    AnimationView *animationView;
    StartScreenView *startScreenView;
    QSoundEffect *levelPassSound;
    QSoundEffect *levelFailSound;
    QSoundEffect *depositSound;
    LifeEventDisplay lifeEventDisplay;
    warningdisplay warningDisplay;

    QString generateReportString(QVector<double> newTotals, QVector<double> changes);

    QuizCategory quizCategory;
    uint quizLength;

    bool firstStart;

    void generalUISetup();

    void setUpGifs();

    void setupAudio();

    void enableQuizSubmission();

    void depositingConnectionWindowToModel(MainModel *model);

    void withdrawingConnectionsWindowToModel(MainModel *model);

    void buyingStockUIConnections();

    void sellingStockUIConnections();

    void visualIUpdatesStockConnections(MainModel *model);

    void cdPageConnections(MainModel *model);

    void savingsPageConnections(MainModel *model);

    void loansPageConnections(MainModel *model);

    void casinoPageConnections(MainModel *model);

    void nextYearConnections(MainModel *model);

    void phoneConnections();

    void settingsConnections(MainModel *model);

    void extraQuizesPageConnections(MainModel *model);

    void quizConnections(MainModel *model);

    void mainWindowValueUpdateConnections(MainModel *model);

public slots:
    void startQuiz(QuizCategory category, uint questionAmount);
    void showQuizData(Question q);
    void onStartClicked();
    void submitHelper();
    void displayResult(bool result, std::string explanation);
    void updateProgress(uint progress);
    void updateQuizInfo(QuizInfo qI);
    void updateNetWorth(double netWorth);

    void updateSavings(double newBalance, double interestRate);

    //void updateChecking(double newBalance);

    void updateCD(int cdNumber,
                  double newBalance,
                  double interestRate,
                  int termlength,
                  double minimumDeposit,
                  int yearsLeft);

    void updateStock(int stockNumber, double newBalance);

    void updateStockImage(bool stockOneUp, bool stockTwoUp, bool stockThreeUp);

    void updateLoan(
        int loanNumber, double newBalance, double interestRate, bool available, bool active, int yearsLeft);

    void updateBalance(double newAmount);

    void updateStockPriceDisplay(double amount, int stockNumber);

    void updateSellingStockPriceDisplay(double amount, int stockNumber, bool tooMany);

    void updateStockAmountOwned(uint amount, int stockNumber);

    void showEndScreen(uint questionsAnsweredCorrectly, int moneyEarned);

    void enableSubmitButton(bool checked);

    void displayPhone();

    void hidePhone();

    void returnToGame(QWidget *currentWidget);

    void showErrorMessage(QString errorMessage);

    void revalidateAllStockDisplays();

    void newYear(QVector<double> newTotals, QVector<double> changes, int currentYear, double yearlyBills);

    void gameEnded(QString reason, QString imageName);
    void showLifeEvent(LifeEvent lifeEvent);

    void showWarning(QString warning, QString image);
    void updateCreditScore(int score);

signals:

    void requestQuiz(QuizCategory category, uint questionAmount);
    void sendAnswer(std::string answer);

    void depositToSavings(double amount);

    void depositToChecking(double amount);

    void depositToCD(double amount, int cdNumber);

    void buyStock(int numberOfShares, int stockNumber);

    void depositToLoan(double amount, int loanNumber);

    void withdrawFromSavings(double amount);

    void withdrawFromChecking(double amount);

    void withdrawFromCD(int cdNumber);

    void sellStock(int numberOfShares, int stockNumber);

    void activateLoan(int loanNumber);

    void nextYear();

    void requestPriceOfXStocks(int numberOfShares, int stockNumber);

    void requestSellingPriceOfXStocks(int numberOfShares, int stockNumber);

    void revalidateStockDisplay();

    void revalidateSpecificStockDisplay(int amount, int stockNumber);

    void settingsOpened(QWidget *currentWidget);

    void requestCDInfo(int cdNumber);
    void savingsDepositAmountRead(double amount);
    void savingsWithdrawAmountRead(double amount);

    void requestLoanInfo(int loanNumber);
    void requestLifeEvent();
};
#endif // MAINWINDOW_H
