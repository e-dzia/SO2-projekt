#include <random>
#include "Client.h"

int Client::numberOfClients = 0;
std::queue<int> Client::queue;
std::mutex Client::queueMutex;
const int Client::typesOfBakedGoods = 3;
double Client::bakedGoodPrices[Client::typesOfBakedGoods] = {1.57, 2.34, 3.28};

int Client::random(const int &min, const int &max) {
    static thread_local std::mt19937* generator = nullptr;
    static std::hash<std::thread::id> hasher;
    if (!generator) generator = new std::mt19937(clock() + hasher(std::this_thread::get_id()));
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(*generator);
}

Client::Client() {
    this->id = this->numberOfClients++;
}

Client::~Client() {
    if (life.joinable()){
        life.join();
    }
}

void Client::walkIntoStore() {
    action = WAITING;
    sleepRandom(500, 1000);
    shoppingList = random(0, typesOfBakedGoods);

    queueMutex.lock();
    queue.push(this->id);
    queueMutex.unlock();

    action = IN_LINE;
}

void Client::doShopping(Account* account, Shelf* shelf) {
    while (!checkQueue()){
        sleepRandom(100, 200);
    }
    action = BUYING;
    if (shelf->takeBread(shoppingList)){
        account->pay(bakedGoodPrices[shoppingList]);
        sleepRandom(1000, 2000);
    }
    action = WAITING;
}

void Client::walkOutOfStore() {
    shoppingList = -1;

    queueMutex.lock();
    queue.pop();
    queueMutex.unlock();

    action = OUT;
}

void Client::live(Account* account, Shelf* shelf) {
    while(alive){
        walkIntoStore();
        doShopping(account, shelf);
        walkOutOfStore();
        sleepRandom(3000,8000);
    }
}

int Client::getId() const {
    return id;
}

bool Client::isAlive() const {
    return alive;
}

void Client::setAlive(bool alive) {
    Client::alive = alive;
}

void Client::sleepRandom(const int &min, const int &max) {
    int numberOfLoops = random(min,max)/100;
    for (int i = 0; i < numberOfLoops; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        progress = 100*i/numberOfLoops;
    }
}

bool Client::checkQueue() {
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

Client::clientAction Client::getAction() const {
    return action;
}

int Client::getProgress() const {
    return progress;
}


