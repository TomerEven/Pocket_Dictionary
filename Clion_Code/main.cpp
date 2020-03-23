#include <iostream>
#include <iomanip>
#include <x86intrin.h>
#include "PD/Header.h"
#include "Tests/validation_tests.h"
#include "POW2C/pow2c_filter.h"
#include "Tests/benchmark_tests.h"
#include "Tests/validate_bit_op.hpp"
#include "Tests/validate_counters.hpp"
#include "POW2C/pow2c_naive_filter.h"


//todo: naive pow2c_naive_filter validation. benchmark comparing. profiling.
#define CUCKOO_R (8)
using namespace std;


int main() {
    std::cout << "Hello, World!" << std::endl;
/*
    uint64_t x = 0x5555;
    uint32_t y = 0x5555;
//    x <<= 4u;
    cout << x << endl;
    cout << select_r(x, 0) << endl;
    cout << select_r(y, 0) << endl;
    cout << select_r(x, 1) << endl;
    cout << select_r(y, 1) << endl;
    cout << select_r(x, 7) << endl;
    cout << select_r(y, 7) << endl;
    cout << select_r(x, 8) << endl;
    cout << select_r(y, 8) << endl;
//    cout << select_r(x, 80) << endl;*/
    /*assert(v_get_symbols_length_difference(1u << 10u));
    assert(v_vec_and_array_transformation<uint32_t>(1u << 8u, 1u << 8u));
    assert(v_update_element_with_fixed_size_rand<uint32_t>(1u << 10u, 1u << 5u));*/
//    assert(v_vector_update_rand(1u<<12u));
    assert(v_update_by_comparison_rand<uint32_t>(1u<<8u,8u));
    for (int i = 0; i < 16; ++i) {
        srand(i);
        assert(v_update_by_comparison_rand<uint32_t>(1u<<8u,8u));
    }
//    assert(v_vector_update_rand(1u<<12u));
//    assert(v_update_element_iter<uint32_t>(1u<<8u, 1u << 5u));
//    assert(v_update_element_rand<uint32_t>(1u << 4u, 1u << 5u));


    /*for (int i = 0; i < (4u); ++i) {
        srand(clock());
        assert(v_extract_symbol_rand<uint32_t>(1u<<8u,8));
    }*/
/*
    assert(v_extract_symbol_rand<uint32_t>(1u<<8u,8));
    assert(validate_find_first_and_second_set_bits_iter<uint32_t >(1u << 10u, 4));
    assert(validate_find_first_and_second_set_bits_rand<uint32_t >(1u << 10u, 4));
    assert(validate_find_kth_interval_iter(1u << 8u, 4));
    assert(validate_find_kth_interval_random(1u << 12u, 8));
*/

    std::cout << "End!" << std::endl;
    return 0;
}
/*
int main() {
    std::cout << "Hello, World!" << std::endl;
//
*//*


    size_t pd_num = 1u << 10u, m = 128, f = 128, l = 7;
    size_t reps = (1u << (l + 2u)) * pd_num;
    float load_factor = 0.5;
*//*
*//*

    for (int i = 0; i < 16; ++i) {
        bool res = validate_PD_higher_load<PD>(128, 0.75, true);
        if (not res) {
            cout << endl;
            cout << i << endl;
            assert(false);
        }
        res = validate_PD_higher_load<cg_PD>(128, 0.75, true);
        if (not res) {
            cout << endl;
            cout << i << endl;
            assert(false);
        }
    }
*//**//*


//    }
//    return 0;
//
//    cout << validate_filter<gen_2Power<cg_PD>>(pd_num, load_factor, m + 1, f, l, reps) << endl;
//    assert(validate_filter<const_filter>(pd_num, load_factor, m + 1, f, l, reps));
//    assert(validate_filter<pow2c_naive_filter>(pd_num, load_factor, m + 1, f, l, reps));
    assert(validate_filter<pow2c_filter>(pd_num, load_factor, m + 1, f, l, reps));
    assert(validate_filter<gen_2Power<cg_PD>>(pd_num, load_factor, m + 1, f, l, reps));

    cout << endl;
    stringstream s;
    pd_num = 1ul << 12ul;
    size_t fp_size = 8, pd_capacity = 64, lookup_reps = 1ULL << 14ul;
    m = pd_capacity;
    load_factor = 0.65;

//    filter_fp_rates<pow2c_filter>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    cout << "\n\n\n" << endl;
//    filter_fp_rates<pow2c_naive_filter>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    cout << "\n\n\n" << endl;
//    filter_fp_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    cout << "\n\n\n" << endl;


//    for (int i = 0; i < 32; ++i) {
////        filter_rates_simple_pd(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//        filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//        filter_rates<gen_2Power<PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//        cout << endl;
//    }
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    cout << "\n\n\n\n" << endl;
    filter_rates_simple_pd(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates_simple_pd(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates_simple_pd(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates_simple_pd(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates_simple_pd(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    cout << "\n\n\n\n" << endl;
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
*//*

//    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    filter_rates<gen_2Power<cg_PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    filter_rates<gen_2Power<PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    filter_rates<gen_2Power<PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    filter_rates<gen_2Power<PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    filter_rates<gen_2Power<PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
//    filter_rates<gen_2Power<PD>>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);

    *//*

    assert(validate_const_PD(128, 0));
//    assert(validate_get_interval_function_constant(128));
    assert(validate_PD_single_run(128, 0));

    size_t pd_num = 64, m = 128, f = 128, l = 9;
    float load_factor = 0.85;
    assert(filter_naive_r0(pd_num, load_factor, m + 1, f, l));
    assert(const_filter_r0(pd_num, load_factor, l));
    assert(filter_r0(pd_num, load_factor, m, f, l));


    cout << endl;
    stringstream s;
    pd_num = 1ul << 12ul;
    size_t fp_size = 5, pd_capacity = 64, lookup_reps = 1ULL << 14ul;
    m = pd_capacity;
    load_factor = 0.85;

    filter_fp_rates<pow2c_filter>(pd_num, load_factor, m, pd_capacity, fp_size, lookup_reps, cout);
    cout << endl;
    cout << endl;
    filter_fp_rates<pow2c_naive_filter>(pd_num, load_factor, m, f, l, lookup_reps, cout);
//    filter_fp_rates<const_filter>(pd_num, load_factor, m + 1, f, l, lookup_reps, cout);
//    cout << endl;
//    cout << endl;

//    for (int i = 0; i < 16; ++i) {
//        filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
//        const_filter_rates32(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
//        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
//        cout << endl;
//    }

//

*//*

    std::cout << "End!" << std::endl;
    return 0;
}*/

/*
    stringstream s;
    size_t pd_num = 1ul << 10ul, fp_size = CUCKOO_R, m = 32, pd_capacity = 32, lookup_reps = 1ULL << 12ul;
    auto load_factor = 0.88;
    for (int i = 0; i < 16; ++i) {
        const_filter_rates32(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
//        cout << endl;
    }
*/

/*

    for (int i = 0; i < 11; ++i) {
        auto load_factor = (i) * (0.1);
//        cout << "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU" << endl;
        cout << "load_factor is: " << load_factor << ". " << endl;
//        b0(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 13ul, s);
//        b0(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 13ul, s);
//        b0(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 13ul, s);
//        b0(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 13ul, s);
//        b0(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 13ul, s);
//        cout << endl;
//        const_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        const_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        const_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        const_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        const_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        cout << endl;
        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
        cout << endl;
//        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);
//        b0(pd_num, load_factor, pd_capacity, m, fp_size, pd_capacity * pd_num, s);
//        cout << "----------------------------------------------------------------" << endl;
//        b0_naive(pd_num, load_factor, pd_capacity, m, fp_size, pd_capacity * pd_num, s);
//        cout << "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" << endl;
    }
*/


void use_of_validate_PD(size_t reps) {
    bool passed = true;
    for (int i = 0; i < 256; ++i) {
        passed &= validate_PD<cg_PD>(reps, true, false);

    }
    cout << passed << endl;
}