//
// Created by tomer on 10/29/19.
//

#include "v_Header.h"

v_Header::v_Header(size_t m, size_t f, size_t l) : header(m, f, l) {
    size_t number_of_bits = ((m + f) << 1ULL) + 1;
    if (HEADER_BLOCK_SIZE != (8 * sizeof(HEADER_BLOCK_TYPE))) {
        assert(false);
    }
    this->vec.resize(number_of_bits);

}

bool v_Header::lookup(uint_fast16_t quotient, size_t *start_index, size_t *end_index) {
    validate_get_interval(quotient);
    header.get_quotient_start_and_end_index(quotient, start_index, end_index);
    return *start_index != *end_index;
}

void v_Header::insert(uint_fast16_t quotient, size_t *start_index, size_t *end_index) {
    validate_get_interval(quotient);
    header.insert(quotient, start_index, end_index);
    vector_insert(quotient);
    validate_get_interval(quotient);
}

void v_Header::remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index) {
    validate_get_interval(quotient);
    header.remove(quotient, start_index, end_index);
    vector_remove(quotient);
    validate_get_interval(quotient);
}

void v_Header::vector_get_interval(size_t quotient, size_t *start_index, size_t *end_index) {
    size_t zero_counter = -1, continue_from_index = 0;

    for (size_t i = 0; i < vec.size(); ++i) {
        if (zero_counter == quotient - 1) {
            *start_index = i;
            continue_from_index = i;
            break;
        }
        if (vec[i] == 0)
            zero_counter++;
    }

    for (size_t i = continue_from_index; i < vec.size(); ++i) {
        if (vec[i] == 0) {
            *end_index = i;
            return;
        }
    }
    assert(false);
}

void v_Header::vector_insert(size_t quotient) {
    size_t a = -1, b = -1;
    this->vector_get_interval(quotient, &a, &b);
    vec.insert(vec.begin() + a, true);
    vec.pop_back();
}

void v_Header::vector_remove(uint_fast16_t quotient) {
    size_t a = -1, b = -1;
    this->vector_get_interval(quotient, &a, &b);
    assert(a < b);
    vec.erase(vec.begin() + a);
    vec.push_back(false);
}


void v_Header::validate_get_interval(size_t quotient) {
    size_t va = -1, vb = -1, c = -1, d = -1;
    vector_get_interval(quotient, &va, &vb);
    get_interval_attempt(header.get_h(), header.get_size(), quotient, &c, &d);
    bool cond2 = (c == va) && (d == vb);
    if (not cond2) {
        cout << "header as word is: ";
        header.print_as_word();
        cout << "vector as word is: ";
        print_vector_as_words(&vec);

    }
    assert(c == va);
    assert(d == vb);
}
