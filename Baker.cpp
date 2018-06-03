#include "Baker.h"
#include <random>
#include <iostream>

int Baker::numberOfBakers = 0;
std::deque<int> Baker::queueStockroom;
std::deque<int> Baker::queueTable;
std::deque<int> Baker::queueOven;
std::mutex Baker::queueStockroomMutex;
std::mutex Baker::queueTableMutex;
std::mutex Baker::queueOvenMutex;
const int Baker::typesOfBakedGoods = 3;

Baker::Baker() {
    this->id = this->numberOfBakers++;
    nowProducing = -1;
    alive = false;
    action = WAITING;
    progress = 0;
    numberOfBakedGoods[Baker::typesOfBakedGoods];
}

Baker::Baker(const Baker &Baker) : id (Baker.id){}

Baker& Baker::operator=(const Baker &baker) {
    this->id = baker.id;
    return *this;
}

Baker::~Baker() {
    if (life.joinable()){
        life.join();
    }
}

void Baker::live(Utility *stockroom, Utility* table, Oven* oven, Shelf* shelf) {
    while(this->alive){
        action = WAITING;
        useStockroom(stockroom);
        useTable(table);
        useOven(oven);
        useShelf(shelf);
    }
}

int Baker::getId() const {
    return id;
}

bool Baker::isAlive() const {
    return alive;
}

int Baker::random(const int min, const int max) {
    static thread_local std::mt19937* generator = nullptr;
    static std::hash<std::thread::id> hasher;
    if (!generator) generator = new std::mt19937(clock() + hasher(std::this_thread::get_id()));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(*generator);
}

void Baker::sleepRandom(const int min, const int max) {
    int numberOfLoops = random(min,max)/100;
    for (int i = 0; i < numberOfLoops; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        this->progress = 100*i/numberOfLoops;
        if (!this->alive) return;
    }
}

bool Baker::checkQueue(int type) {
    if (!alive) return true;
    switch(type){
        case 0: {
            std::lock_guard<std::mutex> guard(queueStockroomMutex);
            return queueStockroom.front() == this->id;
        }
        case 1: {
            std::lock_guard<std::mutex> guard1(queueTableMutex);
            return queueTable.front() == this->id;
        }
        case 2: {
            std::lock_guard<std::mutex> guard2(queueOvenMutex);
            return queueOven.front() == this->id;
        }
        default:
            return false;
    }
}

void Baker::start(Utility *stockroom, Utility* table, Oven* oven, Shelf* shelf) {
    alive = true;
    life = std::thread(&Baker::live, this, stockroom, table, oven, shelf);
}

void Baker::stop() {
    alive = false;
}

std::string Baker::getAction(){
    return bakerActionName[action];
}

int Baker::getProgress() const {
    return progress;
}

int Baker::getNowProducing() const {
    return nowProducing;
}

void Baker::useStockroom(Utility *stockroom) {
    action = WAITING;

    queueStockroomMutex.lock();
    queueStockroom.push_back(id);
    queueStockroomMutex.unlock();

    while (!checkQueue(0)){
        sleepRandom(100, 200);
    }

    stockroom->startUsing();
    action = STOCKROOM;
    nowProducing = random(0, typesOfBakedGoods-1);
    sleepRandom(500,2000);
    stockroom->stopUsing();

    action = WAITING;

    queueStockroomMutex.lock();
    queueStockroom.pop_front();
    queueStockroomMutex.unlock();
}

void Baker::useTable(Utility *table) {
    action = WAITING;

    queueTableMutex.lock();
    queueTable.push_back(id);
    queueTableMutex.unlock();

    while (!checkQueue(1)){
        sleepRandom(100, 200);
    }


    table->startUsing();
    action = TABLE;
    sleepRandom(1000,3000);
    table->stopUsing();

    action = WAITING;

    queueTableMutex.lock();
    queueTable.pop_front();
    queueTableMutex.unlock();

}

void Baker::useOven(Oven *oven) {
    action = WAITING;

    queueOvenMutex.lock();
    queueOven.push_back(id);
    queueOvenMutex.unlock();

    while (!checkQueue(2)){
        sleepRandom(100, 200);
    }

    oven->putIn(nowProducing);
    action = OVEN;
    for (int i = 0; i < typesOfBakedGoods; i++){
        numberOfBakedGoods[i] = oven->takeOut(i);
    }
    sleepRandom(500,1000);
    action = WAITING;

    queueOvenMutex.lock();
    queueOven.pop_front();
    queueOvenMutex.unlock();
}

void Baker::useShelf(Shelf *shelf) {
    action = SHELF;
    for (int i = 0; i < typesOfBakedGoods; i++){
        shelf->addBread(i,numberOfBakedGoods[i]);
        numberOfBakedGoods[i] = 0;
        sleepRandom(100,500);
    }
    action = WAITING;
}
