#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    static const double MIN_SAVINGS_BALANCE;
    static const double MIN_CURRENT_BALANCE;
    static const double SAVINGS_SERVICE_CHARGE;
    static const double CURRENT_SERVICE_CHARGE;
    static const double INITIAL_SAVINGS_BALANCE;
    static const double INITIAL_CURRENT_BALANCE;

    double savingsBalance;
    double currentBalance;

public:
    Account();
    bool withdrawFromSavings(double amount);
    bool withdrawFromCurrent(double amount);
    bool depositToSavings(double amount);
    bool transferBetweenAccounts(double amount, bool fromSavingsToCurrent);
    double getSavingsBalance() const { return savingsBalance; }
    double getCurrentBalance() const { return currentBalance; }
    void setSavingsBalance(double balance) { savingsBalance = balance; }
    void setCurrentBalance(double balance) { currentBalance = balance; }
};

#endif
