//
// Created by tomer on 4/12/20.
//

#ifndef CLION_CODE_BENCHMARK_COUNTING_FILTER_HPP
#define CLION_CODE_BENCHMARK_COUNTING_FILTER_HPP

#include "benchmark_tests.h"
#include "test_printer.hpp"

//template<class D, typename T>
//auto time_lookups(D* filter, set<T> * element_set) ->chrono::nanoseconds;
//
template<class D>
auto CF_rates_wrapper(size_t filter_max_capacity, size_t lookup_reps, size_t error_power_inv, size_t l1_counter_size,
                      size_t l2_counter_size, double level1_load_factor, double level2_load_factor,
                      ostream &os) -> ostream &;

template<class D>
auto
CF_rates_core(D *filter, size_t filter_max_capacity, size_t lookup_reps, ulong init_time, ostream &os) -> ostream &;

template<class D>
auto CF_rates_init(size_t filter_max_capacity, size_t lookup_reps, size_t error_power_inv, size_t l1_counter_size,
                   size_t l2_counter_size, double level1_load_factor, double level2_load_factor) -> ostream &;

template<class D>
auto time_lookups(D *filter, set<string> *element_set) -> ulong;

template<class D>
auto time_insertions(D *filter, set<string> *element_set) -> ulong;

template<class D>
auto time_deletions(D *filter, set<string> *element_set) -> ulong;


#endif //CLION_CODE_BENCHMARK_COUNTING_FILTER_HPP
