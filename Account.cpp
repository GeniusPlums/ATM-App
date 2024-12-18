#include "Account.h"

const double Account::MIN_SAVINGS_BALANCE = 1000.0;
const double Account::MIN_CURRENT_BALANCE = 5000.0;
const double Account::SAVINGS_SERVICE_CHARGE = 50.0;
const double Account::CURRENT_SERVICE_CHARGE = 250.0;
const double Account::INITIAL_SAVINGS_BALANCE = 10000.0;
const double Account::INITIAL_CURRENT_BALANCE = 25000.0;

Account::Account() : savingsBalance(INITIAL_SAVINGS_BALANCE), currentBalance(INITIAL_CURRENT_BALANCE) {}

bool Account::withdrawFromSavings(double amount) {
    if (amount <= 0) return false;
    
    double totalDeduction = amount;
    if (savingsBalance - amount < MIN_SAVINGS_BALANCE) {
        totalDeduction += SAVINGS_SERVICE_CHARGE;
    }
    
    if (savingsBalance >= totalDeduction) {
        savingsBalance -= totalDeduction;
        return true;
    }
    return false;
}

bool Account::withdrawFromCurrent(double amount) {
    if (amount <= 0) return false;
    
    double totalDeduction = amount;
    if (currentBalance - amount < MIN_CURRENT_BALANCE) {
        totalDeduction += CURRENT_SERVICE_CHARGE;
    }
    
    if (currentBalance >= totalDeduction) {
        currentBalance -= totalDeduction;
        return true;
    }
    return false;
}

bool Account::depositToSavings(double amount) {
    if (amount <= 0) return false;
    savingsBalance += amount;
    return true;
}

bool Account::transferBetweenAccounts(double amount, bool fromSavingsToCurrent) {
    if (amount <= 0) return false;
    
    if (fromSavingsToCurrent) {
        if (withdrawFromSavings(amount)) {
            currentBalance += amount;
            return true;
        }
    } else {
        if (withdrawFromCurrent(amount)) {
            savingsBalance += amount;
            return true;
        }
    }
    return false;
}
