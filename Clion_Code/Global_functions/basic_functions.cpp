//
// Created by tomer on 10/25/19.
//

#include "basic_functions.h"

void print_array(uint32_t *a, size_t a_size) {
    cout << "[" << a[0];
    for (size_t i = 1; i < a_size; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;

}

void print_array(int *a, size_t a_size) {
    cout << "[" << a[0];
    for (size_t i = 1; i < a_size; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;

}

void print_bool_array(bool *a, size_t a_size) {
    cout << "[" << a[0];
    for (size_t i = 0; i < a_size; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}


void print_array_as_consecutive_memory(uint32_t *a, size_t a_size) {
    for (size_t i = 0; i < a_size; ++i) {
        cout << my_bin(a[i]);
    }
    cout << endl;
}

void print_vector(vector<int> *v) {
    cout << "[" << v->at(0);
    for (size_t i = 1; i < v->size(); ++i) {
        cout << ", " << v->at(i);
    }
    cout << "]" << endl;

}

void print_vector(vector<bool> *v) {
    cout << "[" << v->at(0);
    for (size_t i = 1; i < v->size(); ++i) {
        cout << ", " << v->at(i);
    }
    cout << "]" << endl;

}

void print_vector_by_unpacking(vector<bool> *v, size_t unpack_size) {
    size_t a_size = v->size() / unpack_size + (v->size() % unpack_size != 0);
    uint32_t a[a_size];
    assert(unpack_size <= 32);
    for (size_t i = 0; i < a_size; ++i) {
        a[i] = read_FP_from_vector_by_index(v, i * unpack_size, unpack_size);
    }
    print_array(a, a_size);
}

void print_vector_as_words(const vector<bool> *v) {
    size_t number_of_words = (v->size() / 32) + (v->size() % 32 != 0);
    uint32_t a[number_of_words];
    for (size_t j = 0; j < number_of_words; ++j) {
        a[j] = 0;
    }
    vector_to_word_array(v, a, number_of_words);

    print_array(a, number_of_words);
    /*cout << "[" << a[0];
    for (size_t i = 1; i < number_of_words; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;*/
}

void print_bool_vector_no_spaces(vector<bool> *v) {
    for (auto b : *v)
        cout << b;
    cout << endl;
}

void to_vector(vector<bool> *vec, const uint32_t *a, size_t a_size) {
    size_t bit_in_slot = (sizeof(a[0]) * 8);
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

void to_vector(vector<bool> *vec, const uint8_t *a, size_t a_size) {
    size_t bit_in_slot = (sizeof(a[0]) * 8);
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

void vector_to_word_array(const vector<bool> *v, uint32_t *a, size_t a_size) {
    size_t expected_size = (v->size() / 32) + (v->size() % 32 != 0);
    assert(a_size == expected_size);
    for (size_t i = 0; i < a_size - 1; ++i) {
        ulong b = (1ul << 31ul);
        for (int j = 0; j < 32; ++j) {
            assert(b > 0);
            if (v->at(32 * i + j)) {
                a[i] |= b;
            }
            b >>= 1ul;
        }
    }
    ulong b = (1ul << 31ul);
    for (size_t k = 0; k < v->size() % 32; ++k) {
        if (v->at(32 * (a_size - 1) + k)) {
            a[a_size - 1] |= b;
        }
        b >>= 1ul;
    }
}

uint32_t read_FP_from_vector_by_index(vector<bool> *v, size_t bit_start_index, size_t fp_size) {
    assert(bit_start_index + fp_size <= v->size());

//    BODY_BLOCK_TYPE res = v->at(bit_start_index);
    uint32_t res = 0;
    for (size_t i = 0; i < fp_size; ++i) {
        res <<= 1ul;
        res |= v->at(bit_start_index + i);
    }
    return res;
}

void write_FP_to_vector_by_index(vector<bool> *v, size_t index, uint32_t remainder, size_t fp_size) {
    assert(index + fp_size <= v->size());

    ulong b = 1ULL << (fp_size - 1);
    for (size_t i = 0; i < fp_size; ++i) {
        v->at(index + i) = (remainder & b) != 0;
        b >>= 1ul;
    }
}



string my_bin(size_t n, size_t length) {
    string s = "";
    ulong b = 1ull << (ulong) (32 - 1);
    for (int i = 0; i < 32; ++i) {
        if (b & n)
            s.append("1");
        else
            s.append("0");
        b >>= 1ul;
    }
//    cout << s << endl;
    return s;
}

int loglog2(int x) {
    log(x);
}

