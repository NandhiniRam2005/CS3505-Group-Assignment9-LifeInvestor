#ifndef CDACCOUNT_H
#define CDACCOUNT_H

#include "moneycontainer.h"

class CDAccount : public MoneyContainer
{
private:
    double interestRate;
    // add some withdraw limit IDK how CDs work

public:
    CDAccount(double interestRate);

    void nextYear() override;

    double withdraw(double amount) override;
};

#endif // CDACCOUNT_H
