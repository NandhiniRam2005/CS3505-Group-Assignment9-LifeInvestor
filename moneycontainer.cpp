#include "moneycontainer.h"
#include <cmath>

MoneyContainer::MoneyContainer()
{
    balance = 0;
}

bool MoneyContainer::deposit(double amount)
{
    balance += amount;
    balance = std::floor(balance * 100.0) / 100.0;
    return true;
}

bool MoneyContainer::withdraw(double amount)
{
    if (balance < amount)
        return false;
    balance -= amount;
    balance = std::floor(balance * 100.0) / 100.0;
    return true;
}

double MoneyContainer::getBalance()
{
    return balance;
}

void MoneyContainer::nextYear() {
    balance = std::floor(balance * 100.0) / 100.0;

}
