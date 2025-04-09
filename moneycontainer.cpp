#include "moneycontainer.h"

MoneyContainer::MoneyContainer()
{
    balance = 0;
}

bool MoneyContainer::deposit(double amount)
{
    balance += amount;
    return true;
}

bool MoneyContainer::withdraw(double amount)
{
    if (balance < amount)
        return false;
    balance -= amount;
    return true;
}

double MoneyContainer::getBalance()
{
    return balance;
}

void MoneyContainer::nextYear() {}
