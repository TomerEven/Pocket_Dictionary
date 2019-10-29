//
// Created by tomer on 10/24/19.
//

#ifndef CLION_CODE_N_BIT_ARRAY_H
#define CLION_CODE_N_BIT_ARRAY_H

#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <tgmath.h>

#define INTEGER_ROUND(a, b) (((a)/(b)) + ((a)%(b) != 0))


#define BLOCK_SIZE (32)
#define BLOCK_TYPE uint32_t

#define SL(p) (1ULL <<(p))
#define MASK(p)  ( (1ULL <<(p))  - 1ULL)
#define MB_BIT(n) (1ULL << (MB - (n)))
#define ON(a, b) (MASK(a) ^ MASK(b))
#define OFF(a, b) (~(MASK(a) ^ MASK(b)))
#define MOD_INVERSE(n) (BLOCK_SIZE - (n) - 1)


using namespace std;


class n_bit_array {
    size_t size;
    size_t capacity;
    size_t data_size;
    BLOCK_TYPE *A;
//    size_t MB;


public:
    BLOCK_TYPE get_bits(size_t address, size_t length);

    void set_bits(size_t address, size_t bitsToWriteCounter, size_t value);

    void push(size_t start);

    void pull(size_t start);


    size_t get_capacity() const;

    size_t get_data_size() const;

    size_t get_size() const;


    void get_cell(size_t q_index, BLOCK_TYPE *dataArray, size_t arraySize);

//    void getData(size_t q_index, BLOCK_TYPE *dataArray, size_t arraySize);

    BLOCK_TYPE getMB(size_t q_index);

    void set_cell(size_t q_index, BLOCK_TYPE *dataArray, size_t arraySize);

    void set_cell(size_t q_index, BLOCK_TYPE *dataArray, size_t arraySize, BLOCK_TYPE tempMB);


    void set_bit(size_t address, bool setOn);

    void setHelp(size_t aIndex, size_t value, size_t borderStart, size_t borderEnd);


    bool operator<(const n_bit_array &rhs) const;

    bool operator>(const n_bit_array &rhs) const;

    bool operator<=(const n_bit_array &rhs) const;

    bool operator>=(const n_bit_array &rhs) const;
};


#endif //CLION_CODE_N_BIT_ARRAY_H
