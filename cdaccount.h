#ifndef CDACCOUNT_H
#define CDACCOUNT_H

#include "moneycontainer.h"

class CDAccount : public MoneyContainer
{
private:
    double interestRate;
    int yearsRemaining;

public:
    CDAccount(double interestRate, int yearsRemaining);

    void nextYear() override;

    double withdraw(double amount) override;
};

#endif // CDACCOUNT_H
