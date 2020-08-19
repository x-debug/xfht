//
// Created by nbboy on 2020/8/4.
//

#ifndef HASHTABLE_PRIME_H
#define HASHTABLE_PRIME_H

#include <assert.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

static int primes[] = {
        53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
        49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457, 1610612741
};

#define PRIME_SIZE 26

int Prime_get(int at);
int Prime_getAt(int base_size);

#ifdef __cplusplus
}
#endif

#endif //HASHTABLE_PRIME_H
