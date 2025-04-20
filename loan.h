/*
The header file for Loan.

This class represents a Loan. Loans are given a starting balance, interest rate, minimum credit amount, and amount of years left
to pay off. Loans will increase in balance each year until the loan is fully paid off, or until there are no more years left to
pay off the loan.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#ifndef LOAN_H
#define LOAN_H

#include "moneycontainer.h"
#include <QDebug>

class Loan : public MoneyContainer
{
private:
    double interestRate;
    double startingBalance;
    int creditRequirement;
    int yearsLeft;
    int termLength;
    bool available;
    bool active;

public:
    /**
     * Creates a new loan given a interest rate, starting balance, credit requirement, and number of years left
     * @param interestRate The interest rate on the loan
     * @param startingBalance The starting balance of the loan
     * @param creditRequirement The minimum credit score needed to take out this loan
     * @param yearsLeft The number of years remaining to pay off this loan
     */
    Loan(double interestRate, double startingBalance, int creditRequirement, int yearsLeft);

    /**
     * Pays part of this loan off, reducing its balance.
     * @param amount The amount to pay
     * @return true if the amount was successfully paid, false if something went wrong, like paying a negative amount, the loan not being active, etc.
     */
    bool deposit(double amount) override;

    /**
     * This method should be called whenever a new year occurs to ensure
     * that any necessary modifications to the balance of this Loan can be performed.
     */
    void nextYear() override;

    /**
     * @return the interest rate on this loan
     */
    double getInterestRate();

    /**
     * @return The number of years left to pay off this loan
     */
    int getYearsLeft();

    /**
     * @return true if this loan is available to take out, otherwise false
     */
    bool getAvailable();

    /**
     * @return true if the user has currently taken out this loan, otherwise false
     */
    bool getActive();

    /**
     * Sets this loan to be available if the user meets the credit score requirement
     * @param creditScore The credit score of the user
     */
    void setAvailable(int creditScore);

    /**
     * Activates / takes out this loan
     * @return True if it was successfully activated, false it the loan is not available
     */
    bool activate();
};

#endif
