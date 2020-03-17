//
// Created by tomer on 3/14/20.
//

#include "Naive_Counter_Endec.hpp"


template<typename T>
void
find_counter_interval_naive(T *a, size_t a_size, size_t start_lim, size_t end_lim, size_t index, size_t *start,
                            size_t *end) {
    assert(start_lim <= end_lim);
    auto slot_size = sizeof(a[0]) * CHAR_BIT;

    uint first_index = (start_lim >> 5u);
    if (start_lim == 0)
        first_index = 0;

    uint temp_index = first_index;
    uint last_index = end_lim >> 5u;

    if (index == 0) {
        *start = 0;
        while (temp_index <= last_index) {
            if (a[temp_index] == 0) {
                temp_index++;
                continue;
            }

            auto temp_slot = COMMA_DECODE(a[temp_index]);
            T b = 1ull << (slot_size - 1);
            if (b <= temp_slot) {
                //todo check this!
                *end = (slot_size * (temp_index - first_index));
                return;
            }
            for (int i = 1; i < slot_size - 1; ++i) {
                b >>= 1;
                if (b <= temp_slot) {
                    *end = (slot_size * (temp_index - first_index)) + i;
                    return;
                }
            }
        }
    }


}


template<typename T, typename S>
static T encode(S x) {
    assert(0 < x < MAX_COUNTER);
    return T((encode_table[x - 1] << 2) | 1u);
}


template<typename T, typename S>
static T decode(S x) {
    assert(0 < x < MAX_DECODE_VAL);
    T res = T(decode_table[x]);
    assert(res > 0);
    return res;
}

template<typename T, typename S>
T update(S x, int update_val) {
    return encode(decode(x + update_val));
}

template<typename T, typename S>
T update_with_overflow(S x, int update_val) {
    auto temp_val = decode(x + update_val);
    //todo Deal with the case: temp_val < 0.
    if (temp_val == 0 or temp_val > MAX_COUNTER)
        return 0;
    return encode(temp_val);
    return nullptr;
}
