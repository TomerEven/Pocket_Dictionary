//
// Created by tomereven on 02/08/2020.
//

#ifndef FILTERS_CCPD_HPP
#define FILTERS_CCPD_HPP

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <ctgmath>
#include <climits>
#include <iomanip>
#include <cstring>
#include "immintrin.h"
#include "../../Global_functions/macros.h"

#define PSE_CHAR uint64_t

static auto select64(uint64_t x, int64_t j) -> uint64_t {
    assert(j < 64);
    const uint64_t y = _pdep_u64(UINT64_C(1) << j, x);
    return _tzcnt_u64(y);
}

static inline void
cc_body_find_helper(size_t current_b_index, size_t bits_left, size_t *p_B_index, size_t *p_bit_index) {
    *p_B_index = current_b_index;
    *p_bit_index = 64 - bits_left;
}


static bool
cc_is_aligned(const void *ptr, std::uintptr_t alignment = 64u) noexcept {
    auto iptr = reinterpret_cast<std::uintptr_t>(ptr);
    return !(iptr % alignment);
}

template<size_t bits_per_item = 8, size_t capacity = 51, size_t quot_range = 51>
class alignas(64) cc_pd {
    uint64_t a[8] __attribute__((aligned(64)));
    uint64_t b[8] __attribute__((aligned(64))); // For validation.
    uint64_t c[8] __attribute__((aligned(64))); // For validation.

public:
    cc_pd(size_t m, size_t f, size_t l) {
        assert(bits_per_item == 8);
        assert(capacity == 51);
        assert(quot_range == 51);
        a[0] = (1ULL << 50ul) - 1u;
        b[0] = (1ULL << 50ul) - 1u;
        c[0] = -1u ^ ((1ul << 14u) - 1);
        /*
         uint64_t mask = MASK(14);
        a[0] = (-1) & (~mask);
        b[0] = (-1) & (~mask);
         */
        std::fill(&a[1], a + 8, 0);
        std::fill(&b[1], b + 8, 0);
        std::fill(&c[1], c + 8, 0);

        std::cout << __builtin_clz(a[0]) << std::endl;
        std::cout << __builtin_clzl(a[0]) << std::endl;
        std::cout << __builtin_ctz(a[0]) << std::endl;
        std::cout << __builtin_ctzl(a[0]) << std::endl;

        assert(cc_is_aligned(a));
        assert(cc_is_aligned(b));
        assert(cc_is_aligned(c));

        assert(__builtin_popcountll(a[0]) == __builtin_popcountll(b[0]));
        assert(__builtin_popcountll(a[0]) == __builtin_popcountll(c[0]));
    }

    virtual ~cc_pd() {}


    auto lookup(uint64_t q, PSE_CHAR rem) -> bool {
        assert(memcmp(a, b, 64) == 0);
//        assert(cmp_pd_and_c(a));
        bool a_res = h_lookup(q, rem, a);
        bool b_res = h_lookup(q, rem, b);
        assert(a_res == b_res);
//        bool c_res = c_lookup(q, rem, b);
//        assert(a_res == c_res);
        assert(memcmp(a, b, 64) == 0);
        return res;
    }

    void insert(uint64_t q, PSE_CHAR rem) {
        assert(memcmp(a, b, 64) == 0);
        h_insert(q, rem, a);
        h_insert(q, rem, b);
        assert(memcmp(a, b, 64) == 0);
    }

    void remove(uint64_t q, PSE_CHAR rem) {
        assert(memcmp(a, b, 64) == 0);
        h_remove(q, rem, a);
        h_remove(q, rem, b);
        assert(memcmp(a, b, 64) == 0);
    }

    auto conditional_remove(uint64_t q, PSE_CHAR rem) -> bool {
        assert(memcmp(a, b, 64) == 0);
        bool res = h_conditional_remove(q, rem, a);
        bool valid = h_conditional_remove(q, rem, b);
        assert(res == valid);
        assert(memcmp(a, b, 64) == 0);
    }

    auto h_lookup(uint64_t q, PSE_CHAR rem, uint64_t *pd) -> bool {
        auto tp = get_interval(q, pd);
        auto tp_val = get_interval_naive(q, pd);
        assert(tp == tp_val);
        assert(std::get<0>(tp) == std::get<0>(tp_val));
        assert(std::get<1>(tp) == std::get<1>(tp_val));

        uint64_t start = std::get<0>(tp), end = std::get<1>(tp);

        assert((q <= start) and (start <= end));

        size_t unpacked_start_index = start - q;
        size_t unpacked_end_index = end - q;

        auto res = body_lookup(unpacked_start_index, unpacked_end_index, rem, pd);

        size_t B_index = -1, bit_index = -1;
        auto val = body_find(rem, unpacked_start_index, unpacked_end_index, &B_index, &bit_index, pd);
        assert(res == val);
        return res;
    }

    void h_insert(uint64_t q, PSE_CHAR r, uint64_t *pd) {

        assert(get_capacity(pd) < capacity);
        assert(q < quot_range);

        size_t start_index = -1, end_index = -1;
        header_insert(q, &start_index, &end_index, pd);

        assert((q <= start_index) and (start_index <= end_index));

        size_t unpacked_start_index = start_index - q;
        size_t unpacked_end_index = end_index - q;

        body_insert(r, unpacked_start_index, unpacked_end_index, pd);
    }

    void h_remove(uint64_t q, PSE_CHAR r, uint64_t *pd) {
        size_t start_index = -1, end_index = -1;
        header_remove(q, &start_index, &end_index, pd);

        assert(q <= start_index <= end_index);

        size_t unpacked_start_index = start_index - q;
        size_t unpacked_end_index = end_index - q;

        body_remove(r, unpacked_start_index, unpacked_end_index, pd);
    }


    auto h_conditional_remove(uint64_t q, PSE_CHAR r, uint64_t *pd) -> bool {
//    return naive_conditional_remove(q, r);
        size_t start_index = -1, end_index = -1;
        if (not header_lookup(q, &start_index, &end_index, pd))
            return false;

        assert(q <= start_index);
        assert(start_index <= end_index);

        size_t unpacked_start_index = start_index - q;
        size_t unpacked_end_index = end_index - q;
        if (body_conditional_remove(r, unpacked_start_index, unpacked_end_index, pd)) {
            header_pull(end_index, pd);
            return true;
        }
        return false;
    }

    auto is_full(uint64_t *pd) -> bool {
        return get_capacity(pd) == capacity;
    }

    auto get_capacity(uint64_t *pd) -> size_t {
        uint64_t header[2];
        memcpy(header, pd, 13);
        header[1] = header[1] & ((1ULL << 37ul) - 1u);

        auto h0_one_count = _mm_popcnt_u64(header[0]);
        if (h0_one_count == 50) {
            auto index = select64(header[0], 49);
            assert(index < 64);
            auto res = index - 49;
            assert(res == get_capacity_naive(pd));
            return res;
        } else {
            auto h0_zero_count = 64 - h0_one_count;
            auto ones_left = 49 - h0_one_count;
            // bool cond =
            assert(ones_left >= 0);
            auto index = select64(header[1], 49 - h0_one_count);
            assert(index < 64);
            assert(index <= 37);
            assert(index >= ones_left);
            auto res = index - ones_left + h0_zero_count;
            bool cond = res == get_capacity_naive(pd);
            if (!cond) {
                std::cout << "h0_zero_count " << h0_zero_count << std::endl;
                std::cout << "h0_one_count " << h0_one_count << std::endl;
                std::cout << res << std::endl;
                std::cout << get_capacity_naive(pd) << std::endl;
                assert(false);
            }
            assert(res == get_capacity_naive(pd));
            return res;
            return index - ones_left;
        }
    }

    auto get_capacity_naive(uint64_t *pd) -> size_t {
        uint64_t header[2];
        memcpy(header, pd, 13);
        size_t zero_count = 0, one_count = 0;
        for (size_t j = 0; j < 2; j++) {
            uint64_t temp = header[j];
            uint64_t b = 1ULL;
            for (size_t i = 0; i < 64; i++) {
                if (b & temp) {
                    one_count++;
                    if (one_count == 50)
                        return zero_count;
                } else {
                    zero_count++;
                }
                b <<= 1ul;
            }
        }
        std::cout << zero_count << std::endl;
        std::cout << one_count << std::endl;
        assert(false);
    }


    auto get_name() -> std::string {
        std::string a = std::to_string(sizeof(uint64_t) * CHAR_BIT);
        std::string b = std::to_string(bits_per_item);
        std::string c = std::to_string(capacity);
        return "TPD:<" + a + ", " + b + ", " + c + ">";
    }

    auto cmp_pd_and_c(uint64_t *pd) -> bool {
        uint64_t temp[8];
        reverse_array(c, temp, 8);
        return memcmp(a, d, 64) == 0);
    }

private:
    auto get_header_size_in_bits() -> size_t {
        return quot_range << 1u;
    }


////Header functions
    void header_find(uint64_t q, size_t *start, size_t *end, uint64_t *pd) {
        auto tp = get_interval(q, pd);
        *start = std::get<0>(tp);
        *end = std::get<1>(tp);
    }

    auto header_lookup(uint64_t q, size_t *start_index, size_t *end_index, uint64_t *pd) -> bool {
        header_find(q, start_index, end_index, pd);
        assert(*start_index <= *end_index);
        return (*start_index != *end_index);
    }

    void header_insert(uint64_t q, size_t *start_index, size_t *end_index, uint64_t *pd) {
        uint64_t temp_slot = pd[1];

        header_find(q, start_index, end_index, pd);
        header_push(*end_index, pd);

        uint64_t mask = MASK(25ul);
        pd[1] = (pd[1] & (~mask)) | (temp_slot & mask);

    }

    void header_remove(uint64_t q, size_t *start_index, size_t *end_index, uint64_t *pd) {

        uint64_t temp_slot = pd[1];

        header_find(q, start_index, end_index, pd);
        header_pull(*end_index, pd);

        uint64_t mask = MASK(25ul);
        pd[1] = (pd[1] & (~mask)) | (temp_slot & mask);

    }

    void header_push(size_t end_index, uint64_t *pd) {

        if (end_index > 64) {
            assert(end_index <= (capacity << 1u));
//            uint64_t upper = pd[0] << 63ul;
            uint_fast16_t bit_index = end_index % (sizeof(uint64_t) * CHAR_BIT);
            uint_fast16_t shift = (sizeof(uint64_t) * CHAR_BIT) - bit_index;
            ulong mask = MASK(shift);
            ulong mid = pd[1] & (~mask);
            uint64_t lower = (pd[1] >> 1ul) & mask;
            pd[1] = mid | lower;
            return;
        } else if (end_index == 64) {
            pd[1] >>= 1ul;
            return;
        }

        pd[1] = (pd[1] >> 1ul) | (pd[0] << 63ul);
        uint_fast16_t shift = (sizeof(uint64_t) * CHAR_BIT) - end_index;
        ulong mask = MASK(shift);
        ulong upper = pd[0] & (~mask);
        uint64_t lower = (pd[0] >> 1ul) & mask;
        pd[0] = (upper | lower);
        return;
    }

    void header_pull(size_t end_index, uint64_t *pd) {

        if (end_index > 64) {
            assert(end_index <= (capacity << 1u));
            uint_fast16_t bit_index = end_index % (sizeof(uint64_t) * CHAR_BIT);
            uint_fast16_t shift = (sizeof(uint64_t) * CHAR_BIT) - bit_index;
            ulong mask = MASK(shift);
            ulong upper = pd[1] & (~mask);
            uint64_t lower = (pd[1] << 1ul) & mask;
            pd[1] = (upper | lower);
            return;
        } else if (end_index == 64) {
            assert(pd[1] >> 63ul);
            pd[1] <<= 1ul;
            pd[0] | 1u;
            return;
        }

        uint64_t lower = pd[1] >> 63ul;

        uint_fast16_t shift = (sizeof(uint64_t) * CHAR_BIT) - end_index;
        ulong mask = MASK(shift);
        ulong upper = pd[0] & (~mask);
        uint64_t mid = (pd[0] << 1ul) & mask;
        pd[0] = upper | mid | lower;
        return;

    }

////Body functions
    auto body_lookup(uint64_t begin, uint64_t end, PSE_CHAR rem, uint64_t *pd) -> bool {
        assert(begin <= end);
        assert(0 <= begin);
        assert(end <= capacity);
        const __m512i target = _mm512_set1_epi8(rem);

        assert(cc_is_aligned(a));
        assert(cc_is_aligned(b));
        assert(cc_is_aligned(pd));

        __m512i vec = _mm512_load_si512((__m512i *) pd);
        uint64_t v = _mm512_cmpeq_epu8_mask(target, vec);
        // round up to remove the header
        v = v >> ((51 + 50 + CHAR_BIT - 1) / CHAR_BIT);
        return (v & ((UINT64_C(1) << end) - 1)) >> begin;
    }

    auto body_find(PSE_CHAR r, size_t unpacked_start_index, size_t unpacked_end_index, size_t *p_array_index,
                   size_t *p_bit_index, uint64_t *pd) -> bool {
        size_t total_bit_counter = (unpacked_start_index * bits_per_item) + get_header_size_in_bits();
//    size_t total_bit_counter = abstract_body_start_index * bits_per_item;

        /*Empty case. */
        if (unpacked_start_index == unpacked_end_index) {
            *p_array_index = total_bit_counter / 64;
            *p_bit_index = total_bit_counter % 64;
//        *p_array_index = (unpacked_start_index * bits_per_item) / 64;
//        *p_bit_index = (unpacked_start_index * bits_per_item) % 64 + get_header_size_in_bits();
            if (DB_PRINT) std::cout << "a1" << std::endl;
            return false;
        }

        size_t comparing_counter = 0, comparing_lim = unpacked_end_index - unpacked_start_index;

        for (; comparing_counter < comparing_lim; ++comparing_counter) {
            size_t B_index = total_bit_counter / 64;
            size_t bit_index_inside_slot = total_bit_counter % 64;
            size_t bits_left_to_read_inside_slot = 64 - bit_index_inside_slot;

            uint64_t current_cell = pd[B_index];
            /*More than bits_per_item bits remain in B[B_index].*/
            if (bits_left_to_read_inside_slot > bits_per_item) {
                ulong shift = bits_left_to_read_inside_slot - bits_per_item;
                assert(shift < 64);
                uint64_t current_remainder = (current_cell >> (shift)) & MASK(bits_per_item);
                if (r <= current_remainder) {
                    if (DB_PRINT) std::cout << "a2" << std::endl;
                    cc_body_find_helper(B_index, bits_left_to_read_inside_slot, p_array_index, p_bit_index);
                    return r == current_remainder;
                }
                /*Exactly bits_per_item bits remain in B[B_index].*/
            } else if (bits_left_to_read_inside_slot == bits_per_item) {
                uint64_t current_remainder = current_cell & MASK(bits_per_item);
                if (r <= current_remainder) {
                    if (DB_PRINT) std::cout << "a3" << std::endl;
                    cc_body_find_helper(B_index, bits_left_to_read_inside_slot, p_array_index, p_bit_index);
                    return r == current_remainder;
                }
                /*Less than bits_per_item bits remain in B[B_index].*/
            } else {
                size_t number_of_bits_to_read_from_next_slot = bits_per_item - bits_left_to_read_inside_slot;
                ulong upper_shift = bits_per_item - bits_left_to_read_inside_slot;
                assert(upper_shift >= 0 and upper_shift < 64);
                ulong upper = (current_cell & MASK(bits_left_to_read_inside_slot)) << (upper_shift);
                assert(8 > B_index + 1);
                ulong lower_shift = 64 - number_of_bits_to_read_from_next_slot;
                assert(0 <= lower_shift and lower_shift < 64);
                ulong lower = (pd[B_index + 1] >> lower_shift) & MASK(number_of_bits_to_read_from_next_slot);
                uint64_t current_remainder = upper | lower;
                if (r <= current_remainder) {
                    if (DB_PRINT) std::cout << "a4" << std::endl;
                    cc_body_find_helper(B_index, bits_left_to_read_inside_slot, p_array_index, p_bit_index);
                    return r == current_remainder;
                }
            }
            total_bit_counter += bits_per_item;
        }
        *p_array_index = total_bit_counter / 64;
        *p_bit_index = total_bit_counter % 64;
        if (DB_PRINT) std::cout << "a5" << std::endl;
        return false;


    }

    void body_insert(PSE_CHAR r, size_t unpacked_start_index, size_t unpacked_end_index, uint64_t *pd) {
        if (unpacked_start_index > 2) {
            size_t B_index = -1, bit_index = -1;
            auto res = body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index, pd);
            body_push(r, B_index, bit_index, pd);
            std::cout << "j1" << std::endl;
            return;
        }

        uint64_t temp_slot = pd[1];

        size_t B_index = -1, bit_index = -1;
        auto res = body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index, pd);
        body_push(r, B_index, bit_index, pd);

        uint64_t mask = MASK(25ul);
        pd[1] = (pd[1] & (~mask)) | (temp_slot & mask);
        std::cout << "j2" << std::endl;

    }

    void body_push(PSE_CHAR r, size_t B_index, size_t bit_index, uint64_t *pd) {
//    size_t B_index = -1, bit_index = -1;
//    auto res = body_find(unpacked_start_index, unpacked_end_index, r, &B_index, &bit_index);
        size_t left_bit_index = 64 - bit_index;
        for (size_t i = 8 - 1; i > B_index; --i) {
            pd[i] = (pd[i] >> bits_per_item) | ((pd[i - 1]) << (64 - bits_per_item));
        }

        if (64 >= bits_per_item + bit_index) {
            ulong mask = MASK(left_bit_index);
            ulong upper = pd[B_index] & (~mask);
            uint64_t mid = r << (left_bit_index - bits_per_item);
            uint64_t lower = (pd[B_index] >> bits_per_item) & (MASK(left_bit_index - bits_per_item));
            pd[B_index] = (upper | lower | mid);
            assert(left_bit_index - bits_per_item >= 0);
        } else { // Prevents negative shifting.
            size_t shift = left_bit_index;
            ulong mask = MASK(left_bit_index);
            ulong upper = pd[B_index] & (~mask);
            uint64_t lower = r >> (bits_per_item - left_bit_index);
            pd[B_index] = (upper | lower);

            assert(bits_per_item - shift > 0);

            //same amount that r was shifted right by. (bits_per_item - shift)
            size_t bits_left = bits_per_item - shift; // bits_left =  bits_per_item + bit_index - 64
            upper = (r & MASK(bits_left)) << (64 - bits_left); // todo Check this.
            lower = (pd[B_index + 1] << bits_left) >> bits_left; // clear lower's upper-bits. todo try mask instead.
            pd[B_index + 1] = (upper | lower);
        }
//    capacity++;
    }

    void body_remove(PSE_CHAR r, size_t unpacked_start_index, size_t unpacked_end_index, uint64_t *pd) {
        uint64_t temp_slot = pd[1];

        size_t B_index = -1, bit_index = -1;
        auto res = body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index, pd);
        if (not res) {
            body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index, pd);
            std::cout << "trying to remove element not in the PD. "
                         "Specifically not in the Body (might be in the header). " << std::endl;
            return;
        }
        body_pull(B_index, bit_index, pd);

        uint64_t mask = MASK(25ul);
        pd[1] = (pd[1] & (~mask)) | (temp_slot & mask);
    }

    auto
    body_conditional_remove(PSE_CHAR r, size_t unpacked_start_index, size_t unpacked_end_index, uint64_t *pd) -> bool {
        uint64_t temp_slot = pd[1];

        size_t B_index = -1, bit_index = -1;
        auto res = body_find(r, unpacked_start_index, unpacked_end_index, &B_index, &bit_index, pd);
        if (not res) {
            return false;
        }
        body_pull(B_index, bit_index, pd);

        uint64_t mask = MASK(25ul);
        pd[1] = (pd[1] & (~mask)) | (temp_slot & mask);

        return true;
    }

    void body_pull(size_t B_index, size_t bit_index, uint64_t *pd) {
        size_t left_fp_start_index = 64 - bit_index;

        if (B_index == 8 - 1) {
            assert(bit_index + bits_per_item <= 64);

//        ulong shift = left_fp_start_index;
            assert(left_fp_start_index >= 0);
            ulong mask = MASK(left_fp_start_index);
            ulong upper = pd[B_index] & (~mask);
            uint64_t mid = (pd[B_index] & MASK(left_fp_start_index - bits_per_item)) << bits_per_item;
            assert(left_fp_start_index >= bits_per_item);
            pd[B_index] = (upper | mid);
            return;
        }

        if (64 >= bits_per_item + bit_index) {
            ulong shift = left_fp_start_index;
            ulong mask = MASK(left_fp_start_index);
            ulong upper = pd[B_index] & (~mask);
            uint64_t mid = (pd[B_index] & MASK(left_fp_start_index - bits_per_item)) << bits_per_item;
            uint64_t lower = (pd[B_index + 1]) >> (64 - bits_per_item);
            pd[B_index] = (upper | lower | mid);

            assert(shift >= bits_per_item);
            assert(64 - bits_per_item >= 0);

            for (size_t i = B_index + 1; i < 8 - 1; ++i) {
                pd[i] = (pd[i] << bits_per_item) | (pd[i + 1] >> (64 - bits_per_item));
            }
            pd[8 - 1] <<= bits_per_item;

        } else {
            ulong shift = left_fp_start_index;
            ulong mask = MASK(left_fp_start_index);
            ulong upper = pd[B_index] & (~mask);
            ulong lower_shift = 64 - bits_per_item;
            uint64_t lower = pd[B_index + 1] >> lower_shift;
            lower &= MASK(left_fp_start_index);
            pd[B_index] = upper | lower;

            for (size_t i = B_index + 1; i < 8 - 1; ++i) {
                pd[i] = (pd[i] << bits_per_item) | (pd[i + 1] >> (64 - bits_per_item));
            }
            pd[8 - 1] <<= bits_per_item;

            assert(0 <= shift and shift < bits_per_item);
            assert(0 <= lower_shift and lower_shift < 64);
        }

    }


//// For validation
    auto get_last_a_index_containing_the_header() -> size_t {
        return (quot_range * 2 - 1) / ((sizeof(uint64_t) * CHAR_BIT));
    }

    size_t get_number_of_bits_in_a(size_t m, size_t f, size_t l) {
        return (l + 2) * f;
    }

    auto get_a() -> uint64_t * {
        return a;
    }

    auto get_b() -> uint64_t * {
        return b;
    }

    auto get_bits_per_item() const -> const uint_fast16_t {
        return bits_per_item;
    }

    auto get_max_capacity() const -> const uint_fast16_t {
        return capacity;
    }

    auto get_size() const -> const uint_fast16_t {
        return 8;
    }

//// Interval
    auto get_interval(uint64_t q, uint64_t *pd) -> std::tuple<uint64_t, uint64_t> {
        uint64_t start = 0, end = 0;
        if (q == 0) {
            end = __builtin_ctzl(pd[0]);
            assert(end == select64(pd[0], 0));
            assert(end < 64);
            bool end_is_zero_validation = (end != 0) or (pd[0] & ((1ULL) << 63u));
            assert(end_is_zero_validation);
            return std::tuple<uint64_t, uint64_t>{start, end};
        }

        if (__builtin_popcountll(pd[0]) == q) {
            assert(select64(pd[0], q) < 64);
        }

        auto temp = select64(pd[0], q);
        if (temp < 64) {
            start = temp;
            auto end_temp = select64(pd[0], q);
            end = (end_temp < 64) ? end_temp : __builtin_ctzl(pd[1]);
            return std::tuple<uint64_t, uint64_t>{start, end};
        }

        uint64_t count = __builtin_popcountll(pd[0]);
        assert (count < q);
//        if (count == q - 1)
        uint64_t new_count = q - count;
        start = select64(pd[1], new_count);
        assert(start < 64);
        end = select64(pd[1], new_count + 1);
        assert(end < 64);
        return std::tuple<uint64_t, uint64_t>{start, end};
    }

    auto get_interval_naive(uint64_t q, uint64_t *pd) -> std::tuple<uint64_t, uint64_t> {
        constexpr size_t slot_size = sizeof(uint64_t) * CHAR_BIT;
        if (q == 0) {
            for (int j = 0; j < 2; ++j) {
                uint64_t bit = 1ULL;
                for (int i = 0; i < slot_size; ++i) {
                    if (bit & pd[j]) {
                        return std::tuple<uint64_t, uint64_t>{0, i + j * slot_size};
                    }
                    bit <<= 1u;
                }
            }
            assert (false);
        }

        uint64_t counter = 0;
        uint64_t start, end;

        for (int j = 0; j < 2; ++j) {
            uint64_t bit = 1ULL;
            for (int i = 0; i < slot_size; ++i) {
                if (bit & pd[j]) {
                    counter++;
                    if (counter == q) {
                        start = i + j * slot_size;
                    }
                    if (counter == q + 1) {
                        return std::tuple<uint64_t, uint64_t>{start, i + j * slot_size};
                    }
                }
                bit <<= 1u;
            }
        }
        assert (false);
    }

    auto get_interval_b(uint64_t q, PSE_CHAR rem) -> std::tuple<uint64_t, uint64_t> {
        assert(false);
        uint64_t start = 0, end = 0;
        if (q == 0) {
            start = 0;
            end = __builtin_ctzl(b[0]);
            return std::tuple<uint64_t, uint64_t>{start, end};
        }

        size_t zero_count = 0, one_count = 0;
        for (size_t j = 0; j < 2; j++) {
            uint64_t temp = b[j];
            uint64_t b = 1ULL;
            for (size_t i = 0; i < 64; i++) {
                if (b & temp) {
                    one_count++;
                    if (one_count == q)
                        start = i + (j * 64);
                    else if (one_count == q + 1)
                        return std::tuple<uint64_t, uint64_t>{start, i + (j * 64)};

                } else {
                    zero_count++;
                }

                b <<= 1ul;
            }
        }
        std::cout << zero_count << std::endl;
        std::cout << one_count << std::endl;
        assert(false);
    }

//// Printing
    void print_as_array() const;

    friend auto operator<<(std::ostream &os, const cc_pd<bits_per_item, capacity, quot_range> &pd) -> std::ostream & {
        print_array_as_consecutive_memory<uint64_t>(pd.a, 8, cout);
        print_array_as_consecutive_memory(pd.b, 8, cout);
        return os;
    }

};
//template<size_t bits_per_item = 8, size_t capacity = 51, size_t quot_range = 50>
//auto operator<<(std::ostream &os, const cc_pd<bits_per_item, capacity, quot_range> &pd) -> ostream & {
//    print_array_as_consecutive_memory(pd.pd, 8, cout);
//    return os;
//}



/*
uint32_t select_r(uint64_t slot, uint32_t rank) {
//    uint64_t slot;          // Input value to find position with rank rank.
//    unsigned int rank;      // Input: bit's desired rank [1-64].
    unsigned int s;  // Output: Resulting position of bit with the desired rank.[1-64]
    uint64_t pd, b, c, d; // Intermediate temporaries for bit count.
    unsigned int t;  // Bit count temporary.

    // Do pd normal parallel bit count for pd 64-bit integer,
    // but store all intermediate steps.
    // pd = (slot & 0x5555...) + ((slot >> 1) & 0x5555...);
    pd = slot - ((slot >> 1) & ~0UL / 3);
    // b = (pd & 0x3333...) + ((pd >> 2) & 0x3333...);
    b = (pd & ~0UL / 5) + ((pd >> 2) & ~0UL / 5);
    // c = (b & 0x0f0f...) + ((b >> 4) & 0x0f0f...);
    c = (b + (b >> 4)) & ~0UL / 0x11;
    // d = (c & 0x00ff...) + ((c >> 8) & 0x00ff...);
    d = (c + (c >> 8)) & ~0UL / 0x101;
    t = (d >> 32) + (d >> 48);
    // Now do branchless select!
    s = 64;
    // if (rank > t) {s -= 32; rank -= t;}
    s -= ((t - rank) & 256) >> 3;
    rank -= (t & ((t - rank) >> 8));
    t = (d >> (s - 16)) & 0xff;
    // if (rank > t) {s -= 16; rank -= t;}
    s -= ((t - rank) & 256) >> 4;
    rank -= (t & ((t - rank) >> 8));
    t = (c >> (s - 8)) & 0xf;
    // if (rank > t) {s -= 8; rank -= t;}
    s -= ((t - rank) & 256) >> 5;
    rank -= (t & ((t - rank) >> 8));
    t = (b >> (s - 4)) & 0x7;
    // if (rank > t) {s -= 4; rank -= t;}
    s -= ((t - rank) & 256) >> 6;
    rank -= (t & ((t - rank) >> 8));
    t = (pd >> (s - 2)) & 0x3;
    // if (rank > t) {s -= 2; rank -= t;}
    s -= ((t - rank) & 256) >> 7;
    rank -= (t & ((t - rank) >> 8));
    t = (slot >> (s - 1)) & 0x1;
    // if (rank > t) s--;
    s -= ((t - rank) & 256) >> 8;
    //current res between [0,63]
    return 64 - s;
}
*/


/*

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
*/

#endif //FILTER_PD_CC_PD_HPP
