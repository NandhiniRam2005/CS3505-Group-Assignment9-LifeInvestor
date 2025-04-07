#include "loan.h"

Loan::Loan(double interestRate, double balance) : MoneyContainer(), interestRate(interestRate){
    this->balance = balance;
}

void Loan::nextYear() {
    balance = balance + balance * interestRate;
}

bool Loan::deposit(double amount) {
    if (balance + amount > 0)
        return false;
    return MoneyContainer::deposit(amount);
}
