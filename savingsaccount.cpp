/*
The source file for Savings account.

This class represents a savings account. It has an interest rate and will
update the balance by that interest rate every year.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include "savingsaccount.h"

SavingsAccount::SavingsAccount(double interestRate)
    : MoneyContainer()
    , interestRate(interestRate)
{
}

void SavingsAccount::nextYear()
{
    balance = balance + balance * interestRate;
    MoneyContainer::nextYear();
}

double SavingsAccount::getInterestRate()
{
    return interestRate;
}
