#include "loan.h"

Loan::Loan(double startingBalance, double interestRate) : MoneyContainer(), interestRate(interestRate){
    this->balance = startingBalance;
}

void Loan::nextYear() {

}
