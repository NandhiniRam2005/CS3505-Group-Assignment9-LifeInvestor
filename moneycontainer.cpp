#include "moneycontainer.h"

MoneyContainer::MoneyContainer() {}

void MoneyContainer::deposit(double amount) {
    balance += amount;
}

double MoneyContainer::withdraw(double amount) {
    if (balance < amount)
        amount -= balance;
    balance -= amount;
    return amount;
}

double MoneyContainer::getBalance() {
    return balance;
}

void MoneyContainer::nextYear() {

}
