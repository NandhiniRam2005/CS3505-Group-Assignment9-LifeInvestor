#ifndef LOAN_H
#define LOAN_H

#include "moneycontainer.h"

class Loan : public MoneyContainer
{
private:
    double interestRate;

public:
    Loan(double interestRate, double balance);

    bool deposit(double amount) override;

    void nextYear() override;

    double getInterestRate();
};

#endif // LOAN_H
