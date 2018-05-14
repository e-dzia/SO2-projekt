#ifndef BAKERY_OVEN_H
#define BAKERY_OVEN_H

#include <thread>
#include <mutex>
#include <vector>

class Oven {

    struct BakedGood{
        int type;
        int remainingTime;

        BakedGood(int type, int remainingTime){
            this->type = type;
            this->remainingTime = remainingTime;
        }

        void bake(){
            this->remainingTime -= 100;
        }
    };

    static const int typesOfBakedGoods;
    static const int bakingTimes[];

    std::mutex oven;
    std::vector<BakedGood> notYetBaked;

    bool functioning = true;

public:
    Oven() = default;
    Oven(const Oven& oven) = delete;
    Oven& operator=(Oven const&) = delete;

    void putIn(int type);
    int takeOut(int type);

    void bakeAll();

    void live();
    void stop();
};


#endif //BAKERY_OVEN_H
