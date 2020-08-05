//
// Created by tomereven on 02/08/2020.
//

#ifndef FILTER_PD_JUNK_HPP
#define FILTER_PD_JUNK_HPP


void header_insert(uint64_t q, size_t *start_index, size_t *end_index) {
    /*Body does not start in a new slot*/
//            assert(capacity * 2 % ((sizeof(uint64_t) * CHAR_BIT)) == 0);
    size_t temp_index;
    uint64_t temp_slot;
    if (deal_with_joined_slot) {
        temp_index = get_joined_slot_index();
        temp_slot = a[temp_index];
    }

    header_find(q, start_index, end_index);
    header_push(*end_index);

//            /*Restore body's part in the joined cell*/
    if (deal_with_joined_slot) {
        auto mask_bit = (sizeof(uint64_t) * CHAR_BIT) - get_header_bit_index();
        a[temp_index] = (a[temp_index] & (~MASK(mask_bit))) | (temp_slot & MASK(mask_bit));
    }

}

void header_push(size_t end_index) {
    size_t index, last_header_a_slot = get_last_a_index_containing_the_header();
    index = end_index / (sizeof(uint64_t) * CHAR_BIT);

    ulong to_shift = (sizeof(uint64_t) * CHAR_BIT) - 1ul;
    for (uint_fast16_t i = last_header_a_slot; i > index; --i) {
        a[i] = ((ulong) (a[i]) >> 1ul) | ((a[i - 1] & 1ul) << to_shift);
    }


    uint_fast16_t bit_index = end_index % (sizeof(uint64_t) * CHAR_BIT);
    uint_fast16_t shift = (sizeof(uint64_t) * CHAR_BIT) - bit_index;
    ulong mask = MASK(shift);
    ulong upper = a[index] & (~mask);
    uint64_t lower = (a[index] >> 1ul) & mask;
    a[index] = (upper | lower | SL(shift - 1ul));

}

void header_remove(uint64_t q, size_t *start_index, size_t *end_index) {
    /*Body does not start in a new slot*/
//            assert(capacity * 2 % ((sizeof(uint64_t) * CHAR_BIT)) == 0);

    size_t temp_index;
    uint64_t temp_slot;
    if (deal_with_joined_slot) {
        temp_index = get_joined_slot_index();
        temp_slot = a[temp_index];
    }

    header_find(q, start_index, end_index);
    if (DB) {
        if (*start_index == *end_index) {
            std::cout << "trying to remove element not in the PD. Specifically not in the header. "
                      << std::endl;
            return;
        }
    }
    header_pull(*end_index);

    /*Restore body's part in the joined cell*/
    if (deal_with_joined_slot) {
        //Plus one to insure that body's first bit did not effect header last bit.
        //This bit (header last bit) should always be zero.
        auto mask_bit = (sizeof(uint64_t) * CHAR_BIT) - get_header_bit_index() + 1;
        a[temp_index] = (a[temp_index] & (~MASK(mask_bit))) | (temp_slot & MASK(mask_bit));
    }

}

void header_pull(size_t end_index) {
    size_t index = (end_index - 1) / sizeof(uint64_t) *
                   CHAR_BIT, last_header_a_slot = get_last_a_index_containing_the_header();

    if (index == last_header_a_slot) {
        uint_fast16_t bit_index = (end_index - 1) % (sizeof(uint64_t) * CHAR_BIT);
        uint_fast16_t shift = (sizeof(uint64_t) * CHAR_BIT) - bit_index;
        ulong mask = MASK(shift);
        ulong upper = a[index] & (~mask);
        uint64_t mid = ((ulong) a[index] << 1ul) & mask;
        a[index] = upper | mid;
        return;
    }
    uint64_t lower = ((ulong) a[index + 1]) >> ((ulong) ((sizeof(uint64_t) * CHAR_BIT) - 1));

    for (size_t i = index + 1; i < last_header_a_slot; ++i) {
        a[i] = ((ulong) a[i] << 1ul) | ((ulong) a[i + 1] >> ((ulong) ((sizeof(uint64_t) * CHAR_BIT) - 1)));
    }
    a[last_header_a_slot] <<= 1ul;

    uint_fast16_t bit_index = (end_index - 1) % (sizeof(uint64_t) * CHAR_BIT);
    uint_fast16_t shift = (sizeof(uint64_t) * CHAR_BIT) - bit_index;
    ulong mask = MASK(shift);
    ulong upper = a[index] & (~mask);
    uint64_t mid = ((ulong) a[index] << 1ul) & mask;
    a[index] = upper | mid | lower;// | SL(shift);

}

////Body functions
auto body_find(uint64_t r, size_t unpacked_start_index, size_t unpacked_end_index, size_t *p_array_index,
               size_t *p_bit_index) -> bool {
    size_t total_bit_counter = (unpacked_start_index * bits_per_item) + get_header_size_in_bits();
//    size_t total_bit_counter = abstract_body_start_index * bits_per_item;

    /*Empty case. */
    if (unpacked_start_index == unpacked_end_index) {
        *p_array_index = total_bit_counter / BODY_BLOCK_SIZE;
        *p_bit_index = total_bit_counter % BODY_BLOCK_SIZE;
//        *p_array_index = (unpacked_start_index * bits_per_item) / BODY_BLOCK_SIZE;
//        *p_bit_index = (unpacked_start_index * bits_per_item) % BODY_BLOCK_SIZE + get_header_size_in_bits();
        if (DB_PRINT) std::cout << "a1" << std::endl;
        return false;
    }

    size_t comparing_counter = 0, comparing_lim = unpacked_end_index - unpacked_start_index;

    for (; comparing_counter < comparing_lim; ++comparing_counter) {
        size_t B_index = total_bit_counter / BODY_BLOCK_SIZE;
        size_t bit_index_inside_slot = total_bit_counter % BODY_BLOCK_SIZE;
        size_t bits_left_to_read_inside_slot = BODY_BLOCK_SIZE - bit_index_inside_slot;

        BODY_BLOCK_TYPE current_cell = a[B_index];
        /*More than bits_per_item bits remain in B[B_index].*/
        if (bits_left_to_read_inside_slot > bits_per_item) {
            ulong shift = bits_left_to_read_inside_slot - bits_per_item;
            assert(shift < BODY_BLOCK_SIZE);
            BODY_BLOCK_TYPE current_remainder = (current_cell >> (shift)) & MASK(bits_per_item);
            if (r <= current_remainder) {
                if (DB_PRINT) std::cout << "a2" << std::endl;
                body_find_helper(B_index, bits_left_to_read_inside_slot, p_array_index, p_bit_index);
                return r == current_remainder;
            }
            /*Exactly bits_per_item bits remain in B[B_index].*/
        } else if (bits_left_to_read_inside_slot == bits_per_item) {
            BODY_BLOCK_TYPE current_remainder = current_cell & MASK(bits_per_item);
            if (r <= current_remainder) {
                if (DB_PRINT) std::cout << "a3" << std::endl;
                body_find_helper(B_index, bits_left_to_read_inside_slot, p_array_index, p_bit_index);
                return r == current_remainder;
            }
            /*Less than bits_per_item bits remain in B[B_index].*/
        } else {
            size_t number_of_bits_to_read_from_next_slot = bits_per_item - bits_left_to_read_inside_slot;
            ulong upper_shift = bits_per_item - bits_left_to_read_inside_slot;
            assert(upper_shift >= 0 and upper_shift < BODY_BLOCK_SIZE);
            ulong upper = (current_cell & MASK(bits_left_to_read_inside_slot)) << (upper_shift);
            assert(size > B_index + 1);
            ulong lower_shift = BODY_BLOCK_SIZE - number_of_bits_to_read_from_next_slot;
            assert(0 <= lower_shift and lower_shift < BODY_BLOCK_SIZE);
            ulong lower = (a[B_index + 1] >> lower_shift) & MASK(number_of_bits_to_read_from_next_slot);
            BODY_BLOCK_TYPE current_remainder = upper | lower;
            if (r <= current_remainder) {
                if (DB_PRINT) std::cout << "a4" << std::endl;
                body_find_helper(B_index, bits_left_to_read_inside_slot, p_array_index, p_bit_index);
                return r == current_remainder;
            }
        }
        total_bit_counter += bits_per_item;
    }
    *p_array_index = total_bit_counter / BODY_BLOCK_SIZE;
    *p_bit_index = total_bit_counter % BODY_BLOCK_SIZE;
    if (DB_PRINT) std::cout << "a5" << std::endl;
    return false;


}

void body_insert(uint64_t r, size_t unpacked_start_index, size_t unpacked_end_index) {
    size_t temp_index;
    uint64_t temp_slot;
    if (deal_with_joined_slot) {
        temp_index = get_joined_slot_index();
        temp_slot = a[temp_index];
    }

    size_t B_index = -1, bit_index = -1;
    auto res = body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index);
    body_push(r, B_index, bit_index);

    if (deal_with_joined_slot) {
        auto mask_bit = (sizeof(uint64_t) * CHAR_BIT) - get_header_bit_index();
        a[temp_index] = (a[temp_index] & (~MASK(mask_bit))) | (temp_slot & MASK(mask_bit));
    }
}

void body_push(uint64_t r, size_t B_index, size_t bit_index) {
//    size_t B_index = -1, bit_index = -1;
//    auto res = body_find(unpacked_start_index, unpacked_end_index, r, &B_index, &bit_index);
    size_t left_bit_index = BODY_BLOCK_SIZE - bit_index;
    for (size_t i = size - 1; i > B_index; --i) {
        a[i] = (a[i] >> bits_per_item) | ((a[i - 1]) << (BODY_BLOCK_SIZE - bits_per_item));
    }

    if (BODY_BLOCK_SIZE >= bits_per_item + bit_index) {
        ulong mask = MASK(left_bit_index);
        ulong upper = a[B_index] & (~mask);
        BODY_BLOCK_TYPE mid = r << (left_bit_index - bits_per_item);
        BODY_BLOCK_TYPE lower = (a[B_index] >> bits_per_item) & (MASK(left_bit_index - bits_per_item));
        a[B_index] = (upper | lower | mid);
        assert(left_bit_index - bits_per_item >= 0);
    } else { // Prevents negative shifting.
        size_t shift = left_bit_index;
        ulong mask = MASK(left_bit_index);
        ulong upper = a[B_index] & (~mask);
        BODY_BLOCK_TYPE lower = r >> (bits_per_item - left_bit_index);
        a[B_index] = (upper | lower);

        assert(bits_per_item - shift > 0);

        //same amount that r was shifted right by. (bits_per_item - shift)
        size_t bits_left = bits_per_item - shift; // bits_left =  bits_per_item + bit_index - BODY_BLOCK_SIZE
        upper = (r & MASK(bits_left)) << (BODY_BLOCK_SIZE - bits_left); // todo Check this.
        lower = (a[B_index + 1] << bits_left) >> bits_left; // clear lower's upper-bits. todo try mask instead.
        a[B_index + 1] = (upper | lower);
    }
//    capacity++;
}

void body_remove(uint64_t r, size_t unpacked_start_index, size_t unpacked_end_index) {
    /*Body does not start in a new slot*/
//            assert(capacity * 2 % ((sizeof(uint64_t) * CHAR_BIT)) == 0);

    size_t temp_index;
    uint64_t temp_slot;
    if (deal_with_joined_slot) {
        temp_index = get_joined_slot_index();
        temp_slot = a[temp_index];
    }

    size_t B_index = -1, bit_index = -1;
    auto res = body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index);
    if (not res) {
        body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index);
        std::cout << "trying to remove element not in the PD. "
                     "Specifically not in the Body (might be in the header). " << std::endl;
        return;
    }
    body_pull(B_index, bit_index);

    if (deal_with_joined_slot) {
        auto mask_bit = (sizeof(uint64_t) * CHAR_BIT) - get_header_bit_index();
        a[temp_index] = (a[temp_index] & (MASK(mask_bit))) | (temp_slot & (~MASK(mask_bit)));
    }
}

auto body_conditional_remove(uint64_t r, size_t unpacked_start_index, size_t unpacked_end_index) -> bool {
    /*Body does not start in a new slot*/
//            assert(capacity * 2 % ((sizeof(uint64_t) * CHAR_BIT)) == 0);

    size_t temp_index;
    uint64_t temp_slot;

    if (deal_with_joined_slot) {
        temp_index = get_joined_slot_index();
        temp_slot = a[temp_index];
    }

    size_t B_index = -1, bit_index = -1;
    auto res = body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index);
    if (not res) {
        return false;
    }
    body_pull(B_index, bit_index);

    if (deal_with_joined_slot) {
        auto mask_bit = (sizeof(uint64_t) * CHAR_BIT) - get_header_bit_index();
        a[temp_index] = (a[temp_index] & (MASK(mask_bit))) | (temp_slot & (~MASK(mask_bit)));
    }
    return true;
}

void body_pull(size_t B_index, size_t bit_index) {
    size_t left_fp_start_index = BODY_BLOCK_SIZE - bit_index;

    if (B_index == size - 1) {
        assert(bit_index + bits_per_item <= BODY_BLOCK_SIZE);

//        ulong shift = left_fp_start_index;
        assert(left_fp_start_index >= 0);
        ulong mask = MASK(left_fp_start_index);
        ulong upper = a[B_index] & (~mask);
        BODY_BLOCK_TYPE mid = (a[B_index] & MASK(left_fp_start_index - bits_per_item)) << bits_per_item;
        assert(left_fp_start_index >= bits_per_item);
        a[B_index] = (upper | mid);
        return;
    }

    if (BODY_BLOCK_SIZE >= bits_per_item + bit_index) {
        ulong shift = left_fp_start_index;
        ulong mask = MASK(left_fp_start_index);
        ulong upper = a[B_index] & (~mask);
        BODY_BLOCK_TYPE mid = (a[B_index] & MASK(left_fp_start_index - bits_per_item)) << bits_per_item;
        BODY_BLOCK_TYPE lower = (a[B_index + 1]) >> (BODY_BLOCK_SIZE - bits_per_item);
        a[B_index] = (upper | lower | mid);

        assert(shift >= bits_per_item);
        assert(BODY_BLOCK_SIZE - bits_per_item >= 0);

        for (size_t i = B_index + 1; i < size - 1; ++i) {
            a[i] = (a[i] << bits_per_item) | (a[i + 1] >> (BODY_BLOCK_SIZE - bits_per_item));
        }
        a[size - 1] <<= bits_per_item;

    } else {
        ulong shift = left_fp_start_index;
        ulong mask = MASK(left_fp_start_index);
        ulong upper = a[B_index] & (~mask);
        ulong lower_shift = BODY_BLOCK_SIZE - bits_per_item;
        BODY_BLOCK_TYPE lower = a[B_index + 1] >> lower_shift;
        lower &= MASK(left_fp_start_index);
        a[B_index] = upper | lower;

        for (size_t i = B_index + 1; i < size - 1; ++i) {
            a[i] = (a[i] << bits_per_item) | (a[i + 1] >> (BODY_BLOCK_SIZE - bits_per_item));
        }
        a[size - 1] <<= bits_per_item;

        assert(0 <= shift and shift < bits_per_item);
        assert(0 <= lower_shift and lower_shift < BODY_BLOCK_SIZE);
    }

}

auto get_last_a_index_containing_the_header() -> size_t {
    return (quot_range * 2 - 1) / ((sizeof(uint64_t) * CHAR_BIT));
}

auto get_header_bit_index() -> size_t {
    auto temp = (quot_range << 1u);
    return temp % ((sizeof(uint64_t) * CHAR_BIT));
}

auto get_joined_slot_index() -> size_t {
    return get_last_a_index_containing_the_header();
}

//size_t get_header_size_in_bits() {
//    return capacity << 1u;
//}

auto get_a_size(size_t m, size_t f, size_t l) -> size_t {
    return INTEGER_ROUND(((l + 2) * f), ((sizeof(uint64_t) * CHAR_BIT)));
}

size_t get_number_of_bits_in_a(size_t m, size_t f, size_t l) {
    return (l + 2) * f;
}

auto get_a() const -> uint32_t * {
    return a;
}

auto get_bits_per_item() const -> const uint_fast16_t {
    return bits_per_item;
}

auto get_capacity() const -> const uint_fast16_t {
    return capacity;
}

auto get_size() const -> const uint_fast16_t {
    return size;
}

auto get_deal_with_joined_slot() const -> const bool {
    return deal_with_joined_slot;
    /*Body does not start in a new slot*/
//            assert(capacity * 2 % ((sizeof(uint64_t) * CHAR_BIT)) == 0);
//            return deal_with_joined_slot;
}

/*
   void print_as_array() const {
    print_array_as_integers<uint32_t>(a, size);
   }

   void print_as_consecutive_memory() {
    print_array_as_consecutive_memory<uint64_t>(a, size, std::cout);
   }

   auto operator<<(ostream &os, const PD &pd) -> ostream & {
    print_array_as_consecutive_memory<uint64_t>(pd.a, pd.size, std::cout);
    return os;
   }
 */




//    ~PD() {
//        delete[] a;
//    }




auto header_lookup(CG_TYPE q, size_t *start_index, size_t *end_index) -> bool;

void header_insert(CG_TYPE q, size_t *start_index, size_t *end_index);

void header_remove(CG_TYPE q, size_t *start_index, size_t *end_index);

void header_find(CG_TYPE q, size_t *start, size_t *end);

void header_push(size_t end_index);

void header_pull(size_t end_index);

static auto get_number_of_bits_in_a(size_t m, size_t f, size_t l) -> size_t;

auto get_header_bit_index() -> size_t;

inline auto get_header_size_in_bits() -> size_t {
    return capacity << 1u;
}

auto get_joined_slot_index() -> size_t;

auto body_find(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index, size_t *p_array_index,
               size_t *p_bit_index) -> bool;

void body_insert(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index);

void body_push(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index);

void body_remove(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index);

auto body_conditional_remove(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index) -> bool;

/**
 * I think! Moves all elements after the element that starts at "bit_index" to their predecessor position.
 * @param B_index
 * @param bit_index
 */
void body_pull(size_t B_index, size_t bit_index);

public:

/*For testing*/
auto get_a() const -> uint32_t *;

auto get_fp_size() const -> const uint_fast16_t;

auto get_capacity() const -> const uint_fast16_t;

auto get_size() const -> const uint_fast16_t;

auto get_deal_with_joined_slot() const -> const bool;

void print_as_array() const;

#endif //FILTER_PD_JUNK_HPP
