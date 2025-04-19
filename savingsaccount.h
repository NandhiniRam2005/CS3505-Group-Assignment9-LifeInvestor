/*
The header file for Savings account.

This class represents a savings account. It has an interest rate and will
update the balance by that interest rate every year.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "moneycontainer.h"

class SavingsAccount : public MoneyContainer
{
private:
    double interestRate;

public:
    /**
     * Creates a savings account with a balance of 0 and a given interest rate
     * @param interestRate the interest rate on the account
     */
    SavingsAccount(double interestRate);

    /**
     * @return The interest rate of this Savings Account
     */
    double getInterestRate();

    /**
     * This method should be called whenever a new year occurs to ensure
     * that any necessary modifications to the balance of this SavingsAccount can be performed.
     */
    void nextYear() override;
};

#endif
