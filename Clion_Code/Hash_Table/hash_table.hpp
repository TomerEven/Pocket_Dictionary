/*Todo: I assumed */

#ifndef CLION_CODE_HASH_TABLE_HPP
#define CLION_CODE_HASH_TABLE_HPP

#include <iostream>
#include <zconf.h>
#include <vector>
#include <cstdint>
#include <cassert>
#include <ostream>
#include <cmath>
#include "../Global_functions/macros.h"
#include "../Hash/static_hashing.h"
#include "../bit_operations/my_bit_op.hpp"
//#include "../Hash/hashutil/hashutil.h"

#define EMPTY (0x80000000)
#define DELETED (0xc0000000)
#define MAX_CUCKOO_LOOP (1u<<10u)
#define DEFAULT_BUCKET_SIZE (4)
#define DEFAULT_MAX_LOAD_FACTOR (.5)

//#define FREE_IND (0x80000000)
//#define IS_FREE(x) ((x & MASK(31u)) == 0)

template<typename T>
class hash_table {
    T *table;
    const size_t table_size{}, max_capacity{}, element_length{}, bucket_size{};
    size_t capacity{};
    const double max_load_factor{};
    const uint32_t seed1{}, seed2{};

    ////validation parameters.

    /** "max_cuckoo_insert" is used to store the maximal length of a cuckoo chain occurred during an insertion.*/
    size_t max_cuckoo_insert{};
    /** "cuckoo_insert_counter" is used to measure the total length of cuckoo chain occurred during all insertion.
     * The measure over single insertion "I_1", equal to the length of the cuckoo chain this insertion caused,
     * multiplied by the size of a bucket.
     */
    size_t cuckoo_insert_counter{};

    size_t max_capacity_reached{};


public:
    hash_table(size_t max_capacity, size_t element_length, size_t bucket_size, double max_load_factor);

    hash_table(size_t number_of_pd, size_t quotient_range, size_t single_pd_capacity, size_t remainder_length);

    void insert(T x);

    void full_buckets_handler(T x, size_t b1, size_t b2);

    void insert_without_counter(T x);

    void pop_attempt(T x);

    void remove(T x);

    auto find(T x) -> bool;

    auto find_table_location(T x) -> size_t;

    virtual ~hash_table();

    ////validation
    auto is_state_valid() -> bool;

    auto is_bucket_elements_unique(size_t bucket_index) -> bool;

    auto get_max_cuckoo_insert() const -> size_t;

    auto get_cuckoo_insert_counter() const -> size_t;

    auto get_max_capacity_reached() const -> size_t;

    void get_data();

private:

    hash_table(size_t max_capacity, size_t element_length) {
        cout << "Const 2" << endl;
        hash_table(max_capacity, element_length, DEFAULT_BUCKET_SIZE, DEFAULT_MAX_LOAD_FACTOR);
    }

    auto insert_helper(T x, size_t bucket_index);

    auto find_helper(T x, size_t bucket_index) -> bool;

    auto find_helper_table_location(T x, size_t bucket_index) -> int;

    auto remove_helper(T x, size_t bucket_index) -> bool;

    /**
     * Tries to insert "x" to bucket in "bucket_index".
     * If the bucket is not full, x will be inserted, and true will be returned.
     * Otherwise, x was not inserted, and false will be returned.
     * @param x
     * @param bucket_index
     * @return
     */
    auto insert_if_bucket_not_full(T x, size_t bucket_index) -> bool;


    /**
     *
     * @param with_counter
     * @param without_counter
     * @return compares x,y first "element length" bits.
     */
    auto is_equal(T with_counter, T without_counter) -> bool;

    auto is_empty(size_t table_index) -> bool;

    auto is_deleted(size_t table_index) -> bool;

    auto get_bucket_capacity(size_t bucket_index) -> size_t;

    /**
     * This function is called whenever an element is trying to be inserted into full bucket.
     * It tries to move one of the elements in "bucket_index" to it's other possible location (cuckoo scheme).
     * If it succeed, a pointer to a free location will be returned.
     * Otherwise, a null pointer will be returned.
     * @param bucket_index The bucket from whom elements will try to be moved.
     * @return pointer to the free location.
     */
    auto move_el_from_bucket_to_other(size_t bucket_index) -> T *;

//    inline void my_hash(T x, uint32_t *i1, uint32_t *i2) {
//        *i1 = hashint(x);
//        *i2 = hashint2(x);
//    }

    inline void my_hash(T x, uint32_t *b1, uint32_t *b2) {
        size_t number_of_buckets_in_each_table = (table_size / bucket_size) / 2;
        *b1 = (hashint(x)) % number_of_buckets_in_each_table;
        *b2 = (hashint2(x) % number_of_buckets_in_each_table) + number_of_buckets_in_each_table;
    }
};


//auto compute_size(const size_t max_capacity, const double max_load_factor) -> size_t;


auto
compute_max_capacity(size_t number_of_pd, size_t quotient_range, size_t single_pd_capacity,
                     size_t remainder_length) -> size_t;

auto
compute_element_length(size_t number_of_pd, size_t quotient_range, size_t single_pd_capacity,
                       size_t remainder_length) -> size_t;

auto
compute_element_length(size_t number_of_pd, size_t quotient_range, size_t single_pd_capacity, size_t remainder_length,
                       size_t counter_length) -> size_t;

#endif //CLION_CODE_HASH_TABLE_HPP
