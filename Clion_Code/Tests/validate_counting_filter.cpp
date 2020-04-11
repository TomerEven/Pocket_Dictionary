//
// Created by tomer on 4/11/20.
//

#include "validate_counting_filter.hpp"

template<class D>
auto v_counting_filter(size_t filter_max_capacity, size_t lookup_reps, size_t error_power_inv, size_t l1_counter_size,
                       size_t l2_counter_size, double level1_load_factor, double level2_load_factor) -> bool {
    auto filter = D(filter_max_capacity, error_power_inv, l1_counter_size, l2_counter_size, level1_load_factor,
                    level2_load_factor);
    cout << "\nexpected #fp is: " << ((double) lookup_reps / (1u << error_power_inv)) << endl;
    auto res = validate_filter_core_mid(&filter, filter_max_capacity, lookup_reps);
    if (!res) {
        std::cout << "mid falied" << endl;
        return false;
    }
//
    return validate_filter_core(&filter, filter_max_capacity, lookup_reps);
    return true;
}

template auto
v_counting_filter<basic_multi_dict>(size_t filter_max_capacity, size_t lookup_reps,
                                    size_t error_power_inv, size_t l1_counter_size,
                                    size_t l2_counter_size, double level1_load_factor,
                                    double level2_load_factor) -> bool;

template auto
v_counting_filter<safe_multi_dict>(size_t filter_max_capacity, size_t lookup_reps,
                                   size_t error_power_inv, size_t l1_counter_size,
                                   size_t l2_counter_size, double level1_load_factor,
                                   double level2_load_factor) -> bool;


