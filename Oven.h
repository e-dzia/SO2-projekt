#ifndef BAKERY_OVEN_H
#define BAKERY_OVEN_H

#include <thread>
#include <mutex>

/*
 * Piec zwiększa stan upieczenia pieczywa, które jest w środku
 * Jednocześnie jest zasobem - tylko jeden wątek może z niego korzystać
 */
class Oven {
    static const int typesOfBakedGoods = 3;
    std::mutex oven;

};


#endif //BAKERY_OVEN_H
