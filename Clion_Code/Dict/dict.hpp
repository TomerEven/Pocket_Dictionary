
#ifndef CLION_CODE_DICT_HPP
#define CLION_CODE_DICT_HPP

#include "../Contiguous_PD/cg_PD.h"
#include "../Hash_Table/hash_table.hpp"

template<class D, class S>
class dict {
    vector<D> pd_vec;
    S *spare;
    vector<uint> pd_capacity_vec;
    size_t capacity;
    const size_t number_of_pd, remainder_length, quotient_range, single_pd_capacity;
    const size_t quotient_length, pd_index_length;
    const bool is_const_size_indicator{};

    dict(size_t number_of_pd, size_t quotient_range, size_t single_pd_capacity, size_t remainder_length);

    auto lookup(string *s) -> bool;

    void insert(string *s);

    void remove(string *s);

    inline void wrap_split(string *s, size_t *pd_index, D_TYPE *q, D_TYPE *r) {
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

//size_t max_capacity, size_t element_length, size_t bucket_size, double max_load_factor
//static void



#endif //CLION_CODE_DICT_HPP
