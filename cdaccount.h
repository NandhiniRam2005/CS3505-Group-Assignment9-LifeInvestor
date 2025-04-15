#ifndef CDACCOUNT_H
#define CDACCOUNT_H
/*
The header file for CDAccount.

This class represents a CD Account. Deposits can be made into the account and the deposit will appreciate with a
given interest rate over a give length of time.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/
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
