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
    double cdBalance;
    ConfettiView* confettiView;

public slots:
    void showQuizData(Question q);
    void onStartClicked();
    void submitHelper();
    void displayResult(bool result, std::string explanation);
    void updateProgress(uint progress);

    void updateSavingsBalance(double newBalance);

    void updateCDBalance(double newBalance);

    void updateStockBalances(QVector<double> newBalances);

    void updateLoanBalances(QVector<double> newBalances);

    void updateCurrentMoney(double newAmount);

    void showEndScreen();

    void enableSubmitButton(bool checked);

signals:
    void startQuizRequested();
    void sendAnswer(std::string answer);

    void depositToSavings(double amount);

    void depositToCD(double amount);

    void buyStock(double amount, int stockNumber);

    void depositToLoan(double amount, int loanNumber);

    void withdrawFromSavings(double amount);

    void withdrawFromCD(double amount);

    void sellStock(double amount, int stockNumber);

    void withdrawFromLoan(double amount, int loanNumber);

    void nextYear();
};
#endif // MAINWINDOW_H
