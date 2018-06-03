#include <thread>
#include <iostream>
#include <ncurses.h>
#include "Utility.h"
#include "Shelf.h"
#include "Account.h"
#include "Client.h"
#include "Oven.h"
#include "Baker.h"

const int numberOfClients = 10;
const int numberOfBakers = 7;

bool simulationOn = true;
const int typesOfBakedGoods = 3;

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

void displayObjects(){ 
    attron(A_BOLD);
    mvprintw(0, 5, "STOCKROOM");
    mvprintw(0, 20, "TABLE");
    mvprintw(0, 35, "OVEN");
    mvprintw(0, 45, "ACCOUNT");
    mvprintw(0, 60, "INSIDE OVEN:");
    
    attron( COLOR_PAIR( 1 ) ); 
    mvprintw(9, 15, "breads");
    attroff( COLOR_PAIR( 1 ) ); 
    
    attron( COLOR_PAIR( 2 ) ); 
    mvprintw(9, 25, "baguettes");
    attroff( COLOR_PAIR( 2 ) ); 
    
    attron( COLOR_PAIR( 3 ) ); 
    mvprintw(9, 35, "croissants");
    attroff( COLOR_PAIR( 3 ) ); 
    
    mvprintw(10, 0, "SHELF");
    attroff(A_BOLD);
}

int main(){
	// START NCURSES *************************************************
	initscr();
    noecho();
    nodelay(stdscr, TRUE);

    start_color();
    init_pair( 1, COLOR_RED, COLOR_BLACK ); //bread
    init_pair( 2, COLOR_GREEN, COLOR_BLACK); //baguette
    init_pair( 3, COLOR_CYAN, COLOR_BLACK); //croissant

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
        clear();
        refresh();
        displayObjects();
        mvprintw(1, 45, std::to_string(account.getBalance()).c_str());
        
        // QUEUE STOCKROOM
        int line = 1;
        for (int i = 0; i < Baker::queueStockroom.size(); i++){
                int colour = -1;
                switch (bakers[Baker::queueStockroom.at(i)].getNowProducing()){
                    case 0:
                        colour = 1;
                        break;
                    case 1:
                        colour = 2;
                        break;
                    case 2:
                        colour = 3;
                        break;
                    default:
                        break;
                        
                }
                attron( COLOR_PAIR( colour ) ); 
                mvprintw(line++, 5, std::to_string(Baker::queueStockroom.at(i)).c_str());
                attroff( COLOR_PAIR( colour ) ); 
                if (i == 0){
                    mvprintw(line-1, 7, std::to_string(bakers[Baker::queueStockroom.at(i)].getProgress()).c_str());
                }
        }
        
        // QUEUE TABLE
        line = 1;
        for (int i = 0; i < Baker::queueTable.size(); i++){
                int colour = -1;
                switch (bakers[Baker::queueTable.at(i)].getNowProducing()){
                    case 0:
                        colour = 1;
                        break;
                    case 1:
                        colour = 2;
                        break;
                    case 2:
                        colour = 3;
                        break;
                    default:
                        break;
                        
                }
                attron( COLOR_PAIR( colour ) ); 
                mvprintw(line++, 20, std::to_string(Baker::queueTable.at(i)).c_str());
                attroff( COLOR_PAIR( colour ) ); 
                if (i == 0){
                    mvprintw(line-1, 22, std::to_string(bakers[Baker::queueTable.at(i)].getProgress()).c_str());
                }
        }
        
        // QUEUE OVEN
        line = 1;
        for (int i = 0; i < Baker::queueOven.size(); i++){
                int colour = -1;
                switch (bakers[Baker::queueOven.at(i)].getNowProducing()){
                    case 0:
                        colour = 1;
                        break;
                    case 1:
                        colour = 2;
                        break;
                    case 2:
                        colour = 3;
                        break;
                    default:
                        break;
                        
                }
                attron( COLOR_PAIR( colour ) ); 
                mvprintw(line++, 35, std::to_string(Baker::queueOven.at(i)).c_str());
                attroff( COLOR_PAIR( colour ) ); 
                if (i == 0){
                    mvprintw(line-1, 37, std::to_string(bakers[Baker::queueOven.at(i)].getProgress()).c_str());
                }
        }
        
        // INSIDE OVEN
        line = 1;
        for (int i = 0; i < oven.getSize(); i++){
                int colour = -1; 
                switch (oven.getType(i)){
                    case 0:
                        colour = 1;
                        break;
                    case 1:
                        colour = 2;
                        break; 
                    case 2:
                        colour = 3;
                        break;
                    default:
                        break;
                        
                }
                attron( COLOR_PAIR( colour ) ); 
                mvprintw(line++, 60, std::to_string(oven.getRemainingTime(i)).c_str());
                attroff( COLOR_PAIR( colour ) ); 
        }
        
        // INSIDE SHELF
        attron( COLOR_PAIR( 1 ) ); 
        mvprintw(10, 15, std::to_string(shelf.getNumberOfBreads()).c_str());
        attroff( COLOR_PAIR( 1 ) ); 
        
        attron( COLOR_PAIR( 2 ) ); 
        mvprintw(10, 25, std::to_string(shelf.getNumberOfBaguettes()).c_str());
        attroff( COLOR_PAIR( 2 ) ); 
        
        attron( COLOR_PAIR( 3 ) ); 
        mvprintw(10, 35, std::to_string(shelf.getNumberOfCroissants()).c_str());
        attroff( COLOR_PAIR( 3 ) ); 
        
        // CLIENTS
        line = 12;
        for (int i = 0; i < Client::queue.size(); i++){
                int colour = -1;
                switch (clients[Client::queue.at(i)].getShoppingList()){
                    case 0:
                        colour = 1;
                        break;
                    case 1:
                        colour = 2;
                        break;
                    case 2:
                        colour = 3;
                        break;
                    default:
                        break;
                        
                }
                attron( COLOR_PAIR( colour ) ); 
                mvprintw(line++, 5, std::to_string(Client::queue.at(i)).c_str());
                attroff( COLOR_PAIR( colour ) ); 
        }
        
        // WAIT
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
    end.join();

    // END NCURSES *************************************************
    endwin();

    return 0;
}
