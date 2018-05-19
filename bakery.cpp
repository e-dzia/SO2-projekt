#include <thread>
#include <iostream>
#include <ncurses.h>
#include "Utility.h"
#include "Shelf.h"
#include "Account.h"
#include "Client.h"
#include "Oven.h"
#include "Baker.h"

const int typesOfBakedGoods = 3;
int numberOfClients = 5;
int numberOfBakers = 5;

bool simulationOn = true;

void ovenThread(Oven *oven){
    oven->live();
}

void getQ(){
    char esc = getch();
    while (esc != 'q'){
        esc = getch();
    }
    simulationOn = false;
}

int main(){
	// START NCURSES *************************************************
	initscr();
    noecho();
    nodelay(stdscr, TRUE);

    start_color();
    init_pair( 1, COLOR_RED, COLOR_BLACK );
    init_pair( 2, COLOR_GREEN, COLOR_BLACK);
    init_pair( 3, COLOR_CYAN, COLOR_BLACK);

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
    std::thread end(getQ);

    // DISPLAY THINGS *************************************************
    while (simulationOn){
        std::cout << shelf.getNumberOfBreads() << " " << shelf.getNumberOfBaguettes() << " "
                  << shelf.getNumberOfCroissants() << " " << account.getBalance() << "    ";
        for (Baker& baker: bakers){
            std::cout << "\t" << baker.getAction() << " " << baker.getProgress() << " " << baker.getNowProducing()<< " " << baker.isAlive();
        }
        std::cout << "     Q: ";
        for (int id : Client::queue){
            std::cout << id << " ";
        }
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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

	// END NCURSES *************************************************
    endwin();

    return 0;
}
