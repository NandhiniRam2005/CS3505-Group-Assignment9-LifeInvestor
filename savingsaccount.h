#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "moneycontainer.h"

class SavingsAccount : public MoneyContainer
{
private:
    double interestRate;

public:
    SavingsAccount(double interestRate);

    void nextYear() override;
};

#endif // SAVINGSACCOUNT_H
