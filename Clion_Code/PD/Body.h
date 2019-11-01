//
// Created by tomer on 10/24/19.
//


/**
 * The core of the code is in the function find_attempt.
 */

#ifndef CLION_CODE_BODY_H
#define CLION_CODE_BODY_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ctgmath>
//#include "../bit_operations/bit_op.h"
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
//    vector<bool> vec;
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

    //todo return value can be boolean (if PD is not adaptive).
    /**
     *
     * @param abstract_body_start_index: remainder first possible location,
     * assuming the body is an array of remainder.
     * @param abstract_body_end_index: the remainder last possible location.
     * @param remainder
     * @param p_B_index: the actual body.B index in which the remainder is, or where it should be inserted.
     * @param p_bit_index: the bit index inside body.B[*p_B_index] from which the remainder start.
     * (or should be inserted)
     * @return 1 - When given remainder was found. Pointers will point to it.
     *         2 - When given remainder was not found. Pointers will point to first slot (in the run or it end)
     *         with remainder bigger than the one that was given (or to the first slot in the next run).
     */
    int
    find_attempt(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder, size_t *p_B_index,
                 size_t *p_bit_index);

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


    int find_helper(bool did_find, size_t current_b_index, size_t bits_left, size_t *p_B_index, size_t *p_bit_index);

    int
    find_helper_attempt(bool did_find, size_t current_b_index, size_t bits_left, size_t *p_B_index,
                        size_t *p_bit_index);

public:
    /**Function used for printing*/
    void store_consecutive_remainders(uint32_t *a);

    void print_consecutive();

    void naive_print();



    /**Vector functions.*/

    /*

    void print_consecutive_with_vector();

    void naive_print_with_vector();

    bool vector_lookup(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void vector_insert(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    void vector_remove(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);

    int
    vector_find(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder, size_t *p_B_index,
                size_t *p_bit_index);

    BODY_BLOCK_TYPE read_FP_from_vector_by_index(size_t bit_start_index);

    void write_FP_to_vector_by_index(size_t index, FP_TYPE remainder);

    bool compare_remainder_and_vector(size_t bit_start_index, FP_TYPE remainder);

    void vector_push(size_t vector_bit_counter);
*/
    /**Validating functions.*/

//    void validate_find(size_t abstract_body_start_index, size_t abstract_body_end_index, FP_TYPE remainder);


    size_t get_fp_size() const;

    size_t get_size() const;

    uint32_t *get_b() const;
};


#endif //CLION_CODE_BODY_H

