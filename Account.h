#ifndef BAKERY_ACCOUNT_H
#define BAKERY_ACCOUNT_H


#include <mutex>

class Account {
    double balance;
    std::mutex balanceMutex;

public:
    Account();
    Account(const Account& account) = delete;
    Account& operator=(Account const&) = delete;

    void pay(double amount);

    double getBalance();
};


#endif //BAKERY_ACCOUNT_H
