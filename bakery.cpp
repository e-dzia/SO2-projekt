
//zasoby: magazyn, stół, piec, półka, konto piekarni.

#include <thread>
#include <iostream>
#include "Utility.h"
#include "Shelf.h"
#include "Account.h"
#include "Client.h"
#include "Oven.h"
#include "Baker.h"

const int typesOfBakedGoods = 3;
int numberOfClients = 5;
int numberOfBakers = 5;

std::mutex coutLock;

bool simulationOn = true;

void ovenThread(Oven *oven){
    oven->live();
}

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
        /*for (Baker& baker: bakers){
            std::cout << "\t" << baker.getId() << " " << baker.getAction() << " " << baker.getProgress() << " " << baker.getNowProducing();
        }*/
        std::cout << "     S: ";
        for (int id : Baker::queueStockroom){
            std::cout << id << " ";
        }
        std::cout << "     T: ";
        for (int id : Baker::queueTable){
            std::cout << id << " ";
        }
        std::cout << "     O: ";
        for (int id : Baker::queueOven){
            std::cout << id << " ";
        }
        std::cout << "     Q: ";
        for (int id : Client::queue){
            std::cout << id << " ";
        }
        std::cout << std::endl;
        coutLock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (i++ > 1000){
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