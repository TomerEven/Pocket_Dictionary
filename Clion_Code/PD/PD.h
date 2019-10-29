//
// Created by tomer on 10/24/19.
//

#ifndef CLION_CODE_PD_H
#define CLION_CODE_PD_H

#include "Header.h"
#include "Body.h"

class PD {
    Header header;
    Body body;
    size_t capacity;
    size_t max_capacity;
public:
    PD(size_t m, size_t f, size_t l);

    bool lookup(size_t quotient, FP_TYPE remainder);

    void insert(size_t quotient, FP_TYPE remainder);

    void remove(size_t quotient, FP_TYPE remainder);

    void header_pp();

    void print();

private:

    uint8_t
    get_body_abstract_start_index(size_t header_interval_start_index, size_t header_interval_end_index, size_t quotient);

    uint8_t
    get_body_abstract_end_index(size_t header_interval_start_index, size_t header_interval_end_index, size_t quotient);

};


#endif //CLION_CODE_PD_H
