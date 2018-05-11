//
// Created by Edzia on 2018-05-11.
//

#ifndef BAKERY_SHELF_H
#define BAKERY_SHELF_H


#include <mutex>

class Shelf {
    static const int typesOfBakedGoods = 3;
    int bakedGoods[typesOfBakedGoods];
    std::mutex shelf;

public:
    Shelf();
    Shelf(const Shelf& shelf) = delete;
    Shelf& operator=(Shelf const&) = delete;

    void addBread(int type);
    bool takeBread(int type);

    int getNumberOfBreads() const;
    int getNumberOfBaguettes() const;
    int getNumberOfCroissants() const;

};


#endif //BAKERY_SHELF_H
