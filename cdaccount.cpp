#include "cdaccount.h"

CDAccount::CDAccount(double interestRate, int yearsRemaining) : MoneyContainer(), interestRate(interestRate), yearsRemaining(yearsRemaining){

}

void CDAccount::nextYear() {
    balance = balance + balance * interestRate;
    if (yearsRemaining > 0)
        yearsRemaining--;
}

double CDAccount::withdraw(double amount) {
    if (yearsRemaining > 0)
        return 0;
    MoneyContainer::withdraw(amount);
}
