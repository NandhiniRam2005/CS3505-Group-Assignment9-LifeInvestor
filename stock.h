#ifndef STOCK_H
#define STOCK_H

#include "moneycontainer.h"
#include <QVector>



class Stock : public MoneyContainer
{
private:
    double currentValue;
    QVector<double> pastValues;
    // add variables to control how stock changes

public:
    Stock(); // add stock variables

    void nextYear() override;

    double getCurrentValue();

    QVector<double> getPastValues();
};

#endif // STOCK_H
