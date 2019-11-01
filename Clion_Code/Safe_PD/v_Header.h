//
// Created by tomer on 10/29/19.
//

#ifndef CLION_CODE_V_HEADER_H
#define CLION_CODE_V_HEADER_H

#include "../PD/Header.h"


class v_Header {
    Header header;
    vector<bool> vec;

public:
    v_Header(size_t m, size_t f, size_t l);

    bool lookup(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void insert(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void validate_get_interval(size_t quotient);

    void vector_get_interval(size_t quotient, size_t *start_index, size_t *end_index);

    void vector_insert(size_t quotient);

    void vector_remove(uint_fast16_t quotient);

};


#endif //CLION_CODE_V_HEADER_H
