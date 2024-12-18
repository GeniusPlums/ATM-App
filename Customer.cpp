#include "Customer.h"

Customer::Customer(const std::string& id, const std::string& pwd) 
    : customerId(id), password(pwd) {}

void Customer::setDetails(const std::string& n, const std::string& e, 
                         const std::string& addr, const std::string& phone) {
    name = n;
    email = e;
    address = addr;
    phoneNumber = phone;
}
