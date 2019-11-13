//
// Created by tomer on 11/4/19.
//

#ifndef CLION_CODE_POW2C_FILTER_H
#define CLION_CODE_POW2C_FILTER_H

#include "../PD/PD.h"
#include "../Hash/Hash.h"
#include "../Hash/Permutation.h"


class pow2c_filter {
    vector<PD> pd_vec;
    size_t capacity;
    const size_t size, fp_size, interval_length, single_pd_capacity;
    const size_t quotient_length, pd_index_length;
    Hash h;
    Permutation perm;

public:
    pow2c_filter(size_t size, size_t interval_length, size_t single_pd_capacity, size_t fp_size);

//    ~pow2c_filter();

    bool lookup(string *s);

    void insert(string *s);

    void remove(string *s);

    bool lookup(uint32_t s);

    void insert(uint32_t s);

    void remove(uint32_t s);


    inline void split(size_t hash_index, size_t *pd_index, D_TYPE *quotient, D_TYPE *remainder) {
        *remainder = hash_index & MASK(fp_size);
        hash_index >>= fp_size;
        *quotient = hash_index & MASK(quotient_length);
        hash_index >>= quotient_length;
        *pd_index = hash_index & MASK(pd_index_length);

    }

    inline void wrap_split_string(string *s, size_t *pd_index1, size_t *pd_index2, D_TYPE *q1, D_TYPE *q2, D_TYPE *r1,
                                  D_TYPE *r2) {
        size_t hash1 = h.hash(s) << 1ul;
        size_t hash2 = (perm.get_perm(h.hash(s)) << 1ul) | 1ul;
        split(hash1, pd_index1, q1, r1);
        split(hash2, pd_index2, q2, r2);
    }

    inline void wrap_split32(uint32_t s, size_t *pd_index1, size_t *pd_index2, D_TYPE *q1, D_TYPE *q2, D_TYPE *r1,
                                  D_TYPE *r2) {
        size_t hash1 = h.hash32(s) << 1ul;
        size_t hash2 = (perm.get_perm(h.hash32(s)) << 1ul) | 1ul;
        split(hash1, pd_index1, q1, r1);
        split(hash2, pd_index2, q2, r2);
    }
};


#endif //CLION_CODE_POW2C_FILTER_H
