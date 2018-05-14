#include <random>
#include <iostream>
#include "Client.h"

int Client::numberOfClients = 0;
std::deque<int> Client::queue;
std::mutex Client::queueMutex;
const int Client::typesOfBakedGoods = 3;
const double Client::bakedGoodPrices[Client::typesOfBakedGoods] = {1.57, 2.34, 3.22};

Client::Client() {
    this->id = this->numberOfClients++;
    shoppingList = -1;
    alive = false;
    action = OUTSIDE;
    progress = 0;
}

Client::Client(const Client &client) : id (client.id){}

Client &Client::operator=(const Client &client) {
    this->id = client.id;
    return *this;
}

Client::~Client() {
    if (life.joinable()){
        life.join();
    }
}

void Client::walkIntoStore() {
    if (!alive) return;
    action = IN_STORE;
    sleepRandom(500, 1000);
    shoppingList = random(0, typesOfBakedGoods-1);

    queueMutex.lock();
    queue.push_back(this->id);
    queueMutex.unlock();

    action = IN_LINE;
}

void Client::doShopping(Account* account, Shelf* shelf) {
    while (!checkQueue()){
        sleepRandom(100, 200);
    }
    if (!alive) return;
    action = BUYING;
    if (shelf->takeBread(shoppingList)){
        account->pay(bakedGoodPrices[shoppingList]);
        sleepRandom(2000, 3000);
    }
    sleepRandom(100,500);
    action = IN_STORE;
}

void Client::walkOutOfStore() {
    if (!alive) return;
    shoppingList = -1;

    queueMutex.lock();
    queue.pop_front();
    queueMutex.unlock();

    action = OUTSIDE;
}

void Client::live(Account* account, Shelf* shelf) {
    while(alive){
        action = OUTSIDE;
        walkIntoStore();
        doShopping(account, shelf);
        walkOutOfStore();
        sleepRandom(5000,15000);
    }
}

int Client::getId() const {
    return id;
}

bool Client::isAlive() const {
    return alive;
}

int Client::random(const int &min, const int &max) {
    static thread_local std::mt19937* generator = nullptr;
    static std::hash<std::thread::id> hasher;
    if (!generator) generator = new std::mt19937(clock() + hasher(std::this_thread::get_id()));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(*generator);
}

void Client::sleepRandom(const int &min, const int &max) {
    int numberOfLoops = random(min,max)/100;
    for (int i = 0; i < numberOfLoops; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = 100*i/numberOfLoops;
        if (!alive) return;
    }
}

bool Client::checkQueue() {
    if (!alive) return true;
    std::lock_guard<std::mutex> guard(queueMutex);
    return queue.front() == this->id;
}

void Client::start(Account *account, Shelf *shelf) {
    alive = true;
    life = std::thread(&Client::live, this, account, shelf);
}

void Client::stop() {
    alive = false;
}

std::string Client::getAction() const {
    return clientActionName[action];
}

int Client::getProgress() const {
    return progress;
}

int Client::getShoppingList() const {
    return shoppingList;
}


