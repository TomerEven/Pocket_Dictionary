//
// Created by tomer on 11/9/19.
//

#ifndef CLION_CODE_CONST_BODY_H
#define CLION_CODE_CONST_BODY_H

#include "../Global_functions/basic_functions.h"
#include "../bit_operations/bit_op.h"


class const_Body {
    uint8_t B[32]{};

public:
    const_Body();
//    const_Body();
//    const_Body(size_t max_capacity);

    bool lookup(size_t abstract_body_start_index, size_t abstract_body_end_index, uint8_t remainder);

    void insert(size_t abstract_body_start_index, size_t abstract_body_end_index, uint8_t remainder);

    void remove(size_t abstract_body_start_index, size_t abstract_body_end_index, uint8_t remainder);

    bool conditional_remove(size_t abstract_body_start_index, size_t abstract_body_end_index, uint8_t remainder);

    int
    find(size_t abstract_body_start_index, size_t abstract_body_end_index, uint8_t remainder,
         size_t *p_B_index);

    void print();
};


#endif //CLION_CODE_CONST_BODY_H
