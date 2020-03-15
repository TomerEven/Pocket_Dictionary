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

    if (index == 0){
        *start = 0;
        while (temp_index <= last_index){
            if (a[temp_index] == 0) {
                temp_index++;
                continue;
            }

            auto temp_slot = COMMA_DECODE(a[temp_index]);
            T b = 1ull << (slot_size - 1);
            if (b <= temp_slot){
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
