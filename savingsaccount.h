#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
/*
The header file for Savings account.

This class represents a savings account. It has an interest rate and will
update the balance by that interest rate every year.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/
#include "moneycontainer.h"

class SavingsAccount : public MoneyContainer
{
private:
    double interestRate;

public:
    SavingsAccount(double interestRate);

    double getInterestRate();

    void nextYear() override;
};

#endif // SAVINGSACCOUNT_H
