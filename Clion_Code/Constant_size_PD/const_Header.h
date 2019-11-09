//
// Created by tomer on 11/9/19.
//

#ifndef CLION_CODE_CONST_HEADER_H
#define CLION_CODE_CONST_HEADER_H


#include "../Global_functions/basic_functions.h"
#include "../bit_operations/bit_op.h"

class const_Header {
    D_TYPE w1, w2;

public:
    const_Header(bool preventing_empty_constructor);

    bool lookup(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void insert(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index);

    void get_interval(size_t quotient, size_t *start_index, size_t *end_index);

    void push(size_t end);

    void pull(size_t end);

    size_t get_capacity();

    void get_w1w2(uint32_t *p1, uint32_t *p2);

    void print();

private:


};

void static_push(D_TYPE *w1, D_TYPE *w2, size_t end);

void static_pull(D_TYPE *w1, D_TYPE *w2, size_t end);

#endif //CLION_CODE_CONST_HEADER_H
