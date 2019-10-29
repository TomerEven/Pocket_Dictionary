//
// Created by tomer on 10/24/19.
//

#ifndef CLION_CODE_BODY_H
#define CLION_CODE_BODY_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ctgmath>
#include "../bit_operations/bit_op.h"
#include "../Global_functions/basic_functions.h"

#define INTEGER_ROUND(a, b) (((a)/(b)) + ((a)%(b) != 0))


#define BODY_BLOCK_SIZE (32)
#define BODY_BLOCK_TYPE uint32_t
#define FP_TYPE_SIZE (32)
#define FP_TYPE uint32_t

#define SL(p) (1ULL <<(p))
#define MASK(p)  ( (1ULL <<(p))  - 1ULL)
#define MB_BIT(n) (1ULL << (MB - (n)))
#define ON(a, b) (MASK(a) ^ MASK(b))
#define OFF(a, b) (~(MASK(a) ^ MASK(b)))
//#define MOD_INVERSE(n) (BODY_BLOCK_SIZE - (n) - 1)

#define CASE_PRINT (0)

class Body {
    size_t fp_size;
    size_t capacity;
    size_t max_capacity;
    size_t size;
    BODY_BLOCK_TYPE *B;

    /** For testing*/
    vector<bool> vec;
public:
    Body(size_t m, size_t f, size_t l);

    /**
     *
     * @param abstract_body_start_index if quotient = x ,and quotient's run started in the i'th index in the header,
     * start_index should be i - x + 1.
     * @param abstract_body_end_index
     * @param remainder
     * @return
     */
    bool lookup(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void insert(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void remove(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    bool wrap_lookup(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void wrap_insert(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void wrap_remove(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

private:
    /**
     *
     * @param abstract_body_start_index
     * @param abstract_body_end_index
     * @param remainder
     * @param p_B_index
     * @param p_bit_index
     * @return 1 - When given remainder was found. Pointers will point to it.
     *         2 - When given remainder was not found. Pointers will point to first slot (in the run or it end)
     *         with remainder bigger than the one that was given (or to the first slot in the next run).
     */
    int
    find(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder, size_t *p_B_index,
         size_t *p_bit_index);

    int
    find_att(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder, size_t *p_B_index,
             size_t *p_bit_index);


    int find_helper(bool did_find, size_t current_b_index, size_t bits_left, size_t *p_B_index, size_t *p_bit_index);

    int
    find_helper_att(bool did_find, size_t current_b_index, size_t bits_left, size_t *p_B_index, size_t *p_bit_index);

public:
    void store_consecutive_remainders(uint32_t *a);

    void print_consecutive();

    void print_consecutive_with_vector();

    void naive_print();

    void naive_print_with_vector();


    /**Vector functions.*/

    bool vector_lookup(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void vector_insert(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void vector_remove(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    int
    vector_find(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder, size_t *p_B_index,
                size_t *p_bit_index);

    BODY_BLOCK_TYPE read_FP_from_vector_by_index(size_t bit_start_index);

    void write_FP_to_vector_by_index(size_t index, FP_TYPE remainder);

    bool compare_remainder_and_vector(size_t bit_start_index, FP_TYPE remainder);


    /**Validating functions.*/

    void validate_find(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);


    void vector_push(size_t vector_bit_counter);
};


#endif //CLION_CODE_BODY_H

/*
    void push(size_t B_index, size_t bit_index);

    void pull(size_t B_index, size_t bit_index);

    void print_q_run(size_t quotient);

    void get_cell(size_t qIndex, BODY_BLOCK_TYPE *dataArray, size_t arraySize);

    void get_data(size_t qIndex, BODY_BLOCK_TYPE *dataArray, size_t arraySize);

    BODY_BLOCK_TYPE get_MB(size_t qIndex);

    void set_cell(size_t qIndex, BODY_BLOCK_TYPE *dataArray, size_t arraySize);

    void set_cell(size_t qIndex, BODY_BLOCK_TYPE *dataArray, size_t arraySize, BODY_BLOCK_TYPE tempMB);

    BODY_BLOCK_TYPE get_bits(size_t address, size_t length);

    bool get_bits_att(size_t address, size_t length, FP_TYPE remainder);

    void set_bits(size_t address, size_t bitsToWriteCounter, size_t value);

    void set_bit(size_t address, bool setOn);

    void set_help(size_t aIndex, size_t value, size_t borderStart, size_t borderEnd);
*/
