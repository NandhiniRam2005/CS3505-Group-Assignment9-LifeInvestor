#ifndef MONEYCONTAINER_H
#define MONEYCONTAINER_H

/*
The header file for MoneyContainer.

This class represents some kind of thing that can hold money in the LifeInvesting application.
It has a balance, which can be changed by depositing or withdrawing, and the value can also change
year-to-year through the nextYear method.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/
class MoneyContainer
{
protected:
    double balance;

public:
    MoneyContainer();

    double getBalance();

    // returns true if the deposit was successful
    virtual bool deposit(double amount);

    // returns true if the withdraw was successful
    virtual bool withdraw(double amount);

    virtual void nextYear();
};

#endif // MONEYCONTAINER_H
