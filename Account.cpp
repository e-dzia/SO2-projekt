#include "Account.h"

Account::Account(){
    std::lock_guard<std::mutex> guard(account);
    balance = 0;
}

void Account::pay(double amount) {
    std::lock_guard<std::mutex> guard(account);
    balance += amount;
}

double Account::getBalance() {
    std::lock_guard<std::mutex> guard(account);
    return balance;
}
