#ifndef BAKERY_OVEN_H
#define BAKERY_OVEN_H

#include <thread>
#include <mutex>

/*
 * Piec zwiększa stan upieczenia pieczywa, które jest w środku
 * Jednocześnie jest zasobem - tylko jeden wątek może z niego korzystać
 */
class Oven {
    std::mutex oven;
    std::thread bake;

};


#endif //BAKERY_OVEN_H
