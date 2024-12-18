#ifndef ATM_SYSTEM_H
#define ATM_SYSTEM_H

#include "Customer.h"
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <stdexcept>

class ATMSystem {
private:
    static const int MAX_CUSTOMERS = 100;
    std::vector<Customer> customers;
    std::stack<std::pair<std::string, std::string>> defaultCredentials;
    std::queue<std::string> accessQueue;
    
    void initializeDefaultCredentials();
    Customer* findCustomer(const std::string& customerId);

public:
    ATMSystem();
    
    bool login(const std::string& customerId, const std::string& password);
    bool registerCustomer(const std::string& name, const std::string& email,
                         const std::string& address, const std::string& phone,
                         const std::string& newPassword);
    
    bool transferMoney(const std::string& fromCustomerId, 
                      const std::string& toCustomerId,
                      double amount, bool fromSavings);
    
    void enqueueCustomer(const std::string& customerId);
    void dequeueCustomer();
    
    Customer* getCurrentCustomer(const std::string& customerId);
};

#endif
