#include <stdio.h>
#include "hashtable.h"

int main() {
    int age = 32;
    double weight = 7.01;

    HT ht = Ht_create(200);
    Ht_set(ht, "myname", "chenxiaofeng");
    Ht_set(ht, "myage", &age);
    Ht_set(ht, "myweight", &weight);
    int *age1 = Ht_get(ht, "myage");
    printf("ack age1:%d\r\n", *age1);

    age = 34;
    Ht_set(ht, "myage", &age);
    age1 = Ht_get(ht, "myage");
    printf("ack age2:%d\r\n", *age1);

    char *name1 = Ht_get(ht, "myname");
    printf("ack name:%s\r\n", name1);

    double *weight1 = Ht_get(ht, "myweight");
    printf("ack weight:%f\r\n", *weight1);

    Ht_del(ht, "myage");
    age1 = Ht_get(ht, "myage");

    if (age1 != NULL) {
        printf("ack age3:%d\r\n", *age1);
    } else {
        printf("NULL Value\r\n");
    }

    age = 88;
    Ht_set(ht, "myage", &age);
    age1 = Ht_get(ht, "myage");
    printf("ack age4:%d\r\n", *age1);

    Ht_destroy(&ht);
    return 0;
}
