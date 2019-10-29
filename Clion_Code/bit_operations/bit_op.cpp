//
// Created by tomer on 10/24/19.
//

#include <cassert>
#include "bit_op.h"

unsigned int msb32(register unsigned int x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    return (x & ~(x >> 1));
}

unsigned char msb8(register __uint8_t x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    return (x & ~(x >> 1));
}

unsigned int reverse(register unsigned int x) {
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return ((x >> 16) | (x << 16));

}

unsigned int floor_log2(register unsigned int x) {
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
#ifdef    LOG0UNDEFINED
    return(ones32(x) - 1);
#else
    return (ones32(x >> 1));
#endif
}

unsigned int ones32(register unsigned int x) {
    /* 32-bit recursive reduction using SWAR...
   but first step is mapping 2-bit values
   into sum of 2 1-bit values in sneaky way
*/
    x -= ((x >> 1) & 0x55555555);
    x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
    x = (((x >> 4) + x) & 0x0f0f0f0f);
    x += (x >> 8);
    x += (x >> 16);
    return (x & 0x0000003f);
}

unsigned int naive_msb32(unsigned int x) {
    if (x == 0) return 0;
    unsigned int b = (-1);
    unsigned int counter = 31;
    for (int i = 0; i < 32; ++i) {
        if (b & x) return 31 - i;
        b >>= 1;
    }
    return 0;

}

