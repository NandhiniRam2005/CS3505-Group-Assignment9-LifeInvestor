#include "savingsaccount.h"

SavingsAccount::SavingsAccount(double interestRate)
    : MoneyContainer()
    , interestRate(interestRate)
{}

void SavingsAccount::nextYear()
{
    balance = balance + balance * interestRate;
    MoneyContainer::nextYear();
}

double SavingsAccount::getInterestRate()
{
    return interestRate;
}
