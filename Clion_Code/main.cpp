#include <iostream>
#include <iomanip>
#include <x86intrin.h>
#include "PD/Header.h"
#include "Tests/validation_tests.h"
#include "POW2C/pow2c_filter.h"
#include "Tests/benchmark_tests.h"
#include "POW2C/pow2c_naive_filter.h"
//todo: naive pow2c_naive_filter validation. benchmark comparing. profiling.

#define CUCKOO_R (8)
using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    assert(validate_const_PD(128, 0));
    assert(validate_get_interval_function_constant(128));
    assert(validate_PD_single_run(128, 0));

    size_t pd_num = 64, m = 128, f = 128, l = 9;
    float load_factor = 0.85;
    assert(filter_naive_r0(pd_num, load_factor, m + 1, f, l));
    assert(const_filter_r0(pd_num, load_factor, l));
    assert(filter_r0(pd_num, load_factor, m, f, l));

    stringstream s;
    pd_num = 1ul << 14ul, m = 32;
    size_t fp_size = CUCKOO_R, pd_capacity = 32, lookup_reps = 1ULL << 20ul;
    load_factor = 0.85;
    for (int i = 0; i < 16; ++i) {
        filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
        const_filter_rates32(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
        cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, lookup_reps, s);
        cout << endl;
    }

//


    std::cout << "End!" << std::endl;
    return 0;
}

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
