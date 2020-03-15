//
// Created by tomer on 3/14/20.
//Todo 1: Deal with the situation of a comma (01) that is separated between the array slot. (0 in the LSB of A[i], and 1 in the MSB of A[i+1])
//


#ifndef CLION_CODE_COUNTERS_ARRAY_HPP
#define CLION_CODE_COUNTERS_ARRAY_HPP


#include <ostream>
#include "../Global_functions/basic_functions.h"
#include "../bit_operations/bit_op.h"

#define COUNTER_TYPE uint32_t
#define COUNTER_TYPE_SIZE (sizeof(COUNTER_TYPE) * (CHAR_BIT))
#define COUNTER_CELL_C8 (0x55)
#define COUNTER_CELL_C16 (0x5555)
#define COUNTER_CELL_C32 (0x55555555)
#define DECODE(x) ((~x) & (x << 1ul) )

class Counters_Array {
    COUNTER_TYPE *A;
    size_t a_size, max_capacity, max_rep, capacity = 0;

public:
    Counters_Array(size_t max_capacity, size_t max_rep);

    /**
     * Increase the element in the "element_index" by "add_value".
     * @param element_index the index of the element, whose counter should be increased.
     * @param add_value By how much that counter should be increased.
     * Todo: Deal with overflow caused by updated counter > max_rep.
     */
    void increase_counter(size_t element_index, size_t add_value);

    /**
     * In case of an overflow, the elements counter should be updated to 0, and the element should be
     * moved to secondary DAST.
     * @param element_index
     * @param add_value
     * @return Did overflow occurred.
     * Remark: Can also be used to deal with counter decreasing.
     */
    bool increase_counter_handle_overflow(size_t element_index, size_t add_value);

    /**
     *
     * @param ith
     * @return the value of the i'th element.
     */
    size_t get_ith_counter(size_t ith);


private:
    /**
     *
     * @param index
     * @param start The minimal k s.t A[:k] ends with "01" (comma), and contain exactly*** (index - 1) commas
     * @param end The beginning of the *next* (after the comma in A[k-2:k])
     * *Remark* - Assuming A does not start with a comma.
     */
    void find_counter_interval(size_t index, size_t *start, size_t *end);

//    void find_counter_interval_naive(size_t index, size_t *start, size_t *end);
};


static size_t get_bit_size(size_t max_capacity, size_t max_rep);

static size_t get_array_size(size_t bit_size);


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
static void
find_counter_interval_naive(uint32_t *a, size_t a_size, size_t start_lim, size_t end_lim, size_t index, size_t *start,
                            size_t *end);

//static size_t get_longest_encoding()



#endif //CLION_CODE_COUNTERS_ARRAY_HPP