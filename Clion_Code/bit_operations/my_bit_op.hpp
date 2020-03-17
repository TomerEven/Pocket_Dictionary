//
// Created by tomer on 3/15/20.
//

#ifndef CLION_CODE_MY_BIT_OP_HPP
#define CLION_CODE_MY_BIT_OP_HPP

#include <iostream>
#include <zconf.h>
#include <vector>
#include <cstdint>
#include <cassert>
#include "../Global_functions/macros.h"
#include "bit_op.h"


using namespace std;
typedef unsigned int u32;


/**
 * Rank and Select operations definition: https://en.wikipedia.org/wiki/Succinct_data_structure#Succinct_dictionaries
 * @tparam T
 * @param a
 * @param a_size
 * @param k
 * @param start Stores result of SELECT(a, k) + 1
 * @param end Stores result of SELECT(a, k + 1)
 */
template<typename T>
void find_kth_interval_simple(T *a, size_t a_size, size_t k, size_t *start, size_t *end);

/**
 * Preforms SELECT, under the assumption "word" contains MORE than k set bits.
 * @param word
 * @param k
 * @param start
 * @param end
 */
void word_k_select(uint32_t word, size_t k, size_t *start, size_t *end);

/**
 *
 * @tparam T
 * @param a
 * @param a_size
 * @return The index of the set bit in a (were a is a vector of bits.)
 */
template<typename T>
auto find_first_set_bit(T *a, size_t a_size) -> size_t;

template<typename T>
void find_first_and_second_set_bits(T *a, size_t a_size, size_t *first, size_t *second);


auto count_set_bits(uint32_t *a, size_t a_size) -> size_t;

////Functions used for validation.

/**
 * * Same as basic_functions::to_vector(...).
 * @tparam T
 * @param vec
 * @param a
 * @param a_size
 */
template<typename T>
void from_array_to_vector(vector<bool> *vec, const T *a, size_t a_size);

/**
 * Same as basic_functions::vector_to_word_array(...).
 * @tparam T
 * @param vec
 * @param a
 * @param a_size
 */
template<typename T>
void from_vector_to_array(const vector<bool> *vec, T *a, size_t a_size);

/**
 *
 * @tparam T
 * @param v
 * @param start
 * @param end
 * @return With python syntax, assuming v is a string of {0,1}*: return int(v[start:end],2)
 */
template <typename T>
T sub_vector_to_word(const vector<bool> *v, size_t start, size_t end);


/**
 *
 * @param vec
 * @param k
 * @param start_index The index of the (k-1) set bit (-1)
 * @param end_index
 */
void vector_find_kth_interval_simple(vector<bool> *vec, size_t k, size_t *start_index, size_t *end_index);


auto vector_find_first_set_bit(vector<bool> *vec) -> size_t;

uint32_t vector_extract_symbol(vector<bool> *vec, size_t *start_index, size_t *end_index);

//void vector_find_first_and_second_set_bits()
#endif //CLION_CODE_MY_BIT_OP_HPP
