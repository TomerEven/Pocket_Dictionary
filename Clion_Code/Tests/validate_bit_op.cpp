//
// Created by tomer on 3/15/20.
//

#include "validate_bit_op.hpp"

auto validate_find_kth_interval_iter(size_t reps, size_t a_size) -> bool {
    uint32_t a[a_size];
    for (size_t j = 0; j < reps; ++j) {
        for (size_t i = 0; i < a_size; ++i) {
            a[i] = j;
        }
        auto set_bit_count = count_set_bits(a, a_size);
        for (int q = 0; q < set_bit_count; ++q) {
            bool res = validate_find_kth_interval_single(a, a_size, q);
            if (!res) {
                cout << "rep number " << j << endl;
                cout << "quot is " << q << endl;
                return false;
            }

        }
    }
    return true;
}


auto validate_find_kth_interval_random(size_t reps, size_t a_size) -> bool {
    uint32_t a[a_size];
    for (size_t j = 0; j < reps; ++j) {
        for (size_t i = 0; i < a_size; ++i) {
            a[i] = random();
        }
        auto set_bit_count = count_set_bits(a, a_size);
        uint32_t q = random() % set_bit_count;
//        cout << j << ":\t";
        if (!validate_find_kth_interval_single(a, a_size, q)) {
            cout << "Failed in the " << j << "'th rep." << endl;
            return false;
        }
    }
    return true;

}

auto validate_find_kth_interval_single(uint32_t *a, size_t a_size, size_t k) -> bool {
    size_t start = -1, end = -1, vec_start = -2, vec_end = -2;
    vector<bool> vec(a_size * sizeof(uint32_t) * CHAR_BIT);
    from_array_to_vector(&vec, a, a_size);
    vector_find_kth_interval_simple(&vec, k, &vec_start, &vec_end);

    find_kth_interval_simple(a, a_size, k, &start, &end);

    bool cond1 = (start == vec_start);
    bool cond2 = (end == vec_end);
    bool res = cond1 & cond2;

    if (res) return true;


    if (!cond1) { printf("start %zu, vec_start %zu\n", start, vec_start); }
    if (!cond2) { printf("end %zu, vec_end %zu\n", end, vec_end); }

    return false;
}

template<typename T>
auto validate_find_first_and_second_set_bits_iter(size_t reps, size_t a_size) -> bool {
    uint32_t a[a_size];
    for (size_t j = 0; j < reps; ++j) {
        for (size_t i = 0; i < a_size; ++i) { a[i] = j + 1; }

        bool res = validate_find_first_and_second_set_bits_single<T>(a, a_size);
        if (!res) {
            cout << "rep number " << j << endl;
            return false;
        }
    }
    return true;
}

template<typename T>
auto validate_find_first_and_second_set_bits_rand(size_t reps, size_t a_size) -> bool {
    uint32_t a[a_size];
    for (size_t j = 0; j < reps; ++j) {
        for (size_t i = 0; i < a_size; ++i) { a[i] = random(); }
//        auto set_bit_count = count_set_bits(a, a_size);
//        uint32_t q = random() % set_bit_count;
//        cout << j << ":\t";
        if (!validate_find_first_and_second_set_bits_single(a, a_size)) {
            cout << "rep number " << j << endl;
            size_t k = 0;
            while (a[k] == 0) k++;
            cout << a[k] << endl;
            return false;
        }
    }
    return true;

}

template<typename T>
auto validate_find_first_and_second_set_bits_single(T *a, size_t a_size) -> bool {
    size_t start = -1, end = -1, vec_start = -2, vec_end = -2;
    vector<bool> vec(a_size * sizeof(uint32_t) * CHAR_BIT);
    from_array_to_vector(&vec, a, a_size);
    vector_find_kth_interval_simple(&vec, 1, &vec_start, &vec_end);

    find_first_and_second_set_bits(a, a_size, &start, &end);

    bool cond1 = (start == vec_start);
    bool cond2 = (end == vec_end);
    bool res = cond1 & cond2;

    if (res) return true;


    if (!cond1) { printf("start %zu, vec_start %zu\n", start, vec_start); }
    if (!cond2) { printf("end %zu, vec_end %zu\n", end, vec_end); }

    return false;
}

template<typename T>
auto v_vec_and_array_transformation(size_t reps, size_t total_bits) -> bool {
    const size_t slot_size = sizeof(T) * CHAR_BIT;
    const size_t a_size = INTEGER_ROUND(total_bits, slot_size);
    T a[a_size];
    vector<bool> vec(total_bits);

    T b[a_size];
    vector<bool> vec2(total_bits);

    for (int i = 0; i < reps; ++i) {
        for (int j = 0; j < a_size; ++j) { a[j] = random(); }
//        print_array_as_integers(a, a_size);
        from_array_to_vector(&vec, a, a_size);
        from_vector_to_array(&vec, b, a_size);
        for (int k = 0; k < a_size; ++k) {
            if (a[k] != b[k]) {
                cout << "h1:" << endl;
                cout << "i is:" << i << endl;
                cout << "k is:" << i << endl;
                cout << a[k] << ", " << b[k] << endl;
                return false;
            }
        }
    }
//    cout << "mid" << endl;
    for (int i = 0; i < reps; ++i) {
        for (int j = 0; j < total_bits; ++j) { vec[j] = (random() % 2); }
//        print_vector(&vec);
        from_vector_to_array(&vec, a, a_size);
        from_array_to_vector(&vec2, a, a_size);
        for (int k = 0; k < total_bits; ++k) {
            if (vec[k] != vec2[k]) {
                cout << "h2:" << i << endl;
                return false;
            }
        }
    }
//    cout << "Pass" << endl;
    return true;
}


template auto validate_find_first_and_second_set_bits_single<uint32_t>(uint32_t *a, size_t a_size) -> bool;

template auto validate_find_first_and_second_set_bits_iter<uint32_t>(size_t reps, size_t a_size) -> bool;

template auto validate_find_first_and_second_set_bits_rand<uint32_t>(size_t reps, size_t a_size) -> bool;

template auto v_vec_and_array_transformation<uint32_t>(size_t reps, size_t total_bits) -> bool;