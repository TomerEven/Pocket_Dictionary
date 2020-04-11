//
// Created by tomer on 4/11/20.
//

#ifndef CLION_CODE_VALIDATE_COUNTING_FILTER_HPP
#define CLION_CODE_VALIDATE_COUNTING_FILTER_HPP

#include "validate_filter.hpp"
#include "../Dict/multi_dict.hpp"


template<class D>
auto v_counting_filter(size_t filter_max_capacity, size_t lookup_reps, size_t error_power_inv, size_t l1_counter_size,
                       size_t l2_counter_size, double level1_load_factor, double level2_load_factor) -> bool;



#endif //CLION_CODE_VALIDATE_COUNTING_FILTER_HPP
