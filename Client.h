#ifndef BAKERY_CLIENT_H
#define BAKERY_CLIENT_H

#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include "Account.h"
#include "Shelf.h"

class Client {
    enum clientAction{
        IN_STORE, IN_LINE, BUYING, OUTSIDE
    };
    const std::string clientActionName[4] = {"in_store", "in_line", "buying", "outside"};

    static int numberOfClients;

    static std::mutex queueMutex;
    static const int typesOfBakedGoods;
    static const double bakedGoodPrices[];

    int id = -1;
    std::atomic<int> shoppingList;// = -1;
    std::atomic<bool> alive;// = false;
    std::atomic<clientAction> action;// = OUTSIDE;
    std::atomic<int> progress;// = 0;
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
    Client& operator=(const Client& client);
    ~Client();

    void live(Account* account, Shelf* shelf);
    int getId() const;
    bool isAlive() const;
    std::string getAction();
    int getProgress() const;
    int getShoppingList() const;

    void start(Account *account, Shelf *shelf);
    void stop();

};


#endif //BAKERY_CLIENT_H
