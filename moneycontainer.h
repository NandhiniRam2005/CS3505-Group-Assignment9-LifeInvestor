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
    /**
     * holds the current amount held in this MoneyContainer
     */
    double balance;

public:
    /**
     * Creates a MoneyContainer with a balance of 0
     */
    MoneyContainer();

    /**
     * @return the current balance of this MoneyContainer
     */
    double getBalance();

    /**
     * deposits a given amount of money in this MoneyContainer
     * @param amount the amount to deposit
     * @return true if the deposit was sucessful, and false otherwise.
     */
    virtual bool deposit(double amount);

    /**
     * withdraws a given amount of money from this MoneyContainer
     * @param amount the amount to withdraw
     * @return true if the withdrawal was sucessful, and false otherwise.
     */
    virtual bool withdraw(double amount);

    /**
     * This method should be callled whenever a new year occurs to ensure
     * that any necessary modifications to the balance of this MoneyContainer can be performed.
     */
    virtual void nextYear();
};

#endif // MONEYCONTAINER_H
