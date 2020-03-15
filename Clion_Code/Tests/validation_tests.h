//
// Created by tomer on 10/25/19.
//

#ifndef CLION_CODE_VALIDATION_TESTS_H
#define CLION_CODE_VALIDATION_TESTS_H


#include <tuple>
#include <random>

#include "../PD/PD.h"
#include "../Safe_PD/safe_PD.h"
#include "../Naive_PD/naive_PD.h"
#include "../POW2C/pow2c_filter.h"
#include "../POW2C/pow2c_naive_filter.h"
#include "benchmark_tests.h"
#include "../Constant_size_PD/const_PD.h"
#include "../Contiguous_PD/cg_PD.h"

void break_point_helper();

bool validate_header_get_interval_function(size_t reps);

bool validate_get_interval_function_constant(size_t reps);

bool validate_push_function(size_t reps);

bool validate_pull_function(size_t reps);

bool validate_rank_function(size_t reps);

/**
 * smashing stack for some reason.
 * @param reps
 * @return
 */
bool validate_header_type(size_t reps);

bool t1(bool to_print = false);

bool t2(bool to_print = false);

bool t3(bool to_print = false);

bool t4(bool to_print = false);

bool t5(size_t m, size_t f, size_t l, bool to_print = false);

template<class T>
bool validate_PD(size_t reps, bool to_seed, bool to_print = 0);


template<class T>
bool validate_PD_higher_load(size_t reps, float load_factor, bool to_seed, bool to_print = 0);

/**
 * random tests.
 * @param reps
 * @param to_print
 * @return
 */
bool validate_PD_single_run(size_t reps, bool to_print = 0);

bool validate_const_PD(size_t reps, bool to_print = 0);

template<class T>
bool validate_PD_core(size_t reps, T *d, size_t m, size_t f, size_t l, bool to_print, float load_factor);

bool r0_core(size_t reps, PD *d, size_t m, size_t f, size_t l, bool to_print = 0);


bool validate_PD_by_load_factor(size_t reps, float load_factor, size_t m = 32, size_t f = 32, bool to_print = 0);

bool validate_safe_PD(size_t reps, bool to_print = 0);

bool validate_safe_PD_const_case(size_t reps, bool to_print = 0);

bool naive_pd_r0(size_t reps, bool to_print = 0);

bool r1(size_t reps, bool to_print);

bool vector_rw_t1();

bool pow2c_r0(size_t reps, bool to_print = 0);

bool pow2c_naive_r0(size_t reps, bool to_print = 0);


//bool naive_pd_r0(size_t reps, bool to_print = 0);

#endif //CLION_CODE_VALIDATION_TESTS_H
