//
// Created by tomer on 11/4/19.
//

#include "CSD.h"

CSD::CSD(size_t size, size_t remainder_length, size_t org_pd_index_length) :
        size(size), remainder_length(remainder_length), pd_index_length(org_pd_index_length), capacity(0) {
    data_array = new D_TYPE[size]();
    assert(remainder_length + pd_index_length + sizeof(D_TYPE*) <= D_TYPE_SIZE);
}

bool CSD::lookup(D_TYPE x) {
    return false;
}

D_TYPE *CSD::insert(D_TYPE x, D_TYPE *next) {
    return nullptr;
}

void CSD::remove(D_TYPE x) {

}

uint32_t CSD::pop(D_TYPE x) {
    return 0;
}
