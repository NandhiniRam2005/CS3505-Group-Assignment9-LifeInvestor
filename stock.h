#ifndef STOCK_H
#define STOCK_H

#include "moneycontainer.h"
#include <QVector>



class Stock : public MoneyContainer
{
private:
    double value;
    int numberOwned;
    double variance;
    double trend;

public:
    Stock(double value, double variance, double trend);

    void nextYear() override;

    double getValue();

    int getNumberOwned();

    bool deposit(double amount) override;

    bool withdraw(double amount) override;
};

#endif // STOCK_H
