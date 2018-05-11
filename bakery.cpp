
//zasoby: magazyn, stół, piec, półka, konto piekarni.

#include <thread>
#include <iostream>
#include "Utility.h"
#include "Shelf.h"
#include "Account.h"
#include "Client.h"

/*
 * Zasoby:
 * półka - liczba chlebów określonego typu?
 * konto piekarni - double
 */

const int typesOfBakedGoods = 3;
double bakedGoodPrices[typesOfBakedGoods] = {1.57, 2.34, 3.28};

std::mutex coutLock;

void produceBread(Shelf *shelf){
    for (int i = 0; i < 10; i ++){
        coutLock.lock();
        std::cout << std::this_thread::get_id() << " " << shelf->getNumberOfBreads() << " "
                  << shelf->getNumberOfBaguettes() << " " << shelf->getNumberOfCroissants() << std::endl;
        coutLock.unlock();
        shelf->addBread(0);
        shelf->addBread(1);
        shelf->addBread(2);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumeBread(Shelf* shelf, Account * account){
    for (int i = 0; i < 10; i ++){
        coutLock.lock();
        std::cout << std::this_thread::get_id() << " " << shelf->getNumberOfBreads() << " "
                  << shelf->getNumberOfBaguettes() << " " << shelf->getNumberOfCroissants() << " " << account->getBalance() << std::endl;
        coutLock.unlock();
        if (shelf->takeBread(0)){
            account->pay(bakedGoodPrices[0]);
        }
        if (shelf->takeBread(1)){
            account->pay(bakedGoodPrices[1]);
        }
        if (shelf->takeBread(2)){
            account->pay(bakedGoodPrices[2]);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(){
    Utility table;
    Utility stockroom;
    Account account;
    Shelf shelf;
    Client client;

    std::thread t1(client.live, &account, &shelf);
    std::thread t2(produceBread, &shelf);

    t1.join();
    t2.join();

    return 0;
}