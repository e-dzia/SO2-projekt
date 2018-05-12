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
        WAITING, IN_LINE, BUYING, OUT
    };

    static int numberOfClients;
    static std::queue<int> queue;
    static std::mutex queueMutex;
    static const int typesOfBakedGoods;
    static double bakedGoodPrices[];// = {1.57, 2.34, 3.28};

    int shoppingList = -1;
    int id = -1;
    bool alive = false;
    clientAction action = WAITING;
    int progress;
    std::thread life;

    void walkIntoStore();
    void doShopping(Account* account, Shelf* shelf);
    void walkOutOfStore();

    int random(const int& min, const int& max);
    void sleepRandom(const int &min, const int &max);

public:
    Client();
    Client(const Client& client) = delete;
    Client& operator=(Client const&) = delete;
    ~Client();

    void live(Account* account, Shelf* shelf);
    int getId() const;
    bool isAlive() const;
    void setAlive(bool alive);

    clientAction getAction() const;

    int getProgress() const;

    void start(Account *account, Shelf *shelf);
    void stop();

    bool checkQueue();


};


#endif //BAKERY_CLIENT_H
