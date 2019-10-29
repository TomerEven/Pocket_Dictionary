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

//
// Created by tomer on 10/24/19.
//


#endif //CLION_CODE_BIT_OP_H
