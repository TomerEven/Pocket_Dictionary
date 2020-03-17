//
// Created by tomer on 3/14/20.
//

#include "Counters_Array.hpp"

Counters_Array::Counters_Array(size_t max_capacity, size_t max_rep) : max_capacity(max_capacity), max_rep(max_rep),
                                                                      a_size(get_array_size(
                                                                              get_bit_size(max_capacity, max_rep))) {
    /* COUNTER_TYPE empty_cell = 0;
    if (COUNTER_TYPE_SIZE == 8)
        empty_cell = COUNTER_CELL_C8;
    else if (COUNTER_TYPE_SIZE == 16)
        empty_cell = COUNTER_CELL_C16;
    else if (COUNTER_TYPE_SIZE == 32)
        empty_cell = COUNTER_CELL_C32;
    else
        assert(false);*/

    A = new COUNTER_TYPE[a_size]();
    for (int i = 0; i < a_size; ++i) { A[i] = 0; }
}

void Counters_Array::increase_counter(size_t element_index, size_t add_value) {

}

size_t Counters_Array::get_ith_counter(size_t ith) {


    return 0;
}

/*void Counters_Array::find_counter_interval(size_t index, size_t *start, size_t *end) {
    ////cg_PD header_find rewriting.
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

    }


}*/

size_t Counters_Array::count_capacity() const {
    size_t counter = 0;
    for (int i = 0; i < a_size - 1; ++i) {
        auto slot = SPLITTED_COMMA_DECODER(A[i], A[i + 1]);
        counter += __builtin_popcount(slot);
    };
    size_t res = counter + __builtin_popcount(COMMA_DECODE(A[a_size - 1]));
    assert(res == get_capacity());
    return res;
}

size_t Counters_Array::get_capacity() const {
    return capacity;
}


COUNTER_TYPE Counters_Array::extract_symbol(size_t bit_start_index, size_t bit_end_index) {
    if (bit_start_index == bit_end_index)
        return 1;

    auto bit_end_rem = bit_start_index % COUNTER_TYPE_SIZE;
    if (bit_end_rem == 0) {
        auto bit_start_rem = bit_start_index % COUNTER_TYPE_SIZE;
        size_t array_start_index = bit_start_index / COUNTER_TYPE_SIZE;
        if (bit_start_rem)
            return A[array_start_index] & (SL(bit_start_rem));
        else
            return A[array_start_index];
    }
    size_t array_start_index = bit_start_index / COUNTER_TYPE_SIZE, array_end_index = bit_end_index / COUNTER_TYPE_SIZE;
//    size_t length = bit_end_index - bit_start_index;
    auto bit_start_rem = bit_start_index % COUNTER_TYPE_SIZE;

    if (array_start_index == array_end_index) {
        auto temp = A[array_start_index];
        if (bit_start_rem)
            temp &= SL(bit_start_rem);
        uint32_t shift = (COUNTER_TYPE_SIZE - bit_end_rem);
        assert(shift > 0);
        return temp >> shift;
    } else {
        auto i = array_start_index;
        assert(i + 1 == array_end_index);
        assert(i + 1 < a_size);

        // a[i] = (a[i] << fp_size) | (a[i + 1] >> (BODY_BLOCK_SIZE - fp_size));
        auto temp = A[i];
        if (bit_start_rem)
            temp &= SL(bit_start_rem);

        return (temp << bit_end_rem) | (A[i + 1] >> (COUNTER_TYPE_SIZE - bit_end_rem));
    }
}

size_t get_bit_size(size_t max_capacity, size_t max_rep) {
    return max_capacity << 1ul;
}

size_t get_array_size(size_t bit_size) {
    return INTEGER_ROUND(bit_size, COUNTER_TYPE_SIZE);
}

template<typename T>
static auto static_extract_symbol(const T *A, size_t a_size, size_t bit_start_index, size_t bit_end_index) -> T {
    if (bit_start_index == bit_end_index)
        return 1;

    auto bit_end_rem = bit_start_index % COUNTER_TYPE_SIZE;
    if (bit_end_rem == 0) {
        auto bit_start_rem = bit_start_index % COUNTER_TYPE_SIZE;
        size_t array_start_index = bit_start_index / COUNTER_TYPE_SIZE;
        auto temp = A[array_start_index] & (SL(bit_start_rem) - 1u);
        return temp;
    }
    size_t array_start_index = bit_start_index / COUNTER_TYPE_SIZE, array_end_index = bit_end_index / COUNTER_TYPE_SIZE;
//    size_t length = bit_end_index - bit_start_index;
    auto bit_start_rem = bit_start_index % COUNTER_TYPE_SIZE;

    if (array_start_index == array_end_index) {
        auto temp = A[array_start_index] & (SL(bit_start_rem) - 1u);
        uint32_t shift = (COUNTER_TYPE_SIZE - bit_end_rem);
        assert(shift > 0);
        return temp >> shift;
    } else {
        auto i = array_start_index;
        assert(i + 1 == array_end_index);
        assert(i + 1 < a_size);

        // a[i] = (a[i] << fp_size) | (a[i + 1] >> (BODY_BLOCK_SIZE - fp_size));
        return ((A[i] & (SL(bit_start_rem) - 1u)) << bit_end_rem) | (A[i + 1] >> (COUNTER_TYPE_SIZE - bit_end_rem));
    }
}


auto u32_extract_symbol(const uint32_t *A, size_t a_size, size_t bit_start_index, size_t bit_end_index) -> uint32_t {
    if (bit_start_index == bit_end_index) {
//        cout << "H0" << endl;
        return 0;
    }
    auto bit_start_rem = bit_start_index % COUNTER_TYPE_SIZE;
    auto bit_end_rem = bit_end_index % COUNTER_TYPE_SIZE;
    size_t shift_power = COUNTER_TYPE_SIZE - bit_start_rem;
    uint32_t mask = SL(shift_power) - 1u;
    uint32_t shift_left = COUNTER_TYPE_SIZE - (bit_end_rem);
/*

    cout << "start:" << bit_start_rem <<  " shift power: " << shift_power << endl;
    cout << "end:" << bit_end_rem <<  " shift left: " << shift_left << endl;
*/

    if (bit_end_rem == 0) {
        size_t array_start_index = bit_start_index / COUNTER_TYPE_SIZE;
        auto temp = A[array_start_index] & mask;
//        cout << "H1" << endl;
        return temp;
    }
    size_t array_start_index = bit_start_index / COUNTER_TYPE_SIZE, array_end_index = bit_end_index / COUNTER_TYPE_SIZE;
//    size_t length = bit_end_index - bit_start_index;

    if (array_start_index == array_end_index) {
        auto temp = A[array_start_index] & mask;
        /*uint32_t temp_mask = MASK32;
        for (int i = 0; i < 32; ++i) {
            auto temp_tmp = (A[array_start_index] & temp_mask) >> shift_left;
            printf("i: %u\t  res: %u\n", i, temp_tmp);
            if (temp_tmp == 1)
                cout << "The correct p for mask is " << i << " and not " << bit_start_rem + 1 << "." << endl;
            temp_mask >>= 1u;
        }*/
        assert(shift_left > 0);

//        cout << "H2" << endl;
//        printf("temp %u, shifted_temp %u, shift %u\n",temp, temp >> shift_left, shift_left);
        return temp >> shift_left;

    } else {
        auto i = array_start_index;
        assert(i + 1 == array_end_index);
        assert(i + 1 < a_size);

        // a[i] = (a[i] << fp_size) | (a[i + 1] >> (BODY_BLOCK_SIZE - fp_size));
//        cout << "H3" << endl;
        return ((A[i] & mask) << bit_end_rem) | (A[i + 1] >> shift_left);
    }
}

//template auto static_extract_symbol<COUNTER_TYPE>(const COUNTER_TYPE *A, size_t a_size, size_t bit_start_index,
//                                                  size_t bit_end_index) -> COUNTER_TYPE;

template auto static_extract_symbol<unsigned int>(const unsigned int *A, size_t a_size, size_t bit_start_index,
                                                  size_t bit_end_index) -> unsigned int;