
//zasoby: magazyn, stół, piec, półka, konto piekarni.

#include <thread>
#include <iostream>
#include "Utility.h"
#include "Shelf.h"
#include "Account.h"
#include "Client.h"
#include "Oven.h"
#include "Baker.h"

/*
 * Zasoby:
 * półka - liczba chlebów określonego typu?
 * konto piekarni - double
 */

const int typesOfBakedGoods = 3;
int numberOfClients = 5;
int numberOfBakers = 5;

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
    Utility stockroom;
    Utility table;
    Account account;
    Shelf shelf;
    Oven oven;

    std::vector<Client> clients;
    for (int i = 0; i < numberOfClients; i++){
        clients.emplace_back(Client());
    }
    std::vector<Baker> bakers;
    for (int i = 0; i < numberOfBakers; i++){
        bakers.emplace_back(Baker());
    }

    //START THREADS *************************************************
    for (Client& client: clients){
        client.start(&account, &shelf);
    }
    for (Baker& baker: bakers){
        baker.start(&stockroom, &table, &oven, &shelf);
    }
    std::thread ovenT(ovenThread, &oven);

    // DISPLAY THINGS *************************************************
    int i = 0;
    while (simulationOn){
        coutLock.lock();
        std::cout << shelf.getNumberOfBreads() << " " << shelf.getNumberOfBaguettes() << " "
                  << shelf.getNumberOfCroissants() << " " << account.getBalance() << "    ";
        for (Baker& baker: bakers){
            std::cout << "\t" << baker.getAction() << " " << baker.getProgress() << " " << baker.getNowProducing();
        }
        std::cout << "     Q: ";
        for (int id : Client::queue){
            std::cout << id << " ";
        }
        std::cout << std::endl;
        coutLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (i++ > 10){
            simulationOn = false;
        }
    }

    // STOP THREADS *************************************************
    for (Client& client: clients){
        client.stop();
    }
    for (Baker& baker: bakers){
        baker.stop();
    }
    oven.stop();
    ovenT.join();

    return 0;
}