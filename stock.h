#ifndef STOCK_H
#define STOCK_H

#include <QVector>
#include "moneycontainer.h"

class Stock : public MoneyContainer
{
private:
    double value;
    double variance;
    double trend;

public:
    Stock(double value, double variance, double trend);

    void nextYear() override;

    double getValue();

    double getMoneyBalance();
};

#endif // STOCK_H
