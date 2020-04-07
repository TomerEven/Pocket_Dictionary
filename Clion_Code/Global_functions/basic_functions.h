//
// Created by tomer on 10/25/19.
//



#ifndef CLION_CODE_BASIC_FUNCTIONS_H
#define CLION_CODE_BASIC_FUNCTIONS_H

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ctgmath>
#include <climits>
#include <iomanip>


using namespace std;

template<typename T>
void print_array_as_integers(const T *a, size_t size);

template<typename T>
ostream &print_array_as_consecutive_memory(const T *a, size_t size, ostream &os);

template<typename T>
string my_bin(T n, size_t length = 32);

/**
 * Assuming x + y < max of type "T" (does not deal with overflow.)
 * @tparam T Integer. (currently size_t)
 * @param x
 * @param y
 * @return ceil(x/y)
 */
template<typename T>
auto my_ceil(T x, T y) -> T;

void print_array(uint8_t *a, size_t a_size);

void print_array(int *a, size_t a_size);

void print_array(uint32_t *a, size_t a_size);

void print_bool_array(bool *a, size_t a_size);

void print_array_as_consecutive_memory(const uint32_t *a, size_t a_size);

//string n_to_32bin(uint32_t n);

void print_vector(vector<int> *v);

void print_vector(vector<bool> *v);

void print_vector_as_words(const vector<bool> *v);

void print_vector_by_unpacking(vector<bool> *v, size_t unpack_size);

void print_bool_vector_no_spaces(const vector<bool> *v);

auto read_FP_from_vector_by_index(const vector<bool> *v, size_t bit_start_index, size_t fp_size) -> uint32_t;

void write_FP_to_vector_by_index(vector<bool> *v, size_t index, uint32_t remainder, size_t fp_size);

void to_vector(vector<bool> *vec, const uint32_t *a, size_t a_size);

void to_vector(vector<bool> *vec, uint8_t *a, size_t a_size);

void vector_to_word_array(const vector<bool> *v, uint32_t *a, size_t a_size);

int compare_vector_and_array(const vector<bool> *v, const uint8_t *a);

int compare_vector_and_array(const vector<bool> *v, const uint32_t *a);

unsigned int naive_msb32(unsigned int x);

string my_bin(size_t n, size_t length = 32);

void formatting();

void table_print(size_t var_num, string *var_names, size_t *values);

void table_print_columns(size_t var_num, size_t column_num, string *var_names, string *columns, size_t *values);

string to_sci(double x, int add_to_counter = 0, size_t precision = 3);

#endif //CLION_CODE_BASIC_FUNCTIONS_H

