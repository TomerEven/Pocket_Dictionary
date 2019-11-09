//
// Created by tomer on 11/9/19.
//

#ifndef CLION_CODE_CONST_FILTER_H
#define CLION_CODE_CONST_FILTER_H

#include "../Constant_size_PD/const_PD.h"
#include "../Hash/Hash.h"
#include "../Hash/Permutation.h"


class const_filter {
    vector<const_PD> pd_vec;
    size_t size, capacity;
    size_t fp_size, interval_length, single_pd_capacity;
    size_t quotient_length, pd_index_length;
    Hash h;
    Permutation perm;
public:
    const_filter(size_t size, size_t interval_length, size_t single_pd_capacity, size_t fp_size);

    bool lookup(string *s);

    void insert(string *s);

    void remove(string *s);

    void split(size_t hash_index, size_t *pd_index, D_TYPE *quotient, D_TYPE *remainder);

};


#endif //CLION_CODE_CONST_FILTER_H
