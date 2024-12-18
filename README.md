# ATM Application

A C++ ATM system that manages savings and current accounts with various banking operations.

## Features

- Two types of accounts: Savings and Current
- Minimum balance requirements
  - Savings Account: Rs. 1000
  - Current Account: Rs. 5000
- Service charges for below minimum balance
  - Savings Account: Rs. 50
  - Current Account: Rs. 250
- User authentication system
- Account registration system
- Queue-based system access
- Stack-based default credentials
- Transfer operations between accounts
- Comprehensive error handling

## Building the Project

Compile using g++:

```bash
g++ main.cpp Account.cpp Customer.cpp ATMSystem.cpp -o atm
```

## Usage

Run the compiled executable and follow the on-screen menu to:
1. Login with existing credentials
2. Register as a new customer
3. Perform various banking operations
