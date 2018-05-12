
//zasoby: magazyn, stół, piec, półka, konto piekarni.

#include <thread>
#include <iostream>
#include "Utility.h"
#include "Shelf.h"
#include "Account.h"
#include "Client.h"
#include "Oven.h"

/*
 * Zasoby:
 * półka - liczba chlebów określonego typu?
 * konto piekarni - double
 */

const int typesOfBakedGoods = 3;
int numberOfClients = 5;

std::mutex coutLock;

bool simulationOn = true;

void produceBread(Shelf *shelf, Oven *oven){
    for (int i = 0; i < 100; i ++){
        for (int j = 0; j < typesOfBakedGoods; j++){
            oven->putIn(j);
        }
        for (int j = 0; j < typesOfBakedGoods; j++){
            shelf->addBread(j, oven->takeOut(j));
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ovenThread(Oven *oven){
    oven->live();
}

/*void consumeBread(Shelf* shelf, Account * account){
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
}*/

int main(){
    // CREATE VARIABLES *************************************************
    Utility table;
    Utility stockroom;
    Account account;
    Shelf shelf;
    Oven oven;
    std::vector<Client> clients;
    for (int i = 0; i < numberOfClients; i++){
        clients.emplace_back(Client());
    }

    //START THREADS *************************************************
    for (Client& client: clients){
        client.start(&account, &shelf);
    }
    std::thread put(produceBread, &shelf, &oven);
    std::thread produce(ovenThread, &oven);

    // DISPLAY THINGS *************************************************
    int i = 0;
    while (simulationOn){
        coutLock.lock();
        std::cout << shelf.getNumberOfBreads() << " " << shelf.getNumberOfBaguettes() << " "
                  << shelf.getNumberOfCroissants() << " " << account.getBalance() << "    ";
        /*for (Client& client: clients){
            std::cout << "\t" << client.getAction() << " " << client.getProgress() << " " << client.getShoppingList();
        }
        std::cout << "     ";*/
        for (int id : Client::queue){
            std::cout << id << " ";
        }
        std::cout << std::endl;
        coutLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (i++ > 100){
            simulationOn = false;
        }
    }

    // STOP THREADS *************************************************
    oven.stop();
    produce.join();
    put.join();
    for (Client& client: clients){
        client.stop();
    }

    return 0;
}