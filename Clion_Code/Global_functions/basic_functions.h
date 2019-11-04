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

#define MASK(p)  ( (1ULL <<(p)) - 1ULL)

using namespace std;

void print_array(int *a, size_t a_size);

void print_array(uint32_t *a, size_t a_size);

void print_bool_array(bool *a, size_t a_size);

void print_array_as_consecutive_memory(uint32_t *a, size_t a_size);

//string n_to_32bin(uint32_t n);

void print_vector(vector<int> *v);

void print_vector(vector<bool> *v);

void print_vector_as_words(const vector<bool> *v);

void print_vector_by_unpacking(vector<bool> *v, size_t unpack_size);

void print_bool_vector_no_spaces(vector<bool> *v);

uint32_t read_FP_from_vector_by_index(vector<bool> *v, size_t bit_start_index, size_t fp_size);

void write_FP_to_vector_by_index(vector<bool> *v, size_t index, uint32_t remainder, size_t fp_size);

void to_vector(vector<bool> *vec, const uint32_t *a, size_t a_size);

void to_vector(vector<bool> *vec, uint8_t *a, size_t a_size);

void vector_to_word_array(const vector<bool> *v, uint32_t *a, size_t a_size);

unsigned int naive_msb32(unsigned int x);

string my_bin(size_t n, size_t length = 32);



#endif //CLION_CODE_BASIC_FUNCTIONS_H

