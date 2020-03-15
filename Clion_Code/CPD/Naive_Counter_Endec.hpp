//
// Created by tomer on 3/14/20.
//

#ifndef CLION_CODE_NAIVE_COUNTER_ENDEC_HPP
#define CLION_CODE_NAIVE_COUNTER_ENDEC_HPP

#include <ostream>
#include "../Global_functions/basic_functions.h"
#include "../bit_operations/bit_op.h"

#define COUNTER_TYPE uint32_t
#define COUNTER_TYPE_SIZE (sizeof(COUNTER_TYPE) * (CHAR_BIT))
#define COUNTER_CELL_C8 (0x55)
#define COUNTER_CELL_C16 (0x5555)
#define COUNTER_CELL_C32 (0x55555555)
#define COMMA_DECODE(x) ((~x) & (x << 1ul) )

using namespace std;
static const uint32_t encode_table[10] = {5, 9, 13, 17, 25, 29, 33, 49, 57, 61};

static const int decode_table[33] = {-1, 1, 2, 3, 4, -1, 6, 7, 8, -1, -1, -1, 12, -1, 14, 15, 16, -1, -1, -1, -1,
                                          -1, -1, -1, 24, -1, -1, -1, 28, -1, 30, 31, 32};

template<typename T, typename S>
static T encode(S x) {
    assert(0 < x < 11);
    return T(encode_table[x - 1]);
}


/**
 *
 * @param a array in which the counter are encoded.
 * @param a_size number of slots in the array.
 * @param start_lim Denotes the first bit in the bit stream.
 * @param end_lim Denotes the last bit in the bit stream.
 * @param index Denote the index of the counter that should be decoded.
 * @param start Store the address of the first bit (relative to start_lim) in the relevant counter.
 * @param end Store the address of the last bit +1 (relative to start_lim) in the relevant counter.
 */

template<typename T>
static void
find_counter_interval_naive(T *a, size_t a_size, size_t start_lim, size_t end_lim, size_t index, size_t *start,
                            size_t *end);


#endif //CLION_CODE_NAIVE_COUNTER_ENDEC_HPP
