#ifndef MONEYCONTAINER_H
#define MONEYCONTAINER_H

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
