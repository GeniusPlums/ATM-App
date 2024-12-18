#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Account.h"
#include <string>

class Customer {
private:
    std::string customerId;
    std::string password;
    std::string name;
    std::string email;
    std::string address;
    std::string phoneNumber;
    Account account;

public:
    Customer() = default;
    Customer(const std::string& id, const std::string& pwd);
    
    void setDetails(const std::string& n, const std::string& e, 
                   const std::string& addr, const std::string& phone);
    void setPassword(const std::string& pwd) { password = pwd; }
    bool validatePassword(const std::string& pwd) const { return password == pwd; }
    
    const std::string& getCustomerId() const { return customerId; }
    Account& getAccount() { return account; }
    const std::string& getName() const { return name; }
    
    void setCustomerId(const std::string& id) { customerId = id; }
};

#endif
