#include "stock.h"
#include <QRandomGenerator>


Stock::Stock(double value, double variance, double trend) : MoneyContainer() {
    this->value = value;
    this->variance = variance;
    this->trend = trend;
}

void Stock::nextYear() {
    value *= (trend - variance) + QRandomGenerator::global()->generateDouble() * 2 * variance;
}

double Stock::getValue() {
    return 0;
}
