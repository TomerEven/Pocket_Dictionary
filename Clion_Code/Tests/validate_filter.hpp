//
// Created by tomer on 4/6/20.
//

#ifndef CLION_CODE_VALIDATE_FILTER_HPP
#define CLION_CODE_VALIDATE_FILTER_HPP

#include "../POW2C/gen_2Power.h"
#include "../POW2C/pow2c_filter.h"
#include "../POW2C/pow2c_naive_filter.h"
#include "../POW2C/const_filter.h"
#include "benchmark_tests.h"
#include "../Dict/dict.hpp"
#include "../Dict/multi_dict.hpp"
#include <set>


template<class T>
auto validate_filter(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l, size_t lookup_reps) -> bool;

template<class D>
auto v_filter(size_t filter_max_capacity, size_t lookup_reps, size_t error_power_inv, double level1_load_factor,
              double level2_load_factor) -> bool;

template<class D>
auto validate_filter_core_mid(D *filter, size_t filter_max_capacity, size_t lookup_reps) -> bool;

//template<class D>
//auto v_filter(size_t filter_max_capacity, size_t error_power_inv, double level1_load_factor, double level2_load_factor) -> bool;

template<class D>
auto validate_filter_core(D *filter, size_t filter_max_capacity, size_t lookup_reps) -> bool;

#endif //CLION_CODE_VALIDATE_FILTER_HPP

