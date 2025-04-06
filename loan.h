#ifndef LOAN_H
#define LOAN_H

#include "moneycontainer.h"

class Loan : public MoneyContainer
{
private:
    double interestRate;

public:
    Loan(double balance, double interestRate);

    void nextYear() override;
};

#endif // LOAN_H
