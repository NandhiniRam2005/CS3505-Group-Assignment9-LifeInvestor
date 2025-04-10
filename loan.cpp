#include "loan.h"
#include "loan.h"

Loan::Loan(double interestRate, double startingBalance, int creditRequirement, int termLength)
    : MoneyContainer()
{
    this->interestRate = interestRate;
    this->startingBalance = -startingBalance;
    this->balance = -startingBalance;
    this->creditRequirement = creditRequirement;
    this->yearsLeft = termLength;
    this->termLength = termLength;
    this->available = false;
    this->active = false;
}

void Loan::nextYear()
{
    if (active) {
        if (balance >= 0) {
            active = false;
            balance = startingBalance;
            yearsLeft = termLength;
        } else {
            balance = balance + balance * interestRate;
            yearsLeft -= 1;
            if (yearsLeft < 0)
                active = false;
        }
    }
}

double Loan::getInterestRate()
{
    return interestRate;
}

int Loan::getYearsLeft()
{
    return yearsLeft;
}

bool Loan::getAvailable()
{
    return available;
}

bool Loan::getActive()
{
    return active;
}

void Loan::setAvailable(int creditScore)
{
    if (!active && creditScore > creditRequirement)
        available = true;
}

bool Loan::activate()
{
    if (available) {
        active = true;
        available = false;
        return true;
    }
    return false;
}

bool Loan::deposit(double amount)
{
    if (!(balance + amount <= 0) || !active)
        return false;
    bool success = MoneyContainer::deposit(amount);
    if (balance > -0.01) {
        active = false;
        balance = startingBalance;
        yearsLeft = termLength;
    }
    return success;
}
