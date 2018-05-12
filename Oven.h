#ifndef BAKERY_OVEN_H
#define BAKERY_OVEN_H

#include <thread>
#include <mutex>
#include <vector>

/*
 * Piec zwiększa stan upieczenia pieczywa, które jest w środku
 * Jednocześnie jest zasobem - tylko jeden wątek może z niego korzystać
 */
class Oven {
    static const int typesOfBakedGoods;
    std::mutex oven;

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
    std::vector<BakedGood> notYetBaked;
    static const int bakingTimes[];

    bool functioning = true;

public:
    Oven() = default;

    void putIn(int type);
    int takeOut(int type);

    void bakeAll();

    void live();
    void stop();
};


#endif //BAKERY_OVEN_H
