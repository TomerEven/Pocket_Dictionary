/**
 * @techreport{magicalgorithms,
 * author={Henry Gordon Dietz},
 * title={{The Aggregate Magic Algorithms}},
 * institution={University of Kentucky},
 * howpublished={Aggregate.Org online technical report},
 * URL={http://aggregate.org/MAGIC/}
 * Date={10/24/19}
 * }
**/


#ifndef CLION_CODE_BIT_OP_H
#define CLION_CODE_BIT_OP_H

#include <iostream>
#include <zconf.h>
#include <vector>
#include <cstdint>

#define MOD_INVERSE(n) (BODY_BLOCK_SIZE - (n) - 1)

typedef unsigned int u32;

using namespace std;


unsigned int msb32(register unsigned int x);

unsigned char msb8(register __uint8_t x);

unsigned int reverse(register unsigned int x);

unsigned int floor_log2(register unsigned int x);

unsigned int ones32(register unsigned int x);

/**
 */

/**
 * Select the bit position (from the most-significant bit) with the given count (rank)
 * The following 64-bit code selects the position of the rth 1 bit when counting from the left.
 * In other words if we start at the most significant bit and proceed to the right, counting the number of bits set to
 * 1 until we reach the desired rank, r, then the position where we stop is returned. If the rank requested exceeds the
 * count of bits set, then 64 is returned. The code may be modified for 32-bit or counting from the right.
 * @param slot Value to find position with rank r.
 * @param rank Bit's desired rank [1-64].
 * @return Resulting position of bit with the desired rank.[1-64]
 */
uint32_t bit_rank(uint64_t slot, uint32_t rank);


/**
 *The following finds the the rank of a bit, meaning it returns the sum of bits that are set to 1 from the
 * most-signficant bit downto the bit at the given position.
 * @param slot Compute the rank (bits set) in slot from the MSB to bit_lim.
 * @param bit_lim Bit position to count bits upto.
 * @return Resulting rank of bit at bit_lim goes here.
 */
uint64_t count(uint64_t slot, unsigned int bit_lim);

/**
 * Count number of set bits in v.
 * @param v
 * @return
 */
uint32_t bit_count(uint32_t v);

//
// Created by tomer on 10/24/19.
//
uint32_t my_count(uint32_t slot);

uint64_t convert_32_to_64(uint32_t slot);

inline bool is_bit_rank_valid(uint64_t slot, uint32_t rank, uint32_t res);

uint32_t my_bit_rank(uint64_t slot, uint32_t rank);

size_t array_zero_count(const uint32_t * a, size_t a_size);


#endif //CLION_CODE_BIT_OP_H
