#ifndef BAKERY_TABLE_H
#define BAKERY_TABLE_H


#include <mutex>

class Utility {
    std::mutex table;
    bool isLocked = false;

public:
    Utility() = default;

    void startUsing();
    void stopUsing();
    bool isBeingUsed();
};


#endif //BAKERY_TABLE_H
