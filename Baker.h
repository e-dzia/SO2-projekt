#ifndef BAKERY_BAKER_H
#define BAKERY_BAKER_H

#include <thread>
#include <mutex>
#include <deque>
#include "Utility.h"
#include "Oven.h"
#include "Shelf.h"

class Baker {
    enum bakerAction{
        STOCKROOM, TABLE, OVEN, SHELF, WAITING
    };
    std::string bakerActionName[5] = {"stockroom", "table", "oven", "shelf", "waiting"};

    static int numberOfBakers;

    static std::mutex queueStockroomMutex;
    static std::mutex queueTableMutex;
    static std::mutex queueOvenMutex;

    static const int typesOfBakedGoods;

    int nowProducing = -1;
    int id = -1;
    bool alive = false;
    bakerAction action = WAITING;
    int progress = 0;
    std::thread life;

    int numberOfBakedGoods[];

    void useStockroom(Utility *stockroom);
    void useTable(Utility* table);
    void useOven(Oven* oven);
    void useShelf(Shelf* shelf);

    int random(const int& min, const int& max);
    void sleepRandom(const int &min, const int &max);

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
    std::string getAction() const;
    int getProgress() const;
    int getNowProducing() const;

    void start(Utility *stockroom, Utility* table, Oven* oven, Shelf* shelf);
    void stop();
};


#endif //BAKERY_BAKER_H
