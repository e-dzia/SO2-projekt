#include "Utility.h"

void Utility::startUsing(){
    table.lock();
    isLocked = true;
}

void Utility::stopUsing(){
    table.unlock();
    isLocked = false;
}

bool Utility::isBeingUsed(){
    return isLocked;
}