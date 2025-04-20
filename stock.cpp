/*
The source file for Stock.

This class represents a stock, each stock has a value, variance, and trend, which is used to calculate
the value the stock will increase to in the next year. These parameters can be changed to make a stock
'safer' or 'riskier'.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan,
Jake Heairld, Joseph Hamilton

Reviewed by Nandhini Ramanathan

April 22, 2025
*/

#include "stock.h"
#include <QRandomGenerator>

Stock::Stock(double value, double variance, double trend)
    : MoneyContainer()
{
    this->value = value;
    this->variance = variance;
    this->trend = trend;
}

void Stock::nextYear()
{
    value *= (trend - variance) + QRandomGenerator::global()->generateDouble() * 2 * variance;
    MoneyContainer::nextYear();
}

double Stock::getValue()
{
    return value;
}

double Stock::getMoneyBalance()
{
    return value * balance;
}
