#include "ATMSystem.h"
#include <algorithm>

ATMSystem::ATMSystem() {
    initializeDefaultCredentials();
}

void ATMSystem::initializeDefaultCredentials() {
    // Initialize with some default customer IDs and passwords
    defaultCredentials.push({"CUST001", "pass001"});
    defaultCredentials.push({"CUST002", "pass002"});
    defaultCredentials.push({"CUST003", "pass003"});
    defaultCredentials.push({"CUST004", "pass004"});
    defaultCredentials.push({"CUST005", "pass005"});
}

Customer* ATMSystem::findCustomer(const std::string& customerId) {
    for (auto& customer : customers) {
        if (customer.getCustomerId() == customerId) {
            return &customer;
        }
    }
    return nullptr;
}

bool ATMSystem::login(const std::string& customerId, const std::string& password) {
    Customer* customer = findCustomer(customerId);
    if (customer && customer->validatePassword(password)) {
        return true;
    }
    return false;
}

bool ATMSystem::registerCustomer(const std::string& name, const std::string& email,
                               const std::string& address, const std::string& phone,
                               const std::string& newPassword) {
    if (defaultCredentials.empty()) {
        throw std::runtime_error("No more default credentials available");
    }
    
    if (customers.size() >= MAX_CUSTOMERS) {
        throw std::runtime_error("Maximum customer limit reached");
    }
    
    auto credentials = defaultCredentials.top();
    defaultCredentials.pop();
    
    Customer newCustomer(credentials.first, newPassword);
    newCustomer.setDetails(name, email, address, phone);
    customers.push_back(newCustomer);
    
    return true;
}

bool ATMSystem::transferMoney(const std::string& fromCustomerId, 
                            const std::string& toCustomerId,
                            double amount, bool fromSavings) {
    Customer* fromCustomer = findCustomer(fromCustomerId);
    Customer* toCustomer = findCustomer(toCustomerId);
    
    if (!fromCustomer || !toCustomer) return false;
    
    Account& fromAccount = fromCustomer->getAccount();
    Account& toAccount = toCustomer->getAccount();
    
    if (fromSavings) {
        if (fromAccount.withdrawFromSavings(amount)) {
            toAccount.depositToSavings(amount);
            return true;
        }
    } else {
        if (fromAccount.withdrawFromCurrent(amount)) {
            toAccount.depositToSavings(amount);
            return true;
        }
    }
    return false;
}

void ATMSystem::enqueueCustomer(const std::string& customerId) {
    accessQueue.push(customerId);
}

void ATMSystem::dequeueCustomer() {
    if (!accessQueue.empty()) {
        accessQueue.pop();
    }
}

Customer* ATMSystem::getCurrentCustomer(const std::string& customerId) {
    if (accessQueue.empty() || accessQueue.front() != customerId) {
        return nullptr;
    }
    return findCustomer(customerId);
}
