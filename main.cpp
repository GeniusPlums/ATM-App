#include "ATMSystem.h"
#include <iostream>
#include <limits>
#include <string>

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMenu() {
    std::cout << "\nATM Menu:\n";
    std::cout << "1. Check Balance\n";
    std::cout << "2. Withdraw from Savings\n";
    std::cout << "3. Withdraw from Current\n";
    std::cout << "4. Transfer between accounts\n";
    std::cout << "5. Transfer to another customer\n";
    std::cout << "6. Logout\n";
    std::cout << "Enter your choice: ";
}

void handleLogin(ATMSystem& atm) {
    std::string customerId, password;
    std::cout << "Enter Customer ID: ";
    std::cin >> customerId;
    std::cout << "Enter Password: ";
    std::cin >> password;
    
    if (atm.login(customerId, password)) {
        atm.enqueueCustomer(customerId);
        std::cout << "Login successful!\n";
        
        Customer* customer = atm.getCurrentCustomer(customerId);
        if (!customer) {
            std::cout << "System is currently busy. Please try again later.\n";
            return;
        }
        
        bool loggedIn = true;
        while (loggedIn) {
            displayMenu();
            int choice;
            std::cin >> choice;
            clearInputBuffer();
            
            Account& account = customer->getAccount();
            
            switch (choice) {
                case 1: {
                    std::cout << "\nSavings Balance: Rs. " << account.getSavingsBalance() << std::endl;
                    std::cout << "Current Balance: Rs. " << account.getCurrentBalance() << std::endl;
                    break;
                }
                case 2: {
                    double amount;
                    std::cout << "Enter amount to withdraw from savings: ";
                    std::cin >> amount;
                    if (account.withdrawFromSavings(amount)) {
                        std::cout << "Withdrawal successful. New savings balance: Rs. " 
                                << account.getSavingsBalance() << std::endl;
                    } else {
                        std::cout << "Withdrawal failed. Insufficient funds or invalid amount.\n";
                    }
                    break;
                }
                case 3: {
                    double amount;
                    std::cout << "Enter amount to withdraw from current: ";
                    std::cin >> amount;
                    if (account.withdrawFromCurrent(amount)) {
                        std::cout << "Withdrawal successful. New current balance: Rs. " 
                                << account.getCurrentBalance() << std::endl;
                    } else {
                        std::cout << "Withdrawal failed. Insufficient funds or invalid amount.\n";
                    }
                    break;
                }
                case 4: {
                    double amount;
                    char fromAccount;
                    std::cout << "Transfer from (S)avings or (C)urrent account? ";
                    std::cin >> fromAccount;
                    std::cout << "Enter amount to transfer: ";
                    std::cin >> amount;
                    
                    bool success = account.transferBetweenAccounts(amount, 
                        toupper(fromAccount) == 'S');
                    
                    if (success) {
                        std::cout << "Transfer successful.\n";
                        std::cout << "Savings Balance: Rs. " << account.getSavingsBalance() << std::endl;
                        std::cout << "Current Balance: Rs. " << account.getCurrentBalance() << std::endl;
                    } else {
                        std::cout << "Transfer failed. Insufficient funds or invalid amount.\n";
                    }
                    break;
                }
                case 5: {
                    std::string targetId;
                    double amount;
                    char fromAccount;
                    
                    std::cout << "Enter target customer ID: ";
                    std::cin >> targetId;
                    std::cout << "Transfer from (S)avings or (C)urrent account? ";
                    std::cin >> fromAccount;
                    std::cout << "Enter amount to transfer: ";
                    std::cin >> amount;
                    
                    if (atm.transferMoney(customerId, targetId, amount, 
                        toupper(fromAccount) == 'S')) {
                        std::cout << "Transfer successful.\n";
                        std::cout << "Your updated balances:\n";
                        std::cout << "Savings Balance: Rs. " << account.getSavingsBalance() << std::endl;
                        std::cout << "Current Balance: Rs. " << account.getCurrentBalance() << std::endl;
                    } else {
                        std::cout << "Transfer failed. Check the customer ID and your balance.\n";
                    }
                    break;
                }
                case 6: {
                    loggedIn = false;
                    atm.dequeueCustomer();
                    std::cout << "Logged out successfully.\n";
                    break;
                }
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }
        }
    } else {
        std::cout << "Login failed. Invalid credentials.\n";
    }
}

void handleRegistration(ATMSystem& atm) {
    std::string name, email, address, phone, password;
    clearInputBuffer();
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your email: ";
    std::getline(std::cin, email);
    std::cout << "Enter your address: ";
    std::getline(std::cin, address);
    std::cout << "Enter your phone number: ";
    std::getline(std::cin, phone);
    std::cout << "Set your password: ";
    std::getline(std::cin, password);
    
    try {
        if (atm.registerCustomer(name, email, address, phone, password)) {
            std::cout << "Registration successful!\n";
        } else {
            std::cout << "Registration failed.\n";
        }
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    ATMSystem atm;
    
    while (true) {
        std::cout << "\nWelcome to the ATM System\n";
        std::cout << "1. Login\n";
        std::cout << "2. Register\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        
        int choice;
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                handleLogin(atm);
                break;
            case 2:
                handleRegistration(atm);
                break;
            case 3:
                std::cout << "Thank you for using our ATM system. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
