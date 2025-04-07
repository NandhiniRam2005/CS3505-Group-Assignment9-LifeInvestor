#ifndef CDACCOUNT_H
#define CDACCOUNT_H

#include "moneycontainer.h"

class CDAccount : public MoneyContainer
{
private:
    double interestRate;
    int termLength;
    int yearsRemaining;

public:
    CDAccount(double interestRate, int termLength);

    void nextYear() override;

    void deposit(double amount) override;

    double withdraw(double amount) override;

    int getTermLength();

    int getYearsRemaining();
};

#endif // CDACCOUNT_H
