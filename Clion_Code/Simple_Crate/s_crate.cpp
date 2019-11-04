//
// Created by tomer on 11/3/19.
//

#include "s_crate.h"

s_crate::s_crate(size_t pd_vec_size, size_t spare_pd_vec_size, size_t m, size_t f, size_t l) :
        pd_vec_size(pd_vec_size), spare_vec_size(spare_pd_vec_size), capacity(0), remainder_length(l),
        pd_index_length(ceil(log2(log2(pd_vec_size)))) {
    for (size_t i = 0; i < pd_vec_size; ++i) {
        pd_vec.emplace_back(m, f, l);
    }
    int temp = ceil(log2(log2(pd_vec_size)));
    assert(temp > 0);
    size_t spare_l = l + temp;
    for (size_t i = 0; i < spare_pd_vec_size; ++i) {
        spare_pd_vec.emplace_back(m, f, spare_l);
    }

    assert(remainder_length + pd_index_length <= 32);
}

bool s_crate::lookup(size_t pd_index, uint32_t quotient, uint32_t remainder, uint32_t spare_pd_index) {
    return spare_pd_vec[spare_pd_index].lookup(quotient, remainder) || pd_vec[pd_index].lookup(quotient, remainder);
}

void s_crate::insert(size_t pd_index, uint32_t quotient, uint32_t remainder, uint32_t spare_pd_index) {
    if (pd_vec[pd_index].is_full()) {
        spare_pd_vec[spare_pd_index].insert(quotient, concatenate(remainder, pd_index));
    }
    else{
        pd_vec[pd_index].insert(quotient, remainder);
    }
    capacity++;

}

void s_crate::remove(size_t pd_index, uint32_t quotient, uint32_t remainder, uint32_t spare_pd_index) {
    if (!pd_vec[pd_index].is_full()){
        pd_vec[pd_index].remove(quotient, remainder);
        return;
    }
    //todo Partial match in pd by pd_index (higher bit in remainder).
    assert (false);

    /*if (spare_pd_vec[spare_pd_index].conditional_remove(quotient, concatenate(pd_index, remainder)))
        return;
    pd_vec[pd_index].remove()
    capacity++;*/
}

uint32_t s_crate::concatenate(uint32_t remainder, uint32_t pd_index) {
    return (pd_index << remainder_length) | remainder;
}
