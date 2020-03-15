//
// Created by tomer on 11/26/19.
//

#ifndef CLION_CODE_STATIC_HASHING_H
#define CLION_CODE_STATIC_HASHING_H


#include "MurmurHash3.h"
#include "../Global_functions/basic_functions.h"
#include "../Global_functions/macros.h"
#include <iostream>
#include <cstring>
#include <random>
#include <assert.h>

//template<typename T>
//uint32_t hash(uint32_t)

//static const uint32_t SEED_1 = random() , SEED_2 = random();
static const uint32_t SEED_1 = 1, SEED_2 = 42;

inline uint32_t my_hash(uint32_t el, uint32_t seed) {
    uint32_t a = 0, b = 0;
    MurmurHash3_x86_32(&el, (int) (64), SEED_1, &a);
    MurmurHash3_x86_32(&el, (int) (64), SEED_2, &b);
    return a + seed * b;
}

inline uint32_t my_hash(const char *elementP, uint32_t seed) {
    uint32_t a, b;
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), SEED_1, &a);
    MurmurHash3_x86_32(elementP, (int) (strlen(elementP)), SEED_2, &b);
    return a + seed * b;
}

inline uint32_t my_hash(string *elementP, uint32_t seed) {
//    assert(false);
    char const *cp = elementP->c_str();
    uint32_t a, b;
    MurmurHash3_x86_32(cp, (int) (strlen(cp)), SEED_1, &a);
    MurmurHash3_x86_32(cp, (int) (strlen(cp)), SEED_2, &b);
    return a + seed * b;
}



//inline uint32_t hash32(uint32_t el, uint32_t seed) {
//    uint32_t a = 0, b = 0;
//    MurmurHash3_x86_32(&el, (int) (32), SEED_1, &a);
//    MurmurHash3_x86_32(&el, (int) (32), SEED_2, &b);
//    return a + seed * b;
//}

inline uint32_t naive_perm(uint32_t n) {
    n += 4061379055;
    n = ((n << 11u) | (n >> 21u)) + 3038993865;
    return ((n << 4u) | (n >> 27u)) ^ 2419120842u;
}

//uint32_t rotl32 (uint32_t value, unsigned int count) {
//    return value << count | value >> (32 - count);
//}
#endif //CLION_CODE_STATIC_HASHING_H