//
// Created by tomer on 10/29/19.
//

#ifndef CLION_CODE_BENCHMARK_TESTS_H
#define CLION_CODE_BENCHMARK_TESTS_H


#include <set>
#include <fstream>
#include <tuple>
#include <random>

#include "../Global_functions/basic_functions.h"
#include "../PD/PD.h"
#include "../Safe_PD/safe_PD.h"
#include "../POW2C/pow2c_filter.h"
#include "../Naive_PD/naive_PD.h"
#include "../POW2C/pow2c_naive_filter.h"


#define MIN_ELEMENT_LENGTH 8
#define MIN_CHAR_RANGE 32
#define MIN_LENGTH_RANGE 8
#define QR_TUPLE tuple<uint32_t ,uint32_t>


string rand_string(int minLength, int charsNum, int numOfDiffLength = MIN_LENGTH_RANGE);

void set_init(size_t size, set <string> *mySet, int minLength = MIN_ELEMENT_LENGTH, int charsNum = MIN_CHAR_RANGE);

void vector_lexicographic_init(size_t size, vector<string> *vec, int minLength = MIN_ELEMENT_LENGTH,
                               int charsNum = MIN_CHAR_RANGE);

void set_init(size_t size, set <QR_TUPLE> *mySet, uint32_t max_q, uint32_t max_r);

ostream &b0(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os);

ostream &
b0_naive(size_t number_of_pds, float load_factor, size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os);

void b1(size_t f, size_t m, size_t l, size_t lookup_reps, ostream &os);


ostream &
test_printer(size_t n, double eps, size_t lookups_num, bool is_adaptive, double set_ratio, int *counter,
             double member_set_init_time,
             double nom_set_init_time, double init_time, double insertion_time, double lookup_time,
             double total_run_time, ostream &os);

bool filter_r1(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l);

bool filter_naive_r1(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l);

bool filter_r0(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l);

bool filter_naive_r0(size_t number_of_pds, float load_factor, size_t m, size_t f, size_t l);

#endif //CLION_CODE_BENCHMARK_TESTS_H
