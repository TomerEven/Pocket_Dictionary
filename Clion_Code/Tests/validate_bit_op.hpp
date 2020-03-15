//
// Created by tomer on 3/15/20.
//

#ifndef CLION_CODE_VALIDATE_BIT_OP_HPP
#define CLION_CODE_VALIDATE_BIT_OP_HPP

#include "../bit_operations/my_bit_op.hpp"

auto validate_find_kth_interval_iter(size_t reps, size_t a_size) -> bool;

auto validate_find_kth_interval_random(size_t reps, size_t a_size) -> bool;

auto validate_find_kth_interval_single(uint32_t *a, size_t a_size, size_t k) -> bool;


template<typename T>
auto validate_find_first_and_second_set_bits_iter(size_t reps, size_t a_size) -> bool;

template<typename T>
auto validate_find_first_and_second_set_bits_rand(size_t reps, size_t a_size) -> bool;

template<typename T>
auto validate_find_first_and_second_set_bits_single(T *a, size_t a_size) -> bool;

#endif //CLION_CODE_VALIDATE_BIT_OP_HPP
