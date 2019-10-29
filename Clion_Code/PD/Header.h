//
// Created by tomer on 10/24/19.
//

#ifndef CLION_CODE_HEADER_H
#define CLION_CODE_HEADER_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ctgmath>
#include "../bit_operations/bit_op.h"
#include "../Global_functions/basic_functions.h"



#define HEADER_BLOCK_SIZE (8)
#define HEADER_BLOCK_TYPE uint8_t

#define SL(p) (1ULL <<(p))
#define MASK(p)  ( (1ULL <<(p))  - 1ULL)
#define MB_BIT(n) (1ULL << (MB - (n)))
#define ON(a, b) (MASK(a) ^ MASK(b))
#define OFF(a, b) (~(MASK(a) ^ MASK(b)))
//#define MOD_INVERSE(n) (HEADER_BLOCK_SIZE - (n) - 1)
#define INTEGER_ROUND(a, b) (((a)/(b)) + ((a)%(b) != 0))



class Header {
    size_t capacity;
    size_t max_capacity;
    size_t size;
    HEADER_BLOCK_TYPE *H;

    /** For testing*/
    vector<bool> vec;
public:
    Header(size_t m, size_t f, size_t l);

    void get_quotient_start_and_end_index(size_t quotient, size_t *start_index, size_t *end_index);

    bool lookup(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void insert(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void print_as_word();

    void pretty_print();

    void print();

    void print_as_bool_array();

    /**Functions for vector*/

    void vector_get_interval(size_t quotient, size_t *start_index, size_t *end_index);

    void vector_insert(size_t quotient);

    void vector_remove(uint_fast16_t quotient);

    uint32_t sum_vector();

    /**Functions for validation*/

    uint32_t sum_header();

    void validate_get_interval(size_t quotient);

    friend ostream &operator<<(ostream &os, const Header &header);


    void header_to_word_array(uint32_t *a, size_t a_size);

    void header_to_bool_array(bool *a);

//    void print_bool_array(bool *a, size_t a_size);

    void pull(uint_fast16_t quotient, size_t start, size_t end);

    void push(uint_fast16_t quotient, size_t start, size_t end);

    size_t get_size() const;

//public:
//    size_t get_max_capacity();
};


// TODO OUT OF BOUND ERROR WILL OCCUR IF QUOTIENT DOES NOT BELONG TO [M].
void
get_interval_old(const HEADER_BLOCK_TYPE *a, size_t a_size, size_t quotient, size_t *start_index, size_t *end_index);

void
get_interval_att(const HEADER_BLOCK_TYPE *a, size_t a_size, size_t quotient, size_t *start_index, size_t *end_index);


#endif //CLION_CODE_HEADER_H
