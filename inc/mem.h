//
// Created by nbboy on 2020/8/4.
//

#ifndef HASHTABLE_MEM_H
#define HASHTABLE_MEM_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define Mem_callocP(__count, __size) ({\
    void **__temp = calloc(__count, __size);\
    for(int __i = 0;__i<__count;__i++){\
        __temp[__i] = NULL;\
    }\
    __temp;\
})

#ifdef __cplusplus
}
#endif
#endif //HASHTABLE_MEM_H
