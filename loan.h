#ifndef LOAN_H
#define LOAN_H

#include "moneycontainer.h"
#include <QDebug>

class Loan : public MoneyContainer
{
private:
    double interestRate;
    double startingBalance;
    int creditRequirement;
    int yearsLeft;
    int termLength;
    bool available;
    bool active;

public:
    Loan(double interestRate, double startingBalance, int creditRequirement, int yearsLeft);

    bool deposit(double amount) override;

    void nextYear() override;

    double getInterestRate();

    int getYearsLeft();

    bool getAvailable();

    bool getActive();

    void setAvailable(int creditScore);

    bool activate();
};

#endif // LOAN_H
