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


bool validate_header_get_interval_function(size_t reps);

bool t1(bool to_print = false);

bool t2(bool to_print = false);

bool t3(bool to_print = false);

bool t4(bool to_print = false);

bool t5(size_t m, size_t f, size_t l, bool to_print = false);

/**
 * random tests.
 * @param reps
 * @param to_print
 * @return
 */
bool r0(size_t reps, bool to_print = 0);


template<class T>
bool r0_core_template(size_t reps, T *d, size_t m, size_t f, size_t l, bool to_print = 0);

bool r0_core(size_t reps, PD *d, size_t m, size_t f, size_t l, bool to_print = 0);

bool s0(size_t reps, bool to_print = 0);

bool naive_pd_r0(size_t reps, bool to_print = 0);

bool r1(size_t reps, bool to_print);

bool vector_rw_t1();

bool pow2c_r0(size_t reps, bool to_print = 0);

bool pow2c_naive_r0(size_t reps, bool to_print = 0);


//bool naive_pd_r0(size_t reps, bool to_print = 0);

#endif //CLION_CODE_VALIDATION_TESTS_H
