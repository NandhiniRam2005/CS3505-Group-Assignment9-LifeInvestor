#ifndef BANK_H
#define BANK_H

#include <QObject>

class Bank
{
public:
    Bank();
    int depositIntoSavings(int depositAmount);
    int withdrawFromSavings(int withDrawAmount);
    int depositIntoChecking(int depositAmount);
    int withDrawFromChecking(int withDrawAmount);

private:
    int totalMoney;
    int savingsAccountMoney;
    int checkingAccountMoney;
};

#endif // BANK_H
