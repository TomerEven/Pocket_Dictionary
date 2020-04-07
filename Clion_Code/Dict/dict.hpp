
#ifndef CLION_CODE_DICT_HPP
#define CLION_CODE_DICT_HPP

#include "../Contiguous_PD/cg_PD.h"
#include "../Hash_Table/hash_table.hpp"

#define S_TYPE uint32_t

template<class D, class S>
class dict {
    vector<D> pd_vec;
    vector<uint> pd_capacity_vec;
    S *spare;

    size_t capacity;
    const size_t number_of_pd, remainder_length, quotient_range, single_pd_capacity;
    const size_t quotient_length, pd_index_length;

    const size_t sparse_element_length, sparse_counter_length;

public:
    dict(size_t max_number_of_elements, size_t error_power_inv, double level1_load_factor, double level2_load_factor);

//    dict(size_t number_of_pd, size_t quotient_range, size_t single_pd_capacity, size_t remainder_length);
//         size_t bucket_size = DEFAULT_BUCKET_SIZE, double max_load_factor = DEFAULT_MAX_LOAD_FACTOR);

//    dict(size_t filter_max_capacity, size_t error_power_inv, double level1_load_factor, double level2_load_factor);

//    virtual ~dict();

    auto lookup(const string *s) -> bool;

    void insert(const string *s);
    void insert_to_spare_without_pop(S_TYPE hash_val);

    void insert_to_spare_with_pop(S_TYPE hash_val);

    void remove(const string *s);

    void get_info();

private:

    auto pop_attempt(string *s) -> S_TYPE *;

    auto pop_attempt_by_bucket(size_t bucket_index) -> S_TYPE *;

    auto pop_attempt_with_insertion_by_bucket(S_TYPE hash_val, size_t bucket_index) -> bool;

    /**
     * reads the element if
     * @param element
     * @return
     */
    auto single_pop_attempt(S_TYPE element) -> bool;

    inline auto wrap_hash(const string *s) -> S_TYPE {
        return my_hash(s, HASH_SEED) & MASK(sparse_element_length);
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


static auto
get_max_elements_in_level1(size_t number_of_pd, size_t single_pd_capacity, double level1_load_factor) -> size_t;

static auto get_max_elements_in_level2(size_t number_of_pd, size_t single_pd_capacity, double level1_load_factor,
                                       double level2_load_factor) -> size_t;

static auto get_spare_max_capacity(size_t dict_max_capacity, double level1_load_factor) -> size_t;


#endif //CLION_CODE_DICT_HPP
