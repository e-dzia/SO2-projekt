#ifndef BAKERY_CLIENT_H
#define BAKERY_CLIENT_H

#include <thread>
#include <queue>
#include <mutex>
#include "Account.h"
#include "Shelf.h"

/*
 * Klienci wchodzą do sklepu i kupują chleb z półki, jednocześnie płacąc za niego (zwiększając stan konta piekarni). Chlebów może być kilka rodzajów dla urozmaicenia (klient chce kupić konkretny rodzaj).
 */
class Client {
    enum clientAction{
        IN_STORE, IN_LINE, BUYING, OUTSIDE
    };
    std::string clientActionName[4] = {"in_store", "in_line", "buying", "outside"};

    static int numberOfClients;

    static std::mutex queueMutex;
    static const int typesOfBakedGoods;
    static const double bakedGoodPrices[];// = {1.57, 2.34, 3.28};

    int shoppingList = -1;
    int id = -1;
    bool alive = false;
    clientAction action = OUTSIDE;
    int progress = 0;
    std::thread life;

    void walkIntoStore();
    void doShopping(Account* account, Shelf* shelf);
    void walkOutOfStore();

    int random(const int& min, const int& max);
    void sleepRandom(const int &min, const int &max);

    bool checkQueue();

public:
    static std::deque<int> queue;

    Client();
    Client(const Client& client);
    ~Client();

    void live(Account* account, Shelf* shelf);
    int getId() const;
    bool isAlive() const;
    std::string getAction() const;
    int getProgress() const;
    int getShoppingList() const;

    void start(Account *account, Shelf *shelf);
    void stop();

};


#endif //BAKERY_CLIENT_H
