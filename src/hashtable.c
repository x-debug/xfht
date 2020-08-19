//
// Created by nbboy on 2020/8/4.
//

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hashtable.h"
#include "prime.h"
#include "mem.h"

#define HT_LOAD(__ht) (__ht->count * 100 / __ht->size)
#define IS_UP(__ht) (HT_LOAD(__ht) > 70)
#define IS_DOWN(__ht) (HT_LOAD(__ht) < 10)

static struct HashTableItem_T deleted_item = {NULL, 0, NULL};

static int PRIME_A = 196613;

static int PRIME_B = 6291469;

static HashTableItem *create_item(const char *key, void *value) {
    HashTableItem *item = malloc(sizeof(HashTableItem));
    item->key_len = strlen(key);
    item->key = strdup(key);
    item->value = value;
    return item;
}

static void destroy_item(HashTableItem *item) {
    assert(item);
    free(item->key);
    free(item);
}

static int hash_code(const char *key, int prime, size_t bucket_num) {
    long hash = 0;

    int key_len = (int) strlen(key);
    for (int i = 0; i < key_len; ++i) {
        hash += (long) (pow(prime, key_len - i - 1) * key[i]);
        hash = hash % bucket_num;
    }

    return (int) hash;
}

static int get_hash(const char *key, int at, size_t bucket_num) {
    int hash_a = hash_code(key, PRIME_A, bucket_num);
    int hash_b = hash_code(key, PRIME_B, bucket_num);

    return (int) ((hash_a + at * (hash_b + 1)) % bucket_num);
}

static void resize_buckets(HT ht, size_t base_size) {
    HT new_ht = Ht_create(base_size);
    struct HashTableItem_T *item;
    struct HashTableItem_T **temp_items;
    size_t temp_size;

    //复制到新buckets
    for (int i = 0; i < ht->size; ++i) {
        item = ht->items[i];
        if (item != NULL && item != &deleted_item){
            Ht_set(new_ht, item->key, item->value);
        }
    }

    temp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = temp_items;

    temp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = temp_size;

    ht->base_size = new_ht->base_size;
    ht->prime_at = new_ht->prime_at;

    Ht_destroy(&new_ht);
}

HT Ht_create(size_t base_size) {
    HT ht = malloc(sizeof(HashTable));
    ht->count = 0;
    ht->base_size = base_size;
    ht->prime_at = Prime_getAt(base_size);
    if (ht->prime_at == -1) {
        fprintf(stderr, "base_size error");
        free(ht);
        assert(0);
    }
    ht->size = Prime_get(ht->prime_at);
    ht->items = (struct HashTableItem_T **) Mem_callocP(ht->size, sizeof(struct HashTableItem_T *));
    return ht;
}

int Ht_set(HT ht, const char *key, void *value) {
    int index, i = 0;
    struct HashTableItem_T *item;

    //resize
    if (IS_UP(ht)) {
        resize_buckets(ht, 2 * ht->base_size);
    }

    while (1) {
        index = get_hash(key, i, ht->size);
        item = ht->items[index];

        if (item == NULL || item == &deleted_item) {
            break;
        }

        if (item != &deleted_item && !strcmp(item->key, key)) {
            item->value = value;
            return 0;
        }

        i++;
    }
    ht->items[index] = create_item(key, value);
    ht->count++;
    return 1;
}

void *Ht_get(HT ht, const char *key) {
    int index, i = 0;
    struct HashTableItem_T *item;

    while (1) {
        index = get_hash(key, i, ht->size);
        item = ht->items[index];
        if (item == NULL) {
            break;
        }

        if (item != &deleted_item && !strcmp(item->key, key)) {
            return item->value;
        }

        i++;
    }

    return NULL;
}

int Ht_del(HT ht, const char *key) {
    int index, i = 0;
    struct HashTableItem_T *item;

    //resize
    if (IS_DOWN(ht)) {
        resize_buckets(ht, ht->base_size / 2);
    }

    while (1) {
        index = get_hash(key, i, ht->size);
        item = ht->items[index];

        if (item == NULL) {
            break;
        }

        if (item != &deleted_item && !strcmp(item->key, key)) {
            destroy_item(item);
            ht->items[index] = &deleted_item;
            ht->count--;
            return 1;
        }

        i++;
    }

    return 0;
}

void Ht_destroy(HT *htp) {
    HT ht = *htp;
    for (int i = 0; i < ht->size; ++i) {
        if (ht->items[i] != NULL && ht->items[i] != &deleted_item) {
            destroy_item(ht->items[i]);
        }
    }
    free(ht->items);
    free(ht);
    *htp = NULL;
}
