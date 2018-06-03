#include <iostream>
#include "Oven.h"

const int Oven::typesOfBakedGoods = 3;
const int Oven::bakingTimes[Oven::typesOfBakedGoods] = {3000, 5000, 7000};

void Oven::putIn(int type) {
    std::lock_guard<std::mutex> guard(notYetBakedMutex);
    notYetBaked.emplace_back(BakedGood(type, bakingTimes[type]));
}

int Oven::takeOut(int type) {
    int takenOut = 0;
    std::lock_guard<std::mutex> guard(notYetBakedMutex);
    for (auto it = notYetBaked.begin(); it != notYetBaked.end(); ++it){
        if (it->type == type && it->remainingTime <= 0){
            takenOut++;
            notYetBaked.erase(it);
            --it;
        }
    }
    return takenOut;
}

void Oven::bakeAll() {
    std::lock_guard<std::mutex> guard(notYetBakedMutex);
    for (BakedGood& bakedGood: notYetBaked){
        bakedGood.bake();
    }
}

void Oven::live(){
    functioning = true;
    while (functioning){
        bakeAll();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Oven::stop() {
    functioning = false;
}

int Oven::getRemainingTime(int i){
    std::lock_guard<std::mutex> guard(notYetBakedMutex);
    return notYetBaked[i].remainingTime;
}

int Oven::getType(int i){
    std::lock_guard<std::mutex> guard(notYetBakedMutex);
    return notYetBaked[i].type;
}

int Oven::getSize(){
    std::lock_guard<std::mutex> guard(notYetBakedMutex);
    return notYetBaked.size();
}
