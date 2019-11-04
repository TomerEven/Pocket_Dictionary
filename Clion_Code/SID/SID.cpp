//
// Created by tomer on 11/4/19.
//

#include "SID.h"


SID::SID(const size_t number_of_csd, size_t csd_size, const Hash *h, size_t remainder_length,
         size_t org_pd_index_length) :
        size(number_of_csd), csd_size(csd_size), h(h), remainder_length(remainder_length),
        pd_index_length(org_pd_index_length) {

    ll_array = new D_TYPE *[size]();

    for (size_t i = 0; i < size; ++i) {
        ll_array[i] = nullptr;
        csd_vec.emplace_back(CSD(csd_size, remainder_length, org_pd_index_length));
    }

}

bool SID::lookup(size_t csd_index, D_TYPE x) {
//    return csd_vec[csd_index].lookup(x);
}

void SID::insert(size_t csd_index, D_TYPE x) {
    size_t pd_index = get_org_pd_index(x);
//    ll_array[pd_index] = csd_vec[csd_index].insert(x, ll_array[pd_index]);
    /*if (ll_array[pd_index]){
        ll_array[pd_index] = csd_vec[csd_index].insert(x, ll_array[pd_index]);
        return;
//        ll_array[pd_index] = &address;
//        ll_array[pd_index] = &(csd_vec[csd_index].insert(x, ll_array[pd_index]));*/

}

void SID::remove(size_t csd_index, D_TYPE x) {
    return;
}

uint32_t SID::pop(D_TYPE x) {
    return 0;
}

D_TYPE SID::get_org_pd_index(D_TYPE x) {
    return x & MASK(pd_index_length);
}
