//
// Created by nbboy on 2020/8/4.
//

#include "prime.h"

int Prime_get(int at) {
    if (at < 0 || at >= PRIME_SIZE) {
        fprintf(stderr, "prime is overflow");
        assert(0);
    }

    return primes[at];
}

/**
 *  找到第一个比base_size大的数
 * @param base_size
 * @return 返回-1就是没有找到
 */
int Prime_getAt(int base_size) {
    int begin = 0;
    int end = PRIME_SIZE - 1;
    int middle;

    while (begin <= end) {
        middle = end - (end - begin) / 2;
        if (primes[middle] < base_size) {
            begin = middle + 1;
        } else {
            if (middle == 0 || primes[middle - 1] < base_size) {
                return middle;
            }

            end = middle - 1;
        }
    }

    return -1;
}
