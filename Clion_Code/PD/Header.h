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


#define HEADER_BLOCK_SIZE (32)
#define HEADER_BLOCK_TYPE uint32_t

#define SL(p) (1ULL <<(p))
//#define MASK(perm)  ( (1ULL <<(perm)) - 1ULL)
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
//    vector<bool> vec;
public:
    Header(size_t m, size_t f, size_t l);

//    ~Header();

    void get_quotient_start_and_end_index(size_t quotient, size_t *start_index, size_t *end_index);

    bool lookup(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void insert(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    bool conditional_remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    /**
     * Moves bits starting from end, one bit to the left.
     * @param quotient
     * @param start
     * @param end
     */
    void pull(uint_fast16_t quotient, size_t start, size_t end);

    /**
     * Moves bits starting from end, one bit to the right.
     * @param quotient
     * @param start
     * @param end
     */
    void push(uint_fast16_t quotient, size_t start, size_t end);

    /** Helpers */

    void print_as_word();

    void pretty_print();

    void print();

    void print_as_bool_array();

    /**Functions for vector*/

    /*void get_interval(size_t quotient, size_t *start_index, size_t *end_index);

    void insert(size_t quotient);

    void remove(uint_fast16_t quotient);

    uint32_t sum_vector();
*/
    /**Functions for validation*/

//    uint32_t sum_header();

//    void validate_get_interval(size_t quotient);


    void header_to_word_array(uint32_t *a, size_t a_size);

    void header_to_bool_array(bool *a);

//    void print_bool_array(bool *a, size_t a_size);


    size_t get_size() const;

    HEADER_BLOCK_TYPE *get_h() const;

    friend ostream &operator<<(ostream &os, const Header &header);


//public:
//    size_t get_max_capacity();
};


void
get_interval_old(const HEADER_BLOCK_TYPE *a, size_t a_size, size_t quotient, size_t *start_index, size_t *end_index);

/*TODO: 1) OUT OF BOUND ERROR WILL OCCUR IF QUOTIENT DOES NOT BELONG TO [M].
      2) more efficient implementation.*/
/**
 *
 * @param a
 * @param a_size: a's length.
 * @param quotient:
 * @param start_index: Denote the index of the (quotient - 1)th zero by i.
 * This function set *start_index to i + 1.
 * @param end_index: Denote the index of the (quotient)th zero by j.
 * This function set *end_index to j.
 */
void
get_interval_attempt(const HEADER_BLOCK_TYPE *a, size_t a_size, size_t quotient, size_t *start_index,
                     size_t *end_index);

void
get_interval_by_rank(const HEADER_BLOCK_TYPE *a, size_t a_size, size_t quotient, size_t *start_index,
                     size_t *end_index);


bool validate_get_interval_functions(const HEADER_BLOCK_TYPE *arr, size_t a_size, size_t quotient);
#endif //CLION_CODE_HEADER_H
