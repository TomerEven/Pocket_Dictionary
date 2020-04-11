//
// Created by tomer on 4/8/20.
//

//Todo: move element from pd with overflowing counter, to spare. (and underflow counter from spare to pd)
// Also, all this moves should be done using some lazy scheme.

#ifndef CLION_CODE_MULTI_DICT_HPP
#define CLION_CODE_MULTI_DICT_HPP

#include <ostream>
#include "../CPD/CPD.hpp"
#include "../Hash_Table/multi_hash_table.hpp"
#include "../CPD/CPD_validator.hpp"


template<class D, class S>
class multi_dict {
    vector<D> pd_vec;
    vector<uint> pd_capacity_vec;
    S *spare;
//    multi_hash_table<uint32_t> *spare2;

    size_t capacity;
    const size_t number_of_pd, remainder_length, quotient_range, single_pd_capacity;
    const size_t quotient_length, pd_index_length;
    const size_t level1_counter_size, level2_counter_size;

    const size_t spare_element_length, sparse_counter_length;
//    const string bad_str = "@BO@JWLZWGC";
public:
    multi_dict(size_t max_number_of_elements, size_t error_power_inv, size_t level1_counter_size,
               size_t level2_counter_size, double level1_load_factor, double level2_load_factor);


    auto lookup(const string *s) -> bool;

    auto lookup_multi(const string *s) -> size_t;

    void insert(const string *s);

    void remove(const string *s);

    void get_info();

//    friend ostream &operator<<(ostream &os, const multi_dict &dict);

    auto sum_pd_capacity() -> size_t;

private:

    void insert_to_spare(MS_TYPE y);

    void insert_to_spare_with_pop(MS_TYPE hash_val);

    void insert_to_spare_with_known_counter(MS_TYPE hash_val, size_t counter);

    void insert_level1_inv_overflow_handler(MS_TYPE hash_val);

    auto insert_to_bucket_attempt(MS_TYPE y, size_t bucket_index) -> counter_status;

    auto insert_to_bucket_attempt(MS_TYPE y, size_t bucket_index, bool pop_attempt) -> counter_status;

    auto insert_inc_to_bucket_attempt(MS_TYPE y, size_t bucket_index) -> std::tuple<counter_status, size_t>;

    auto pop_attempt(string *s) -> MS_TYPE *;

    /**
     * Try to drop an element in the bucket to lower level.
     * Stops after the first time the popping succeed, and return the poped element position.
     * @param bucket_index
     * @param y element with counter.
     * @return
     */
    auto pop_attempt_by_bucket(MS_TYPE y, size_t bucket_index) -> size_t;

    auto pop_attempt_with_insertion_by_bucket(MS_TYPE hash_val, size_t bucket_index) -> bool;

    /**
     * reads the element if
     * @param element
     * @return
     */
    auto single_pop_attempt(MS_TYPE element) -> bool;

    auto single_pop_attempt(MS_TYPE temp_el, MS_TYPE counter) -> bool;


    inline auto wrap_hash(const string *s) -> MS_TYPE {
        return my_hash(s, HASH_SEED) & MASK(spare_element_length);
    }

    inline void wrap_split(const string *s, size_t *pd_index, D_TYPE *q, D_TYPE *r) {
        auto h = my_hash(s, HASH_SEED);
        split(h, pd_index, q, r);
    }

    inline void split(ulong h, size_t *pd_index, D_TYPE *q, D_TYPE *r) {
        *r = h & MASK(remainder_length);
        h >>= remainder_length;
        *q = h % (quotient_range);
        h >>= quotient_length;
        *pd_index = h % pd_vec.size();
    }

};

static auto get_multi_spare_max_capacity(size_t dict_max_capacity, double level1_load_factor) -> size_t;

typedef multi_dict<CPD, multi_hash_table<uint32_t>> basic_multi_dict;
typedef multi_dict<CPD_validator, multi_hash_table<uint32_t>> safe_multi_dict;

#endif //CLION_CODE_MULTI_DICT_HPP
