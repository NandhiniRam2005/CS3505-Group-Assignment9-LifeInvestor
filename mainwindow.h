#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QSoundEffect>
#include "animationview.h"
#include "depositwindow.h"
#include "mainmodel.h"
#include "quizhandler.h"

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
    QSoundEffect *levelPassSound;
    DepositWindow depositWindow;

    QString generateReportString(QVector<double> newTotals, QVector<double> changes);

public slots:
    void showQuizData(Question q);
    void onStartClicked();
    void submitHelper();
    void displayResult(bool result, std::string explanation);
    void updateProgress(uint progress);

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

    void updateBalance(double newAmount);

    void updateStockPriceDisplay(double amount, int stockNumber);

    void updateSellingStockPriceDisplay(double amount, int stockNumber, bool tooMany);

    void updateStockAmountOwned(uint amount, int stockNumber);

    void showEndScreen();

    void enableSubmitButton(bool checked);

    void displayPhone();

    void hidePhone();

    void returnToGame(QWidget *currentWidget);

    void showErrorMessage(QString errorMessage);

    void revalidateAllStockDisplays();
    void displayDepositPage();
    void readSavingsAmount();

    void newYear(QVector<double> newTotals, QVector<double> changes);

signals:
    void startQuizRequested();
    void sendAnswer(std::string answer);

    void depositToSavings(double amount);

    void depositToCD(double amount, int cdNumber);

    void buyStock(int numberOfShares, int stockNumber);

    void depositToLoan(double amount, int loanNumber);

    void withdrawFromSavings(double amount);

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
    void amountRead(int amount);
};
#endif // MAINWINDOW_H
