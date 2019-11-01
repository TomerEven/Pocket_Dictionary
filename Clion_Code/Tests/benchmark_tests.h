//
// Created by tomer on 10/29/19.
//

#ifndef CLION_CODE_BENCHMARK_TESTS_H
#define CLION_CODE_BENCHMARK_TESTS_H


#include <set>
#include <fstream>

#include "../Global_functions/basic_functions.h"
#include "../PD/PD.h"
#include "../Safe_PD/safe_PD.h"


#define MIN_ELEMENT_LENGTH 8
#define MIN_CHAR_RANGE 32
#define MIN_LENGTH_RANGE 8
#define QR_TUPLE tuple<uint32_t ,uint32_t>


string rand_string(int minLength, int charsNum, int numOfDiffLength = MIN_LENGTH_RANGE);

void set_init(size_t size, set<string> *mySet, int minLength = MIN_ELEMENT_LENGTH, int charsNum = MIN_CHAR_RANGE);

void set_init(size_t size, set<QR_TUPLE > *mySet, uint32_t max_q, uint32_t max_r);


void b1(size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os)

#endif //CLION_CODE_BENCHMARK_TESTS_H
