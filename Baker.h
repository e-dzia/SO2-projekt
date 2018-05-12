#ifndef BAKERY_BAKER_H
#define BAKERY_BAKER_H

#include <thread>
#include <mutex>
#include <deque>
#include "Utility.h"
#include "Oven.h"
#include "Shelf.h"

/*
 * Piekarze
     * pobierają składniki z magazynu (najkrótszy etap),
     * urabiają ciasto na stole (średnio długi etap) i
     * pieką chleb w piekarniku (najdłuższy etap), -> ważne! musi przy wkładaniu sprawdzać, czy jakieś chleby w piecu są skończone
     * po czym kładą gotowy chleb na półki.
 */
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

    void useStockroom(Utility *stockroom);
    void useTable(Utility* table);
    void useOven(Oven* oven);
    void useShelf(Shelf* shelf);

    int random(const int& min, const int& max);
    void sleepRandom(const int &min, const int &max);

    bool checkQueue(int type);

public:
    static std::deque<int> queueStockroom;
    static std::deque<int> queueTable;
    static std::deque<int> queueOven;
    std::thread life;

    Baker();
    Baker(const Baker& client);
    ~Baker();

    void live(Utility *stockroom, Utility* table, Oven* oven, Shelf* shelf);
    int getId() const;
    bool isAlive() const;
    std::string getAction() const;
    int getProgress() const;
    int getNowProducing() const;

    void start(Utility *stockroom, Utility* table, Oven* oven, Shelf* shelf);
    void stop();

private:
    int numberOfBakedGoods[];
};


#endif //BAKERY_BAKER_H
