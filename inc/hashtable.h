//
// Created by nbboy on 2020/8/4.
//

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct HashTableItem_T {
    char *key;
    size_t key_len;
    void *value;
} HashTableItem;

typedef struct HashTable_T {
    size_t count;

    size_t size;

    size_t base_size;

    int prime_at;

    struct HashTableItem_T **items;
} HashTable;

typedef HashTable *HT;

//ADT
HT Ht_create(size_t base_size);

int Ht_set(HT ht, const char *key, void *value);

void *Ht_get(HT ht, const char *key);

int Ht_del(HT ht, const char *key);

void Ht_destroy(HT *ht);

#ifdef __cplusplus
}
#endif
#endif //HASHTABLE_HASHTABLE_H
