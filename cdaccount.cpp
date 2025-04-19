/*
The source file for CDAccount.

This class represents a CD Account. Deposits can be made into the account and the deposit will appreciate with a
given interest rate over a give length of time.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include "cdaccount.h"

CDAccount::CDAccount(double interestRate, int termLength, double minimumDeposit)
    : MoneyContainer()
{
    this->interestRate = interestRate;
    this->termLength = termLength;
    this->minimumDeposit = minimumDeposit;
    yearsRemaining = 0;
    balance = 0.0;
}

void CDAccount::nextYear()
{
    balance = balance + balance * interestRate;
    if (yearsRemaining > 0)
        yearsRemaining--;
    MoneyContainer::nextYear();
}

bool CDAccount::withdraw(double amount)
{
    if (yearsRemaining > 0)
        return false;
    return MoneyContainer::withdraw(amount);
}

bool CDAccount::deposit(double amount)
{
    if (yearsRemaining == 0 && balance == 0 && amount >= minimumDeposit) {
        yearsRemaining = termLength;
        return MoneyContainer::deposit(amount);
    }
    return false;
}

double CDAccount::getInterestRate()
{
    return interestRate;
}

int CDAccount::getTermLength()
{
    return termLength;
}

int CDAccount::getYearsRemaining()
{
    return yearsRemaining;
}

double CDAccount::getMinimumDeposit()
{
    return minimumDeposit;
}
