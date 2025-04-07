#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include "mainmodel.h"
#include "quizhandler.h"
#include "confettiview.h"

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
    ConfettiView* confettiView;

public slots:
    void showQuizData(Question q);
    void onStartClicked();
    void submitHelper();
    void displayResult(bool result, std::string explanation);
    void updateProgress(uint progress);

    void updateSavings(double newBalance, double interestRate);

    void updateCD(int cdNumber, double newBalance, double interestRate, int termlength, double minimumDeposit, int yearsLeft);

    void updateStock(int stockNumber, double newBalance);

    void updateLoan(int loanNumber, double newBalance, double interestRate);

    void updateBalance(double newAmount);

    void showEndScreen();

    void enableSubmitButton(bool checked);

    void displayPhone();

    void hidePhone();

    void returnToGame(QWidget* currentWidget);

    void showErrorMessage(QString errorMessage);

signals:
    void startQuizRequested();
    void sendAnswer(std::string answer);

    void depositToSavings(double amount);

    void depositToCD(double amount, int cdNumber);

    void buyStock(double amount, int stockNumber);

    void depositToLoan(double amount, int loanNumber);

    void withdrawFromSavings(double amount);

    void withdrawFromCD(double amount, int cdNumber);

    void sellStock(double amount, int stockNumber);

    void nextYear();

    void settingsOpened(QWidget* currentWidget);
};
#endif // MAINWINDOW_H
