//
// Created by tomer on 10/25/19.
//

#ifndef CLION_CODE_VALIDATION_TESTS_H
#define CLION_CODE_VALIDATION_TESTS_H


#include <tuple>
#include <random>

#include "../PD/PD.h"
#include "../Safe_PD/safe_PD.h"

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

bool s0(size_t reps, bool to_print = 0);

bool r1(size_t reps, bool to_print);

bool vector_rw_t1();



#endif //CLION_CODE_VALIDATION_TESTS_H
