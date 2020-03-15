//
// Created by tomer on 3/14/20.
//

#include "Counters_Array.hpp"

Counters_Array::Counters_Array(size_t max_capacity, size_t max_rep) : max_capacity(max_capacity), max_rep(max_rep),
                                                                      a_size(get_array_size(
                                                                              get_bit_size(max_capacity, max_rep))) {
    COUNTER_TYPE empty_cell = 0;
    if (COUNTER_TYPE_SIZE == 8)
        empty_cell = COUNTER_CELL_C8;
    else if (COUNTER_TYPE_SIZE == 16)
        empty_cell = COUNTER_CELL_C16;
    else if (COUNTER_TYPE_SIZE == 32)
        empty_cell = COUNTER_CELL_C32;
    else
        assert(false);

    A = new COUNTER_TYPE[a_size]();
    for (int i = 0; i < a_size; ++i) { A[i] = empty_cell; }
}

void Counters_Array::increase_counter(size_t element_index, size_t add_value) {

}

size_t Counters_Array::get_ith_counter(size_t ith) {


    return 0;
}

void Counters_Array::find_counter_interval(size_t index, size_t *start, size_t *end) {
    /*cg_PD header_find rewriting.*/
    //todo: start over.
    if (index == 0) {
        *start = 0;
        *end = __builtin_clz(DECODE(A[0]));
        return;
    }

    for (int i = 0; i < a_size; ++i) {
        COUNTER_TYPE decoded_slot = DECODE(A[i]);
        auto cz = __builtin_popcount(decoded_slot);
        if (cz < index) index -= cz;
        else if (cz == index) {
            uint32_t bit_pos = __builtin_ctz(decoded_slot) - 2;
//            uint64_t slot = ((ulong) (slot) << 32ul) | 4294967295ul;
//            uint32_t bit_pos = select_r(~slot, index);
//            if (DB) assert(bit_pos < COUNTER_TYPE_SIZE);
            *start = (i + (bit_pos + 1 == COUNTER_TYPE_SIZE)) * COUNTER_TYPE_SIZE + (bit_pos + 1) % COUNTER_TYPE_SIZE;
            size_t j = i + 1;
            while (A[j] == MASK32) j++;
            *end = (j) * COUNTER_TYPE_SIZE + __builtin_clz(~A[j]);
            return;

            /*if (bit_pos == CG_TYPE_SIZE - 1) {
                *start = (i + 1) * CG_TYPE_SIZE;
                size_t j = i + 1;
                while (A[j] == MASK32) j++;
                uint64_t slot2 = ((ulong) (A[j]) << 32ul) | 4294967295ul;
                *end_index = (j) * CG_TYPE_SIZE + bit_rank(~slot2, 1);
                cout << "h1" << endl;
            } else {
                *start = (i) * CG_TYPE_SIZE + bit_pos + 1;
                size_t j = i + 1;
                while (A[j] == MASK32) j++;
                uint64_t slot2 = ((ulong) (A[j]) << 32ul) | 4294967295ul;
                *end_index = (j) * CG_TYPE_SIZE + select_r(~slot2, 1);
                cout << "h2" << endl;
            }
            return;*/
        } else {
            if (DB) assert(index < COUNTER_TYPE_SIZE);
            uint64_t slot = ((ulong) (A[i]) << 32ul) | 4294967295ul;
            uint32_t bit_pos = select_r(~slot, index);
            if (DB) assert(bit_pos < COUNTER_TYPE_SIZE);
            *start = i * COUNTER_TYPE_SIZE + select_r(~slot, index) + 1;
            *end = i * COUNTER_TYPE_SIZE + select_r(~slot, index + 1);
//            cout << "h3" << endl;
            return;

            auto temp_count = __builtin_popcount(slot);
            if (temp_count + 1 <= index)
                break;
            index -= temp_count;
        }


        if (index == 0) {
            *start = 0;
            size_t j = 0;
            while (A[j] == MASK32) j++;
            *end = (j) * COUNTER_TYPE_SIZE + __builtin_clz(~A[j]);
//        uint64_t slot2 = ((ulong) (A[j]) << 32ul) | 4294967295ul;
//        *end_index = (j) * CG_TYPE_SIZE + select_r(~slot2, 1);
//        cout << "h0" << endl;
            return;
        }
        for (size_t i = 0; i <= 42; ++i) {
            auto cz = __builtin_popcount(~A[i]);
            if (cz < index) index -= cz;
            else if (cz == index) {
                uint64_t slot = ((ulong) (A[i]) << 32ul) | 4294967295ul;
                uint32_t bit_pos = select_r(~slot, index);
                if (DB) assert(bit_pos < COUNTER_TYPE_SIZE);
                *start = (i + (bit_pos + 1 == COUNTER_TYPE_SIZE)) * COUNTER_TYPE_SIZE +
                         (bit_pos + 1) % COUNTER_TYPE_SIZE;
                size_t j = i + 1;
                while (A[j] == MASK32) j++;
                *end = (j) * COUNTER_TYPE_SIZE + __builtin_clz(~A[j]);
                return;

                /*if (bit_pos == CG_TYPE_SIZE - 1) {
                    *start = (i + 1) * CG_TYPE_SIZE;
                    size_t j = i + 1;
                    while (A[j] == MASK32) j++;
                    uint64_t slot2 = ((ulong) (A[j]) << 32ul) | 4294967295ul;
                    *end_index = (j) * CG_TYPE_SIZE + bit_rank(~slot2, 1);
                    cout << "h1" << endl;
                } else {
                    *start = (i) * CG_TYPE_SIZE + bit_pos + 1;
                    size_t j = i + 1;
                    while (A[j] == MASK32) j++;
                    uint64_t slot2 = ((ulong) (A[j]) << 32ul) | 4294967295ul;
                    *end_index = (j) * CG_TYPE_SIZE + select_r(~slot2, 1);
                    cout << "h2" << endl;
                }
                return;*/
            } else {
                if (DB) assert(index < COUNTER_TYPE_SIZE);
                uint64_t slot = ((ulong) (A[i]) << 32ul) | 4294967295ul;
                uint32_t bit_pos = select_r(~slot, index);
                if (DB) assert(bit_pos < COUNTER_TYPE_SIZE);
                *start = i * COUNTER_TYPE_SIZE + select_r(~slot, index) + 1;
                *end = i * COUNTER_TYPE_SIZE + select_r(~slot, index + 1);
//            cout << "h3" << endl;
                return;

            }
        }
        assert(false);
        /*int zero_counter = -1, continue_from_a_index = 0, continue_from_bit_index = -1;
        bool to_break = false;
        for (size_t i = 0; i < size; ++i) {
            ulong b = 1ULL << (ulong) (CG_TYPE_SIZE - 1);
            for (size_t j = 0; j < CG_TYPE_SIZE; ++j) {
                if (DB) assert(b > 0);
                if (zero_counter == index - 1) {
                    *start = i * CG_TYPE_SIZE + j;
                    continue_from_a_index = i;
                    continue_from_bit_index = j;
                    to_break = true;
                    break;
                }
                if (not(A[i] & b))
                    zero_counter++;

                b >>= 1ul;
            }
            if (to_break) break;
        }
        if (DB) assert(continue_from_bit_index >= 0);

        size_t j = continue_from_bit_index;
        ulong b = 1ULL << (ulong) (CG_TYPE_SIZE - 1 - j);
        for (size_t i = continue_from_a_index; i < size; ++i) {
            for (; j < CG_TYPE_SIZE; ++j) {
                if (not(A[i] & b)) {
                    *end_index = i * CG_TYPE_SIZE + j;
                    return;
                }
                b >>= 1ul;
            }
            b = 1ULL << (ulong) (CG_TYPE_SIZE - 1);
            j = 0;
        }
        assert(false);
    */

    }


}

size_t get_bit_size(size_t max_capacity, size_t max_rep) {
    return max_capacity << 1ul;
}

size_t get_array_size(size_t bit_size) {
    return INTEGER_ROUND(bit_size, COUNTER_TYPE_SIZE);
}
