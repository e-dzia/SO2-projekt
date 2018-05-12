#include "Shelf.h"

Shelf::Shelf(){
    for (int i = 0; i < typesOfBakedGoods; i++){
        bakedGoods[i] = 0;
    }
}

void Shelf::addBread(int type){
    std::lock_guard<std::mutex> guard(shelf);
    bakedGoods[type]++;
}

void Shelf::addBread(int type, int amount){
    std::lock_guard<std::mutex> guard(shelf);
    bakedGoods[type] += amount;
}

bool Shelf::takeBread(int type){
    std::lock_guard<std::mutex> guard(shelf);
    if (bakedGoods[type] > 0){
        bakedGoods[type]--;
        return true;
    }
    return false;
}

int Shelf::getNumberOfBreads() const {
    return bakedGoods[0];
}

int Shelf::getNumberOfBaguettes() const {
    return bakedGoods[1];
}

int Shelf::getNumberOfCroissants() const {
    return bakedGoods[2];
}


