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
            if (this-> remainingTime > 0)
                this->remainingTime -= 100;
        }
    };

    static const int typesOfBakedGoods;
    static const int bakingTimes[];

    std::mutex notYetBakedMutex;
    std::vector<BakedGood> notYetBaked;

    bool functioning = true;

public:
    Oven() = default;
    Oven(const Oven& oven) = delete;
    Oven& operator=(Oven const&) = delete;

    void putIn(int type);
    int takeOut(int type);

    void bakeAll();
    
    int getRemainingTime(int i);
    int getType(int i);
    
    int getSize();

    void live(); 
    void stop();
};


#endif //BAKERY_OVEN_H
