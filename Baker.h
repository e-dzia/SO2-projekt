#ifndef BAKERY_BAKER_H
#define BAKERY_BAKER_H

#include <thread>
#include <mutex>
#include <deque>
#include <atomic>
#include <condition_variable>
#include "Utility.h"
#include "Oven.h"
#include "Shelf.h"

class Baker {
    enum bakerAction{
        STOCKROOM, TABLE, OVEN, SHELF, WAITING
    };
    const std::string bakerActionName[5] = {"stockroom", "table", "oven", "shelf", "waiting"};

    static int numberOfBakers;

    static std::mutex queueStockroomMutex;
    static std::mutex queueTableMutex;
    static std::mutex queueOvenMutex;

    static std::condition_variable queueStockroomCV;
    static std::condition_variable queueTableCV;
    static std::condition_variable queueOvenCV;

    static const int typesOfBakedGoods;

    int id = -1;
    std::atomic<int> nowProducing;// = -1;
    std::atomic<bool> alive;// = false;
    std::atomic<bakerAction> action;// = WAITING;
    std::atomic<int> progress;// = 0;
    
    std::thread life;

    int numberOfBakedGoods[];

    void useStockroom(Utility *stockroom);
    void useTable(Utility* table);
    void useOven(Oven* oven);
    void useShelf(Shelf* shelf);

    int random(int min, int max);
    void sleepRandom(int min, int max);

    bool checkQueue(int type);

    void live(Utility *stockroom, Utility* table, Oven* oven, Shelf* shelf);

public:
    static std::deque<int> queueStockroom;
    static std::deque<int> queueTable;
    static std::deque<int> queueOven;


    Baker();
    Baker(const Baker& client);
    Baker& operator=(const Baker& baker);
    ~Baker();

    int getId() const;
    bool isAlive() const;
    std::string getAction();
    int getProgress() const;
    int getNowProducing() const;

    void start(Utility *stockroom, Utility* table, Oven* oven, Shelf* shelf);
    void stop();
};


#endif //BAKERY_BAKER_H
