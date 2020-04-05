//
// Created by tomer on 3/15/20.
//

#ifndef CLION_CODE_VALIDATE_BIT_OP_HPP
#define CLION_CODE_VALIDATE_BIT_OP_HPP

#include "../bit_operations/my_bit_op.hpp"
#include "../Global_functions/basic_functions.h"

auto validate_find_kth_interval_iter(size_t reps, size_t a_size) -> bool;

auto validate_find_kth_interval_random(size_t reps, size_t a_size) -> bool;

auto validate_find_kth_interval_single(uint32_t *a, size_t a_size, size_t k) -> bool;

template<typename T>
auto validate_find_first_and_second_set_bits_iter(size_t reps, size_t a_size) -> bool;

template<typename T>
auto validate_find_first_and_second_set_bits_rand(size_t reps, size_t a_size) -> bool;

template<typename T>
auto validate_find_first_and_second_set_bits_single(T *a, size_t a_size) -> bool;

template<typename T>
auto v_vec_and_array_transformation(size_t reps, size_t total_bits) -> bool;

/*

template<typename T>
auto v_update_element_with_fixed_size_single(T *a, size_t a_size, size_t bit_start_pos, size_t bit_end_pos,
                                             T new_val) -> bool;
*/


template<typename T>
auto v_update_element_single(T *a, size_t a_size, size_t start, size_t end, size_t new_val) -> bool;

template<typename T>
auto v_update_element_with_fixed_size_rand(size_t reps, size_t sub_reps) -> bool;

template<typename T>
auto v_update_element_iter(size_t reps, size_t sub_reps) -> bool;

template<typename T>
auto v_update_element_rand(size_t reps, size_t sub_reps) -> bool;

template<typename T>
auto
v_update_push_helper(T *a, size_t start, size_t end, size_t new_start, size_t new_end, size_t prev_val, size_t new_val,
                     size_t a_size) -> bool;


auto v_vector_update_single(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                            size_t new_val) -> bool;

auto v_vector_update_rand(size_t reps) -> bool;


template<typename T>
auto v_update_by_comparison_single(T *a, size_t a_size, vector<bool> *vec, size_t prev_start, size_t prev_end,
                                   size_t new_start, size_t new_end, size_t new_val) -> bool;

template<typename T>
auto v_update_by_comparison_rand(size_t reps, size_t a_size) -> bool;


template<typename T>
auto v_read_k_words_fixed_length_single(const T *a, size_t a_size, size_t index, size_t element_length, T *res_array,
                                        size_t k) -> bool;

template<typename T>
auto v_read_k_words_fixed_length_rand(size_t reps, size_t element_length) -> bool;
#endif //CLION_CODE_VALIDATE_BIT_OP_HPP
