#ifndef BAKERY_SHELF_H
#define BAKERY_SHELF_H


#include <mutex>

class Shelf {
    static const int typesOfBakedGoods = 3;
    int bakedGoods[typesOfBakedGoods];
    std::mutex bakedGoodsMutex;

public:
    Shelf();
    Shelf(const Shelf& shelf) = delete;
    Shelf& operator=(Shelf const&) = delete;

    void addBread(int type);
    void addBread(int type, int amount);
    bool takeBread(int type);

    int getNumberOfBreads();
    int getNumberOfBaguettes();
    int getNumberOfCroissants();

};


#endif //BAKERY_SHELF_H
