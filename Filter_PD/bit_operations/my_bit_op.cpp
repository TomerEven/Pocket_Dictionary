//
// Created by tomer on 3/15/20.
//

//#include "Naive_Counter_Endec.hpp"
#include "my_bit_op.hpp"

void word_k_select(uint32_t word, size_t k, size_t *start, size_t *end) {

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// vector functions.

auto vector_last_k_bits_are_zero(vector<bool> *vec, size_t k) -> bool {
    auto size = vec->size();
    for (auto i = size - k; i < size; ++i) {
        if (vec->at(i) != 0) {
            return false;
        }
    }
    return true;
}


void vector_find_kth_interval_simple(vector<bool> *vec, size_t k, size_t *start_index, size_t *end_index) {
    size_t set_bit_counter = 0, continue_from_index = 0;
    for (size_t i = 0; i < vec->size(); ++i) {
        if (set_bit_counter == k) {
            *start_index = i;
            continue_from_index = i;
            break;
        }
        if (vec->at(i))
            set_bit_counter++;
    }
    assert(*start_index < vec->size());

    for (size_t i = continue_from_index; i < vec->size(); ++i) {
        if (vec->at(i)) {
            *end_index = i;
            return;
        }
    }
    cout << "vector_find_kth_interval_simple: reached end of vector" << endl;
    assert(false);
}

auto vector_find_first_set_bit(vector<bool> *vec) -> size_t {
    for (int i = 0; i < vec->size(); ++i) { if (vec->at(i)) return i; }
    assert(false);
}


auto count_set_bits(uint32_t *a, size_t a_size) -> size_t {
    size_t counter = 0;
    for (int i = 0; i < a_size; ++i) {
        counter += __builtin_popcount(a[i]);
    }
    return counter;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Templates definitions.



/*
template auto get_numbers_bit_length_difference<uint32_t>(const uint32_t x, const uint32_t y) -> int;

template auto get_x_bit_length<uint32_t>(const uint32_t x) -> size_t;

template size_t find_first_set_bit<uint32_t>(uint32_t *a, size_t a_size);

template void find_kth_interval_simple<uint32_t>(uint32_t *a, size_t a_size, size_t k, size_t *start, size_t *end);

template auto find_kth_interval_simple<uint64_t>(uint64_t *a, size_t a_size, size_t k) -> std::tuple<size_t, size_t>;

template void from_array_to_vector<uint32_t>(vector<bool> *vec, const uint32_t *a, size_t a_size);

template void from_vector_to_array<uint32_t>(const vector<bool> *vec, uint32_t *a, size_t a_size);

template uint32_t sub_vector_to_word<uint32_t>(const vector<bool> *v, size_t start, size_t end);

template void
update_element_with_fixed_size<uint32_t>(uint32_t *a, size_t bit_start_pos, size_t bit_end_pos,
                                         uint32_t new_val, size_t a_size);


template void
update_element<uint32_t>(uint32_t *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                         uint32_t new_val, size_t a_size);

template void
update_element_pull<uint32_t>(uint32_t *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                              uint32_t new_val, size_t a_size);

template void
update_element_push<uint32_t>(uint32_t *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                              uint32_t new_val, size_t a_size);

template auto
read_word<uint32_t>(const uint32_t *A, size_t a_size, size_t bit_start_index, size_t bit_end_index) -> uint32_t;

//template auto read_T_word<uint32_t>(const vector<bool> *v, size_t start, size_t end) -> uint32_t;



template
void vector_update_element_with_fixed_size<uint32_t>(vector<bool> *vec, size_t bit_start_pos, size_t bit_end_pos,
                                                     uint32_t new_val);

template
void vector_update_element_with_fixed_size<size_t>(vector<bool> *vec, size_t bit_start_pos, size_t bit_end_pos,
                                                   size_t new_val);

template void
vector_update_element<uint32_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                                uint32_t new_val);

template void
vector_update_element<size_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                              size_t new_val);


template void
vector_update_push<uint32_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                             uint32_t new_val);

template void
vector_update_push<size_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                           size_t new_val);

template void
vector_update_pull<uint32_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                             uint32_t new_val);


template void
vector_update_pull<size_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                           size_t new_val);

template void
read_k_words_fixed_length_att<uint32_t>(const uint32_t *A, size_t a_size, size_t first_element_index,
                                        size_t element_length,
                                        uint32_t *res_array, size_t k);

template void
read_k_words_fixed_length_att<size_t>(const size_t *A, size_t a_size, size_t first_element_index, size_t element_length,
                                      size_t *res_array, size_t k);


template
auto find_first_and_second_set_bits<uint32_t>(const uint32_t *a, size_t a_size) -> std::tuple<size_t, size_t>;*/
