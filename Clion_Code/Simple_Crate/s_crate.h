//
// Created by tomer on 11/3/19.
//

#ifndef CLION_CODE_S_CRATE_H
#define CLION_CODE_S_CRATE_H


#include "../PD/PD.h"
#include "../Hash/Hash.h"

class s_crate {
    vector<PD> pd_vec;
    vector<PD> spare_pd_vec;
    size_t pd_vec_size, spare_vec_size, capacity, remainder_length, pd_index_length;
//    Hash h1, h2;

public:
    s_crate(size_t pd_vec_size, size_t spare_pd_vec_size, size_t m, size_t f, size_t l);

    bool lookup(size_t pd_index, uint32_t quotient, uint32_t remainder, uint32_t spare_pd_index);

    void insert(size_t pd_index, uint32_t quotient, uint32_t remainder, uint32_t spare_pd_index);

    void remove(size_t pd_index, uint32_t quotient, uint32_t remainder, uint32_t spare_pd_index);

private:
    uint32_t concatenate(uint32_t remainder, uint32_t pd_index);
};


#endif //CLION_CODE_S_CRATE_H
