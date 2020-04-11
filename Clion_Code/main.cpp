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
#include "Hash_Table/cuckoohash_map.hh"
#include "Hash_Table/hash_table.hpp"
#include "Tests/validate_hash_table.hpp"
#include "Tests/validate_filter.hpp"
#include "Tests/validate_counter_PD.hpp"


//todo: naive pow2c_naive_filter validation. benchmark comparing. profiling.
#define CUCKOO_R (8)
using namespace std;

void using_cuckoo_table();

void t_read_k_word_rand();

void t_HT();

void t_cg_PD();

void use_of_validate_PD(size_t reps);

void all();

int main() {
    std::cout << "Hello, World!" << std::endl;
//    all();

    size_t reps = 1u<<10u, max_distinct_capacity = 256;
    size_t remainder_length = 13, counter_size = 5;
    for (int i = 0; i < 10; ++i) {
        v_wrapper_single(max_distinct_capacity, remainder_length, counter_size, (i+1) * 0.1, false);
        cout << i << endl;
    }


    /*for (int j = 0; j < 32 - remainder_length; ++j) {
        auto res = op_sequence_iter(reps, max_distinct_capacity, remainder_length + j, counter_size + j / 4, .25, 1, false);
        assert(res);
        cout << j << endl;
    }*/





    std::cout << "End!" << std::endl;
    return 0;
}


void use_of_validate_PD(size_t reps) {
    bool passed = true;
    for (int i = 0; i < 256; ++i) {
        passed &= validate_PD<cg_PD>(reps, true, false);

    }
    cout << passed << endl;
}

void using_cuckoo_table() {
    libcuckoo::cuckoohash_map<int, std::string> Table;

    for (int i = 0; i < 100; i++) {
        Table.insert(i, "hello");
    }

    for (int i = 0; i < 101; i++) {
        std::string out;

        if (Table.find(i, out)) {
            std::cout << i << "  " << out << std::endl;
        } else {
            std::cout << i << "  NOT FOUND" << std::endl;
        }
    }
}

void t_read_k_word_rand() {
    size_t reps = 128;
    for (int el_length = 7; el_length < 33; ++el_length) {
        assert(v_read_k_words_fixed_length_rand<uint32_t>(128, el_length));
    }
}

void t_HT() {
    const size_t max_capacity = 1u << 10u, element_length = 28, bucket_size = 4;
    size_t reps = 1u << 14u;
    auto load_factor = .75;
    double working_LF = .72;
    double variance = .1;

    v_hash_table_rand_gen_load(reps, max_capacity, element_length, 2, load_factor, working_LF, variance);
    cout << "\n\n\n" << endl;
    v_hash_table_rand_gen_load(reps, max_capacity, element_length, 4, load_factor, working_LF, variance);
    cout << "\n\n\n" << endl;
    v_hash_table_rand_gen_load(reps, max_capacity, element_length, 8, load_factor, working_LF, variance);
    cout << "\n\n\n" << endl;
    v_hash_table_rand_gen_load(reps, max_capacity, element_length, 12, load_factor, working_LF, variance);
}

void t_cg_PD() {
    bool res = 0;
    for (int i = 0; i < 16; ++i) {
        res = validate_PD<cg_PD>(1u << 10u, true, false);
        res &= validate_PD_higher_load<cg_PD>(1u << 10u, .8, true, 0);
        assert (res);
    }
}

void t_from_array_to_bit_vector_by_bit_limits() {
    for (int i = 0; i < 16; ++i) {
        assert(v_from_array_to_vector_by_bit_limits_rand<uint32_t>(1u << 4u, 16, true));
        cout << i << endl;
    }
}

void t_from_array_to_bit_vector_by_bit_limits();


void all() {
    using_cuckoo_table();
    cout << "pass" << endl;
    t_read_k_word_rand();
    cout << "pass" << endl;
//    t_HT();
//    cout << "pass" << endl;
    t_cg_PD();
    cout << "pass" << endl;
    use_of_validate_PD(1u << 6u);
    cout << "pass" << endl;
}




/*
//    bool res = 0;
//    res = validate_CPD<CPD>(1u << 10u, false, true);

//    for (int i = 0; i < 32; ++i) {
//        cout << i << endl;
//        bool res = validate_CPD<CPD>(1u << 10u, true, false);
//        assert (res);
//    }
//    assert(res);
*/
/*const size_t max_capacity = 1u << 14u, element_length = 28, bucket_size = 4;
size_t reps = 1u << 14u;
auto load_factor = .75;
double working_LF = .72;
double variance = .1;
for (int i = 0; i < 8; ++i) {
    srand(i);
    auto res = v_filter<dict<cg_PD, hash_table<uint32_t> > >(max_capacity, max_capacity<< 2u, 13, .75, .5);
    assert(res);
}*/

/*uint32_t a = 1;
hash_table<uint32_t> t(max_capacity, element_length, bucket_size, load_factor);
assert(t.find(a) == 0);
t.insert(a);
assert(t.find(a) == 1);
t.remove(a);
assert(t.find(a) == 0);*/

/*
v_hash_table_rand_gen_load(reps, max_capacity, element_length, 1, load_factor, working_LF, variance);
cout << "\n\n\n" << endl;
cout << "\n\n\n" << endl;

v_hash_table_rand(1u << 14u, max_capacity, element_length, 4, load_factor);
cout << "1" << endl;
v_hash_table_rand(1u << 14u, max_capacity, element_length, 2, load_factor);
cout << "2" << endl;
v_hash_table_rand(1u << 14u, max_capacity, element_length, 16, load_factor);
cout << "4" << endl;
v_hash_table_rand(1u << 14u, max_capacity, element_length, 8, load_factor);
cout << "5" << endl;
v_hash_table_rand(1u << 14u, max_capacity, element_length, 1, load_factor);
cout << "3" << endl;
*/

/*assert(v_vector_update_rand(1u<<12u));
assert(v_update_by_comparison_rand<uint32_t>(1u<<8u,8u));
for (int i = 0; i < 256; ++i) {
    srand(i);
    assert(v_update_by_comparison_rand<uint32_t>(1u<<8u,8u));
}
assert(v_vector_update_rand(1u<<12u));
assert(v_update_element_iter<uint32_t>(1u<<8u, 1u << 5u));*/

/*
 * assert(v_update_element_rand<uint32_t>(1u << 4u, 1u << 5u));
 * */

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

