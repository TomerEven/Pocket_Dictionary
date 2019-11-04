//
// Created by tomer on 11/4/19.
//

#ifndef CLION_CODE_POW2C_FILTER_H
#define CLION_CODE_POW2C_FILTER_H

#include "../PD/PD.h"
#include "../Hash/Hash.h"
#include "../Hash/Permutation.h"

#define D_TYPE uint32_t
#define D_TYPE_SIZE (32)

class pow2c_filter {
    vector<PD> pd_vec;
    size_t size, capacity;
    size_t fp_size, interval_length, single_pd_capacity;
    size_t quotient_length, pd_index_length;
    Hash h;
    Permutation perm;

public:
    pow2c_filter(size_t size, size_t fp_size, size_t interval_length, size_t single_pd_capacity);

    bool lookup(string *s);

    void insert(string *s);

    void remove(string *s);

    void split(size_t hash_index, size_t *pd_index, D_TYPE *quotient, D_TYPE *remainder);
};


#endif //CLION_CODE_POW2C_FILTER_H
