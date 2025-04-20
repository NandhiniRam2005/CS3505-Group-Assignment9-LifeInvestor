/*
The header file for CDAccount.

This class represents a CD Account. Deposits can be made into the account and the deposit will appreciate with a
given interest rate over a give length of time.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#ifndef CDACCOUNT_H
#define CDACCOUNT_H

#include "moneycontainer.h"

class CDAccount : public MoneyContainer
{
private:
    double interestRate;
    int termLength;
    double minimumDeposit;
    int yearsRemaining;

public:
    /**
     * Creates a CDAccount given an interest rate, term length, and minimum allowed deposit amount.
     * @param interestRate the interest rate of the CD
     * @param termLength the term length of the CD
     * @param minimumDeposit the minimum amount allowed to be deposited in the CD
     */
    CDAccount(double interestRate, int termLength, double minimumDeposit);

    /**
     * This method should be called whenever a new year occurs to ensure
     * that any necessary modifications to the balance of this CD can be performed.
     */
    void nextYear() override;

    /**
     * deposits a given amount of money in this MoneyContainer
     * @param amount the amount to deposit
     * @return true if the deposit was successful, and false otherwise.
     */
    bool deposit(double amount) override;

    /**
     * withdraws a given amount of money from this CD
     * @param amount the amount to withdraw
     * @return true if the withdrawal was successful, and false otherwise.
     */
    bool withdraw(double amount) override;

    /**
     * @return The interest rate of this CD
     */
    double getInterestRate();

    /**
     * @return The term length of this CD
     */
    int getTermLength();

    /**
     * @return The number of years remaining in this CD's term
     */
    int getYearsRemaining();

    /**
     * @return The minimum amount that can be deposited in this CD
     */
    double getMinimumDeposit();
};

#endif
