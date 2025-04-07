#ifndef STOCK_H
#define STOCK_H

#include "moneycontainer.h"
#include <QVector>



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

};

#endif // STOCK_H
