/*
The source file for MoneyContainer.

This class represents some kind of thing that can hold money in the LifeInvesting application.
It has a balance, which can be changed by depositing or withdrawing, and the value can also change
year-to-year through the nextYear method.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

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
