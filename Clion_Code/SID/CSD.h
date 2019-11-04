//
// Created by tomer on 11/4/19.
//

#ifndef CLION_CODE_CSD_H
#define CLION_CODE_CSD_H

#include "../Global_functions/basic_functions.h"

#define D_TYPE uint32_t
#define D_TYPE_SIZE (32)


class CSD {
    D_TYPE *data_array;
    size_t size, capacity, remainder_length, pd_index_length;

public:
    CSD(size_t size, size_t remainder_length, size_t org_pd_index_length);

//    CSD(uint32_t *data_array, size_t size, size_t capacity, size_t remainder_length, size_t pd_index_length);

    bool lookup(D_TYPE x);

    D_TYPE* insert(D_TYPE x, D_TYPE* next);

    void remove(D_TYPE x);

    uint32_t pop(D_TYPE x);
};


#endif //CLION_CODE_CSD_H
