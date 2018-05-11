#include "Account.h"

Account::Account(){
    balance = 0;
}

void Account::pay(double amount) {
    std::lock_guard<std::mutex> guard(account);
    balance += amount;
}

double Account::getBalance() const {
    return balance;
}