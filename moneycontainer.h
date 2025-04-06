#ifndef MONEYCONTAINER_H
#define MONEYCONTAINER_H

class MoneyContainer
{
protected:
    double balance;

public:
    MoneyContainer();

    double getBalance();

    virtual void deposit(double amount);

    virtual double withdraw(double amount);

    virtual void nextYear();

};

#endif // MONEYCONTAINER_H
