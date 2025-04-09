#ifndef CDACCOUNT_H
#define CDACCOUNT_H

#include "moneycontainer.h"

class CDAccount : public MoneyContainer
{
private:
    double interestRate;
    int termLength;
    double minimumDeposit;
    int yearsRemaining;

public:
    CDAccount(double interestRate, int termLength, double minimumDeposit);

    void nextYear() override;

    bool deposit(double amount) override;

    bool withdraw(double amount) override;

    double getInterestRate();

    int getTermLength();

    int getYearsRemaining();

    double getMinimumDeposit();
};

#endif // CDACCOUNT_H
