#ifndef STOCK_H
#define STOCK_H
/*
The header file for Stock.

This class represents a stock, each stock has a value, variance, and trend, which is used to calculate
the value the stock will increase to in the next year. These parameters can be changed to make a stock
'safer' or 'riskier'.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

April 22, 2025
*/
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
