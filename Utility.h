#ifndef BAKERY_TABLE_H
#define BAKERY_TABLE_H


#include <mutex>

class Utility {
    std::mutex table;
    bool isLocked = false;

public:
    Utility() = default;

    void startUsing(){
        table.lock();
        isLocked = true;
    }

    void stopUsing(){
        table.unlock();
        isLocked = false;
    }

    bool isBeingUsed(){
        return isLocked;
    }
};


#endif //BAKERY_TABLE_H
