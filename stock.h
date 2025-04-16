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
    /**
     * Creates a stock with a given value, variance, and trend
     * @param value the value / price of a share of this stock
     * @param variance the variance in returns for this stock (higher for more volatile returns, lower for more consistent returns)
     * @param trend the trend in returns for this stock (how high the return should be on average)
     */
    Stock(double value, double variance, double trend);

    /**
     * This method should be called whenever a new year occurs to ensure
     * that any necessary modifications to the value of this Stock can be performed.
     */
    void nextYear() override;

    /**
     * @return The current value of one share of this stock
     */
    double getValue();

    /**
     * @return How much money is currently invested in this stock
     */
    double getMoneyBalance();
};

#endif // STOCK_H
