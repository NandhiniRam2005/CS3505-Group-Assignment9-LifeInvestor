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
    return value;
}

int Stock::getNumberOwned() {
    return numberOwned;
}

bool Stock::deposit(double amount) {
    if ((amount / value) != std::floor(amount / value))
        return false;
    numberOwned += amount / value;
    return MoneyContainer::deposit(amount);
}

bool Stock::withdraw(double amount) {
    if ((amount / value) != std::floor(amount / value))
        return false;
    numberOwned -= amount / value;
    return MoneyContainer::withdraw(amount);
}
