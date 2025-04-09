#include "savingsaccount.h"

SavingsAccount::SavingsAccount(double interestRate) : MoneyContainer(), interestRate(interestRate){

}

void SavingsAccount::nextYear() {
    balance = balance + balance * (1 + interestRate);
}

double SavingsAccount::getInterestRate() {
    return interestRate;
}
