/*A secondary data structure, used for maintaining elements with high multiplicity, of elements from PD that was
 * overflowed.*/

#ifndef CLION_CODE_SPARSE_HPP
#define CLION_CODE_SPARSE_HPP

#include "../Hash_Table/cuckoohash_map.hh"

#define KEY_TYPE uint32_t
#define KEY_SIZE (32)
#define VAL_TYPE uint32_t
#define VAL_SIZE (32)

class sparse {
    libcuckoo::cuckoohash_map<KEY_TYPE, VAL_TYPE> Table;
    size_t capacity = 0;
    size_t const max_capacity;

public:
    sparse(size_t max_capacity);
};


#endif //CLION_CODE_SPARSE_HPP
