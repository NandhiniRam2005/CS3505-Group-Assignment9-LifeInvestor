#include "cdaccount.h"

CDAccount::CDAccount(double interestRate, int termLength) : MoneyContainer(), interestRate(interestRate), termLength(termLength){
    yearsRemaining = 0;
}

void CDAccount::nextYear() {
    balance = balance + balance * interestRate;
    if (yearsRemaining > 0)
        yearsRemaining--;
}

double CDAccount::withdraw(double amount) {
    if (yearsRemaining > 0)
        return 0;
    return MoneyContainer::withdraw(amount);
}

void CDAccount::deposit(double amount) {
    if (yearsRemaining == 0 && balance == 0) {
        MoneyContainer::deposit(amount);
        yearsRemaining = termLength;
    }
}

int CDAccount::getTermLength() {
    return termLength;
}

int CDAccount::getYearsRemaining() {
    return yearsRemaining;
}
