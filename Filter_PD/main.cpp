#include <iostream>
#include <iomanip>
#include <x86intrin.h>
#include "PD/Non_Contiguous_PD/Header.h"
#include "Hash_Table/hash_table.hpp"

#include "Filters/POW2C/pow2c_filter.h"
#include "Filters/POW2C/pow2c_naive_filter.h"

#include "Tests/Validation/validate_bit_op.hpp"
#include "Tests/Validation/validate_counters.hpp"
#include "Tests/Validation/validate_hash_table.hpp"
#include "Tests/Validation/validate_filter.hpp"
#include "Tests/Validation/validate_counter_PD.hpp"
#include "Tests/Validation/validate_counting_filter.hpp"
#include "Tests/Validation/validation_tests.h"

#include "Tests/Benchmarking/benchmark_counting_filter.hpp"
#include "Tests/Benchmarking/benchmark_tests.h"


//todo: naive pow2c_naive_filter validation. benchmark comparing. profiling.
using namespace std;

void using_cuckoo_table();

void t_read_k_word_rand();

void t_HT();

void t_cg_PD();

void use_of_validate_PD(size_t reps);

void all();

void test_multi_dict();

void example_of_CF_rates_wrapper();

enum dict_types {
    basic, counting//, cuckoo_dict
};


int main(int argc, char **argv) {

//    example_of_CF_rates_wrapper();

    dict_types temp_type;
    size_t max_distinct_capacity;
    size_t error_prob_exponent;
    size_t number_of_lookups_to_preform;
    size_t level1_counter_size;
    size_t level2_counter_size;
    double level_1_load_factor;
    double level_2_load_factor;

    char *end;
    if (argc == 2) {
        temp_type = (dict_types) std::strtol(argv[1], &end, 10);
        max_distinct_capacity = 1u << 15u;
        error_prob_exponent = 6;
        number_of_lookups_to_preform = 1u << 18u;
        level1_counter_size = 3;
        level2_counter_size = 7;
        level_1_load_factor = .95;
        level_2_load_factor = .5;
    } else if (argc == 5) {

        temp_type = (dict_types) std::strtol(argv[1], &end, 10);
        max_distinct_capacity = std::strtol(argv[2], &end, 10);
        error_prob_exponent = std::strtol(argv[3], &end, 10);
        number_of_lookups_to_preform = std::strtol(argv[4], &end, 10);

        level1_counter_size = 3, level2_counter_size = 7;
        level_1_load_factor = 0.95, level_2_load_factor = 0.5;
    } else if (argc == 9) {
        temp_type = (dict_types) std::strtol(argv[1], &end, 10);
        max_distinct_capacity = std::strtol(argv[2], &end, 10);
        error_prob_exponent = std::strtol(argv[3], &end, 10);
        number_of_lookups_to_preform = std::strtol(argv[4], &end, 10);

        level1_counter_size = std::strtol(argv[5], &end, 10);
        level2_counter_size = std::strtol(argv[6], &end, 10);
        level_1_load_factor = std::strtod(argv[7], &end);
        level_2_load_factor = std::strtod(argv[8], &end);

    } else {
        std::cout << "Wrong number of arguments." << std::endl;
        return 1;
    }

    switch (temp_type) {
        case basic:
            CF_rates_wrapper<dict32>(max_distinct_capacity, number_of_lookups_to_preform, error_prob_exponent,
                                     level1_counter_size,
                                     level2_counter_size, level_1_load_factor, level_2_load_factor, cout);
            return 0;
        case counting:
            CF_rates_wrapper<multi_dict64>(max_distinct_capacity, number_of_lookups_to_preform, error_prob_exponent,
                                           level1_counter_size,
                                           level2_counter_size, level_1_load_factor, level_2_load_factor, cout);
            return 0;
            /*case cuckoo_dict:
                CF_rates_wrapper<cuckoofilter::>(max_distinct_capacity, number_of_lookups_to_preform, error_prob_exponent, level1_counter_size,
                                               level2_counter_size, level_1_load_factor, level_2_load_factor, cout);
                return 0*/
        default:
            std::cout << "Unknown type" << std::endl;
            return 1;
    }

=======

int main(int argc, char **argv) {

    example_of_CF_rates_wrapper();

    dict_types temp_type;
    size_t max_distinct_capacity;
    size_t error_prob_exponent;
    size_t number_of_lookups_to_preform;
    size_t level1_counter_size;
    size_t level2_counter_size;
    double level_1_load_factor;
    double level_2_load_factor;

    char *end;
    if (argc == 2) {
        temp_type = (dict_types) std::strtol(argv[1], &end, 10);
        max_distinct_capacity = 1u << 15u;
        error_prob_exponent = 6;
        number_of_lookups_to_preform = 1u << 18u;
        level1_counter_size = 3;
        level2_counter_size = 7;
        level_1_load_factor = .95;
        level_2_load_factor = .5;
    } else if (argc == 5) {

        temp_type = (dict_types) std::strtol(argv[1], &end, 10);
        max_distinct_capacity = std::strtol(argv[2], &end, 10);
        error_prob_exponent = std::strtol(argv[3], &end, 10);
        number_of_lookups_to_preform = std::strtol(argv[4], &end, 10);

        level1_counter_size = 3, level2_counter_size = 7;
        level_1_load_factor = 0.95, level_2_load_factor = 0.5;
    } else if (argc == 9) {
        temp_type = (dict_types) std::strtol(argv[1], &end, 10);
        max_distinct_capacity = std::strtol(argv[2], &end, 10);
        error_prob_exponent = std::strtol(argv[3], &end, 10);
        number_of_lookups_to_preform = std::strtol(argv[4], &end, 10);

        level1_counter_size = std::strtol(argv[5], &end, 10);
        level2_counter_size = std::strtol(argv[6], &end, 10);
        level_1_load_factor = std::strtod(argv[7], &end);
        level_2_load_factor = std::strtod(argv[8], &end);

    } else {
        std::cout << "Wrong number of arguments." << std::endl;
        return 1;
    }

    switch (temp_type) {
        case basic:
            CF_rates_wrapper<dict32>(max_distinct_capacity, number_of_lookups_to_preform, error_prob_exponent,
                                     level1_counter_size,
                                     level2_counter_size, level_1_load_factor, level_2_load_factor, cout);
            return 0;
        case counting:
            CF_rates_wrapper<multi_dict64>(max_distinct_capacity, number_of_lookups_to_preform, error_prob_exponent,
                                           level1_counter_size,
                                           level2_counter_size, level_1_load_factor, level_2_load_factor, cout);
            return 0;
            /*case cuckoo_dict:
                CF_rates_wrapper<cuckoofilter::>(max_distinct_capacity, number_of_lookups_to_preform, error_prob_exponent, level1_counter_size,
                                               level2_counter_size, level_1_load_factor, level_2_load_factor, cout);
                return 0*/
        default:
            std::cout << "Unknown type" << std::endl;
            return 1;
    }

>>>>>>> 24fe58bed803bee636acdd25b655e05f85eb57d6

}


void example_of_CF_rates_wrapper() {
<<<<<<< HEAD
    ulong shift = 16u;
=======
    ulong shift = 12u;
>>>>>>> 24fe58bed803bee636acdd25b655e05f85eb57d6
    size_t reps = 1u << (shift + 3u), max_distinct_capacity = 1u << shift;
    size_t remainder_length = 13;
    size_t l1_counter_size = 3, l2_counter_size = 7;
    double l1_LF = 0.95, l2_LF = 0.65;


    CF_rates_wrapper<multi_dict64>(max_distinct_capacity, reps, remainder_length, l1_counter_size,
                                   l2_counter_size, l1_LF, l2_LF, cout);
}

void use_of_validate_PD(size_t reps) {
    bool passed = true;
    for (int i = 0; i < 256; ++i) {
        passed &= namePD::validate_PD<cg_PD>(reps, true, false);

    }
    cout << passed << endl;
}

void using_cuckoo_table() {
    /*libcuckoo::cuckoohash_map<int, std::string> Table;

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
    }*/
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
        res = namePD::validate_PD<cg_PD>(1u << 10u, true, false);
        res &= namePD::validate_PD_higher_load<cg_PD>(1u << 10u, .8, true, 0);
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


void test_multi_dict() {
    size_t reps = 1u << 16u, max_distinct_capacity = 1u << 16u;
    size_t remainder_length = 13;
    size_t l1_counter_size = 4, l2_counter_size = 8;
    double l1_LF = 0.85, l2_LF = 0.25;

    auto res2 = v_CF_wrapper<multi_dict64>(max_distinct_capacity, reps, remainder_length, l1_counter_size,
                                           l2_counter_size, l1_LF, l2_LF);
    assert(res2);

    auto s_res2 = v_CF_wrapper<safe_multi_dict64>(max_distinct_capacity >> 6u, reps >> 6u, remainder_length,
                                                  l1_counter_size,
                                                  l2_counter_size, l1_LF, l2_LF);
    assert(s_res2);

    assert(v_CF_wrapper<multi_dict64>(max_distinct_capacity, reps, remainder_length, l1_counter_size, l2_counter_size,
                                      l1_LF, l2_LF, 32u));

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




//    std::cout << "Hello, World!" << std::endl;

/*
size_t reps = 1u << 15u, max_distinct_capacity = 1u << 14u;
size_t remainder_length = 7;
size_t l1_counter_size = 3, l2_counter_size = 7;
double l1_LF = 0.95, l2_LF = 0.65;
w_validate_filter<dict32>(max_distinct_capacity, reps, remainder_length, l1_LF, l2_LF);
*/
//
//    CF_rates_wrapper<dict32>(max_distinct_capacity, reps, remainder_length, l1_counter_size,
//                             l2_counter_size, l1_LF, l2_LF, cout);

/*
    cout << string(32, '*') << endl;
    cout << string(32, '*') << endl;
    example_of_CF_rates_wrapper();
    cout << string(32, '*') << endl;
    cout << string(32, '*') << endl;
    CF_rates_wrapper<dict32>(max_distinct_capacity, reps, remainder_length, l1_counter_size,
                             l2_counter_size, l1_LF, l2_LF, cout);
    cout << string(32, '*') << endl;
    cout << string(32, '*') << endl;
    example_of_CF_rates_wrapper();
*/

/* size_t pd_num = 1ul << 14ul, fp_size = 13, m = 32, pd_capacity = 32, lookup_reps = 1ULL << 21ul;
auto load_factor = 0.88;
stringstream s;
cuckoo_filter_rates(pd_num, load_factor, pd_capacity, m, fp_size, 1ULL << 12ul, s);

cout << string(32, '*') << endl;
*/
/*
example_of_CF_rates_wrapper();
*/
//    std::cout << "End!" << std::endl;
