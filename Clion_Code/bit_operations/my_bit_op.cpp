//
// Created by tomer on 3/15/20.
//

#include "my_bit_op.hpp"

template<typename T>
void find_kth_interval_simple(T *a, size_t a_size, size_t k, size_t *start, size_t *end) {
    if (k == 0) {
        *start = 0;
        *end = find_first_set_bit<T>(a, a_size);
        if (DB) cout << "h1" << endl;
        return;
    }

    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    for (int i = 0; i < a_size; ++i) {
        if (k == 1) {
            find_first_and_second_set_bits(&a[i], a_size - i, start, end);
            *start += (i) * slot_size;
            *end += (i) * slot_size;
            cout << "h2" << endl;
            return;
        }

        auto temp_counter = __builtin_popcount(a[i]);
        if (temp_counter == k) {
            *start = ((i + 1) * slot_size) - __builtin_ctz(a[i]);
            *end = find_first_set_bit(&a[i + 1], a_size - (i + 1)) + slot_size * (i + 1);
            cout << "h3" << endl;
            return;
        }
        if (temp_counter > k) {
            uint shift = select_r(a[i], k) - 32 + 1;
            *end = (i * slot_size) + shift + __builtin_clz(a[i] << (shift));
            *start = (i * slot_size) + shift;
            if (DB) cout << "h5" << endl;
            return;
/*
            return;
            T slot = a[i];
            T counter = 0;
            for (int j = 0; j < k; ++j) {
                auto shift = __builtin_clz(slot) + 1;
                assert(0 < shift < slot_size);
                slot <<= shift;
                assert(slot > 0);
                counter += (shift - 1);
            }
            *start = (i * slot_size) + (slot_size - (counter - 1) - 1);
            *end = (i * slot_size) + (slot_size - (counter + __builtin_ctz(slot)) - 1);
            if (DB) cout << "h5" << endl;
            return;
*/
        }
        k -= temp_counter;
        /*else if (temp_counter == k) {
            *start = (i * slot_size) + (slot_size - __builtin_ctz(a[i]) - 1);
            *end = find_first_set_bit<T>(&(a[i + 1]), a_size - (i + 1)) + slot_size * (i + 1);
            if (DB) cout << "h4: " << temp_counter << endl;
            return;*/
    }
    assert(false);
}

void word_k_select(uint32_t word, size_t k, size_t *start, size_t *end) {

}

template<typename T>
auto find_first_set_bit(T *a, size_t a_size) -> size_t {
    uint i = 0;
    while (a[i] == 0) i++;
    auto bit = __builtin_clz(a[i]);
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    return i * slot_size + bit;
}

template<typename T>
void find_first_and_second_set_bits(T *a, size_t a_size, size_t *first, size_t *second) {
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    uint i = 0;
    while (a[i] == 0) i++;
    auto bit = __builtin_clz(a[i]);
    T slot = a[i] << (bit + 1);
    if (slot) {
        auto length = __builtin_clz(slot);
        *first = i * slot_size + bit + 1;
        *second = i * slot_size + bit + 1 + length;
//        if (DB) cout << "h1" << endl;
        return;
    }
    *first = i * slot_size + bit + 1;
    while (a[++i] == 0);
    bit = __builtin_clz(a[i]);
    *second = i * slot_size + bit;
//    if (DB) cout << "h2" << endl;
    return;
}

auto count_set_bits(uint32_t *a, size_t a_size) -> size_t {
    size_t counter = 0;
    for (int i = 0; i < a_size; ++i) {
        counter += __builtin_popcount(a[i]);
    }
    return counter;
}


template<typename T>
void to_vector(vector<bool> *vec, const T *a, size_t a_size) {
    size_t bit_in_slot = (sizeof(a[0]) * CHAR_BIT);
    size_t vec_new_size = bit_in_slot * a_size, vec_index = 0;
    vec->resize(vec_new_size);
    for (size_t i = 0; i < a_size; ++i) {
        size_t b = 1ULL << (bit_in_slot - 1);
        for (size_t j = 0; j < bit_in_slot; ++j) {
            vec->at(vec_index) = (b & a[i]);
            b >>= 1ULL;
            vec_index++;
        }
    }
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


template size_t find_first_set_bit<uint32_t>(uint32_t *a, size_t a_size);

template void find_kth_interval_simple<uint32_t>(uint32_t *a, size_t a_size, size_t k, size_t *start, size_t *end);

template void to_vector<uint32_t>(vector<bool> *vec, const uint32_t *a, size_t a_size);