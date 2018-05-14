#include "Shelf.h"

Shelf::Shelf(){
    std::lock_guard<std::mutex> guard(shelf);
    for (int &bakedGood : bakedGoods) {
        bakedGood = 3;
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

int Shelf::getNumberOfBreads(){
    std::lock_guard<std::mutex> guard(shelf);
    return bakedGoods[0];
}

int Shelf::getNumberOfBaguettes(){
    std::lock_guard<std::mutex> guard(shelf);
    return bakedGoods[1];
}

int Shelf::getNumberOfCroissants(){
    std::lock_guard<std::mutex> guard(shelf);
    return bakedGoods[2];
}


