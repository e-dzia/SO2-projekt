#include "Account.h"

Account::Account(){
    std::lock_guard<std::mutex> guard(balanceMutex);
    balance = 0;
}

void Account::pay(double amount) {
    std::lock_guard<std::mutex> guard(balanceMutex);
    balance += amount;
}

double Account::getBalance() {
    std::lock_guard<std::mutex> guard(balanceMutex);
    return balance;
}
