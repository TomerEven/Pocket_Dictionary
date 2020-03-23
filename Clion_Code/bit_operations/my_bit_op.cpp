//
// Created by tomer on 3/15/20.
//

//#include "Naive_Counter_Endec.hpp"
#include "my_bit_op.hpp"

template<typename T>
auto compute_diff_value_safe(T x, T y) -> int {
    if ((x == 0) or (y == 0)) {
        if (x == y) return 0;
        return (x) ? __builtin_clz(x) : -__builtin_clz(y);
    }
}

template<typename T>
auto get_numbers_bit_length_difference(const T x, const T y) -> int {
/*
//    if ((x == 0) or (y == 0)){
//        if (x == y) return 0;
//        return (x) ? __builtin_clz(x) : -__builtin_clz(y);
//    }

    auto res2 = 1u;
    if ((x == 0) or (y == 0)) {
        if (x == y) res2 = 0;
        else
            res2 = (x) ? __builtin_clz(x) : -__builtin_clz(y);
    }

    uint32_t old_res = (__builtin_clz(x)) - (__builtin_clz(y));
    uint32_t old_res2 = (__builtin_clz(x)) - (__builtin_clz(y));
    uint32_t old_res3 = (__builtin_clz(x)) - (__builtin_clz(y));
*/
    //For validation.
//    auto x_clz = __builtin_clz(x);
//    auto y_clz = __builtin_clz(y);
//    auto res = x_clz - y_clz;
    int x_temp = (x == 0) ? 0 : floor(log2(x));
    int y_temp = (y == 0) ? 0 : floor(log2(y));
    return y_temp - x_temp;
//    auto exp_res = y_temp - x_temp;
//    assert(exp_res == res);
//    return res;
//    assert (((x != 0) and (y != 0)) or (x == y)); pass
//    assert (((x != 0) and (y != 0))); pass

    /*Explanation: (32 - y) - (32 - x) == floor(l2(x)) - floor(l2(y)) */
//    return __builtin_clz(x) - __builtin_clz(y);
}

template<typename T>
auto get_x_bit_length(const T x) -> size_t {
    if (x == 0)
        return 0;
    auto T_size = sizeof(x) * CHAR_BIT;
    auto res = T_size - __builtin_clz(x);
    assert(x <= (MASK(res)));

    if (res > 1)
        assert(x > (MASK(res - 1u)));
    return res;
}


template<typename T>
void find_kth_interval_simple(T *a, size_t a_size, size_t k, size_t *start, size_t *end) {
    if (k == 0) {
        *start = 0;
        *end = find_first_set_bit<T>(a, a_size);
        if (DB) cout << "h1" << endl;
        return;
    }

    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    for (int i = 0; i < a_size; ++i) {
        if (k == 1) {
            find_first_and_second_set_bits(&a[i], a_size - i, start, end);
            *start += (i) * slot_size;
            *end += (i) * slot_size;
            cout << "h2" << endl;
            return;
        }

        auto temp_counter = __builtin_popcount(a[i]);
        if (temp_counter == k) {
            *start = ((i + 1) * slot_size) - __builtin_ctz(a[i]);
            *end = find_first_set_bit(&a[i + 1], a_size - (i + 1)) + slot_size * (i + 1);
            cout << "h3" << endl;
            return;
        }
        if (temp_counter > k) {
            uint shift = select_r(a[i], k) - 32 + 1;
            *end = (i * slot_size) + shift + __builtin_clz(a[i] << (shift));
            *start = (i * slot_size) + shift;
            if (DB) cout << "h5" << endl;
            return;
/*
            return;
            T slot = a[i];
            T counter = 0;
            for (int j = 0; j < k; ++j) {
                auto shift = __builtin_clz(slot) + 1;
                assert(0 < shift < slot_size);
                slot <<= shift;
                assert(slot > 0);
                counter += (shift - 1);
            }
            *start = (i * slot_size) + (slot_size - (counter - 1) - 1);
            *end = (i * slot_size) + (slot_size - (counter + __builtin_ctz(slot)) - 1);
            if (DB) cout << "h5" << endl;
            return;
*/
        }
        k -= temp_counter;
        /*else if (temp_counter == k) {
            *start = (i * slot_size) + (slot_size - __builtin_ctz(a[i]) - 1);
            *end = find_first_set_bit<T>(&(a[i + 1]), a_size - (i + 1)) + slot_size * (i + 1);
            if (DB) cout << "h4: " << temp_counter << endl;
            return;*/
    }
    assert(false);
}

void word_k_select(uint32_t word, size_t k, size_t *start, size_t *end) {

}

template<typename T>
auto find_first_set_bit(T *a, size_t a_size) -> size_t {
    uint i = 0;
    while (a[i] == 0) i++;
    auto bit = __builtin_clz(a[i]);
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    return i * slot_size + bit;
}

template<typename T>
void find_first_and_second_set_bits(T *a, size_t a_size, size_t *first, size_t *second) {
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    uint i = 0;
    while (a[i] == 0) i++;
    auto bit = __builtin_clz(a[i]);
    T slot = a[i] << (bit + 1);
    if (slot) {
        auto length = __builtin_clz(slot);
        *first = i * slot_size + bit + 1;
        *second = i * slot_size + bit + 1 + length;
//        if (DB) cout << "h1" << endl;
        return;
    }
    *first = i * slot_size + bit + 1;
    while (a[++i] == 0);
    bit = __builtin_clz(a[i]);
    *second = i * slot_size + bit;
//    if (DB) cout << "h2" << endl;
}

template<typename T>
void update_element_att(T *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end, T new_val,
                        size_t a_size) {
    if (prev_start != new_start) {
        cout << "update_element_att" << endl;
        cout << "weird: prev_start != new_start" << endl;
    }
    size_t prev_val_length = prev_end - prev_start;
    size_t new_val_length = new_end - new_start;
    int new_length_minus_prev = new_val_length - prev_val_length;

    auto prev_val = extract_symbol<T>(a, a_size, prev_start, prev_end);

    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    auto start_index = prev_start / slot_size;
//    auto end_index = prev_end / slot_size;
//    auto new_end_index = new_end / slot_size;
    size_t shift = new_length_minus_prev;


    /*const size_t n = 6;
    string var_names[n] = {"prev_val", "new_val", "new_length_minus_prev", "new_val_length", "bit_start_pos",
                           "bit_end_pos"};
    size_t values[n] = {prev_val, new_val, size_t(new_length_minus_prev), new_val_length, prev_start, prev_end};


    */

    const size_t column_num = 3;
    const size_t var_count = 3;
    string columns[column_num] = {"total", "index", "bit_rem"};
    string var_names_c[var_count] = {"start", "prev_end", "new_end"};


    assert(start_index + 1 < a_size);
    size_t values_c[column_num * var_count] =
            {prev_start, prev_start / slot_size, prev_start % slot_size,
             prev_end, prev_end / slot_size, prev_end % slot_size,
             new_end, new_end / slot_size, new_end % slot_size};

    cout << string(32, '*') + "\tupdate_element_att call\t" + string(32, '*') << endl;
    table_print_columns(var_count, column_num, var_names_c, columns, values_c);

    const size_t num = 8;
    string var_names[num] = {"prev_val", "new_val",
                             "prev_val_length", "new_val_length",
                             "abs_length_diff", "shift",
                             "a[start_index]", "a[start_index + 1]"};

    size_t values[num] = {prev_val, new_val,
                          prev_val_length, new_val_length,
                          size_t(abs(new_length_minus_prev)), shift,
                          a[start_index], a[start_index + 1]};
    table_print(num, var_names, values);


    if (prev_val_length == new_val_length) {
        update_element_with_fixed_size<T>(a, prev_start, prev_end, new_val, a_size);
        cout << "H-1" << endl;
        return;
    }
    if (prev_val_length < new_val_length) {
        update_element_push_att(a, prev_start, prev_end, new_start, new_end, new_val, a_size);
    } else if (prev_val_length > new_val_length)
        update_element_pull_att(a, prev_start, prev_end, new_start, new_end, new_val, a_size);
    else {
        assert(false);
    }
}

template<typename T>
void update_element_push_att(T *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end, T new_val,
                             size_t a_size) {

    assert(prev_start == new_start); // I might be assuming this is true in the loop used for shifting.
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    size_t prev_val_length = prev_end - prev_start;
    size_t new_val_length = new_end - new_start;
    int new_length_minus_prev = new_val_length - prev_val_length;

    auto prev_val = extract_symbol<T>(a, a_size, prev_start, prev_end);
    assert(prev_val_length < new_val_length);

    auto start_index = prev_start / slot_size;
    auto new_start_index = new_start / slot_size;
    auto new_end_pos = prev_start + new_val_length;
//    auto prev_end_pos = prev_start + new_val_length;
    auto new_end_index = new_end / slot_size;
    auto prev_end_index = new_end / slot_size;
    size_t shift = new_length_minus_prev;

    bool case1 = (start_index < prev_end_index) and (prev_end_index == new_end_index);
    bool case2 = (start_index == prev_end_index) and (prev_end_index < new_end_index);
    bool case3 = (start_index == prev_end_index) and (prev_end_index == new_end_index);
    bool case4 = (new_end % slot_size) + shift > slot_size;
    assert(case1 or case2 or case3 or case4);
    assert(case1 or case2 or case3);


    assert((0 < shift) && (shift < slot_size));
    //Todo: validate loop.
    for (auto i = a_size - 1; i > new_start_index; --i) {
        a[i] = (a[i] >> shift) | (a[i - 1] << (slot_size - shift));
        assert(a[i] <= MASK(slot_size));
    }
    if (case1) {
        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        cout << case1 << ", " << case4 << endl;
        cout << "H0" << endl;
        return;
    }
        // (new_end_index % slot_size == 0) --> (start_index < new_end_index)
    else if (start_index < new_end_index) {
//        a[new_end_index] >>= shift;

        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        cout << "H1" << endl;
        return;
    } else if (case3) {
        auto pre_edit_val = a[start_index];
        auto left_mask = slot_size - (prev_start % slot_size);
        auto right_mask = slot_size - (prev_end % slot_size);
        auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
        auto right = (right_mask) ? a[start_index] & (MASK(right_mask)) : 0;
//        auto res = left | right;
        auto res = left | (right >> shift);
        assert(a[start_index] == left | right);
        a[start_index] = left | (right >> shift);


        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        cout << "H2" << endl;
        return;
    } else {
        assert(false);
    }

}

template<typename T>
void update_element_pull_att(T *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end, T new_val,
                             size_t a_size) {

    T unchanged_a[a_size];
    for (int i = 0; i < a_size; ++i) { unchanged_a[i] = a[i]; }

    assert(prev_start == new_start);
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    size_t prev_val_length = prev_end - prev_start;
//    size_t new_val_length = get_x_bit_length<T>(new_val);
    size_t new_val_length = new_end - new_start;
    int new_length_minus_prev = prev_val_length - new_val_length;

    auto prev_val = extract_symbol<T>(a, a_size, prev_start, prev_end);
    assert(prev_val_length > new_val_length);

    auto start_index = prev_start / slot_size;
    auto end_index = prev_end / slot_size;
    auto new_end_pos = prev_start + new_val_length;
    auto new_end_index = new_end_pos / slot_size;
    size_t shift = new_length_minus_prev;

    /*const size_t num = 16;
    string var_names[num] = {"prev_start", "start_array_index", "start_bit_rem",
                             "prev_end", "end_array_index", "end_bit_rem",
                             "new_end", "new_end_array_index", "new_end_bit_rem",
                             "prev_val", "new_val", "prev_val_length", "new_val_length", "abs_length_diff", "shift",
                             "temp_Heir"};
    assert(start_index + 1 < a_size);
    size_t values[num] = {prev_start, prev_start / slot_size, prev_start % slot_size,
                          prev_end, prev_end / slot_size, prev_end % slot_size,
                          new_end_pos, new_end_pos / slot_size, new_end_pos % slot_size,
                          prev_val, new_val, prev_val_length, new_val_length, size_t(abs(new_length_minus_prev)),
                          shift, a[start_index + 1]};

    cout << string(32, '*') + "\tupdate_element_pull call\t" + string(32, '*') << endl;
    table_print(num, var_names, values);
*/

    assert(prev_start <= prev_end);

    assert(start_index <= new_end_index);
    assert(new_end_index <= end_index);
    assert(end_index <= start_index + 1);

    bool case1 = (start_index < new_end_index) and (new_end_index == end_index);
    bool case2 = (start_index == new_end_index) and (new_end_index < end_index);
    bool case3 = (start_index == new_end_index) and (new_end_index == end_index);
//    bool case4 = (prev_end % slot_size) + shift > slot_size;
//    assert(case1 or case2 or case3 or case4);
    assert(case1 or case2 or case3);

    if (case1) {
        for (auto i = new_end_index; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        /*
        cout << "prev_end: " << prev_end << endl;
        cout << "new_end_pos: " << new_end_pos << endl;
        cout << "length: " << new_end_pos - prev_start << endl;
        */
        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        cout << "H3" << endl;
        return;
    } else if (case2) {
        assert(end_index <= start_index + 1);
        const auto temp = a[end_index];

        for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        auto num_of_bits_need_to_extract = slot_size - (new_end % slot_size);
        auto max_num_of_bits_that_can_be_extracted = slot_size - (prev_end % slot_size);
        bool is_mid_necessary = num_of_bits_need_to_extract > shift;
        assert(!is_mid_necessary);
        assert(num_of_bits_need_to_extract != 0);
        auto correct_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + num_of_bits_need_to_extract);

        auto prev_end_rem = prev_end % slot_size;
        auto left_mask = slot_size - (prev_start % slot_size);
        auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
        auto right_shift = (slot_size - num_of_bits_need_to_extract);
        T right2 = (temp << prev_end_rem) >> right_shift;
        assert(right2 == right2 & MASK(num_of_bits_need_to_extract));
        assert(right2 == correct_right);
        a[start_index] = left | right2;

        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        auto after = a[start_index];
        cout << "H11" << endl;
        return;

        /*
        auto right_length = slot_size - (new_end_pos % slot_size);
        auto bits_left_in_slot = slot_size - (new_end_pos % slot_size);
        bool is_mid_necessary = (shift < bits_left_in_slot);
        if (is_mid_necessary) {
            auto left_mask = slot_size - (prev_start % slot_size);
            auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
            auto bits_from_next_slot = prev_end % slot_size;
            auto mid_length = slot_size - (new_end_pos % slot_size) - bits_from_next_slot;
            auto mid = (a[start_index] & MASK(mid_length)) << bits_from_next_slot;
            auto right = temp >> (slot_size - bits_from_next_slot);
            auto mid_res = left | mid | right;
            a[start_index] = left | mid | right;

            update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
            auto after = a[start_index];
            cout << "H11" << endl;
            return;
*/

        /*
//        } else {
//            auto left_mask = slot_size - (prev_start % slot_size);
//            auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
//            auto right = (temp >> (slot_size - right_length)) & MASK(right_length);
//            auto right2 = (temp >> (slot_size - right_length));
//            auto mid_res = left | right;
//            a[start_index] = left | right;
//            update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
//            auto after = a[start_index];
//            cout << "H22" << endl;
//            return;
//        }
*/

    } /*else if (case4) {

        cout << "case4" << endl;
        update_element_pull_att_helper<T>(a, prev_start, prev_end, new_start, new_end, new_val, a_size);
        return;

    } */
    else if (case3) {
        assert((start_index == new_end_index) and (new_end_index == end_index));
        auto num_of_bits_need_to_extract = slot_size - (new_end % slot_size);
        auto res = 0;

        if (num_of_bits_need_to_extract + (prev_end % slot_size) > slot_size) {
            cout << "cond is true" << endl;
            auto bits_to_take_from_slot_plus2 = num_of_bits_need_to_extract + (prev_end % slot_size) - slot_size;
            assert(start_index + 2 < a_size);
            res |= (a[start_index + 2]) >> (slot_size - bits_to_take_from_slot_plus2);
            assert(res == (res & MASK(num_of_bits_need_to_extract)));
        }

        const auto temp = a[start_index + 1];
        for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        assert(num_of_bits_need_to_extract != 0);
        auto correct_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + num_of_bits_need_to_extract);
        auto prev_end_rem = prev_end % slot_size;

        /*auto maybe_new_val = (new_val == 0) or (new_val == 1) or (new_val == 3855);
        bool pos_cond = (prev_start == 0) and (prev_end == 12);
        auto break_point_cond = maybe_new_val and pos_cond and a[1];
        */

        auto bit_start_rem = prev_start % slot_size;
        auto bit_end_rem = new_end_pos % slot_size;
        auto l_power = slot_size - (bit_start_rem);
        auto left = (l_power) ? a[start_index] & (~MASK(l_power)) : 0;

        auto right_shift = (slot_size - num_of_bits_need_to_extract);
        T right2 = ((temp << prev_end_rem) >> right_shift) | res;
        assert(right2 == (right2 & MASK(num_of_bits_need_to_extract)));
        assert(right2 == correct_right);

        //todo continue from here. (comment is better?).
        T mid = (a[start_index] & (MASK(slot_size - (prev_end % slot_size)))) << shift;
//        T mid = (a[start_index] & (MASK(prev_end % slot_size))) << shift;

        bool is_mid_necessary = num_of_bits_need_to_extract > shift;
        assert(is_mid_necessary);

        T see_res = left | mid | right2;
        auto b_res = a[start_index];
        a[start_index] = left | mid | right2;
        /*
//        T mid2 = (a[start_index] & (MASK(bit_end_rem))) << shift;
//        T mid3 = (a[start_index] & (MASK(new_end % slot_size))) << shift;
//        auto mid_big2 = (a[start_index] & (MASK(new_end_pos % slot_size))) << shift;
//        auto cond = (mid2 == mid_big2) && (mid2);
//        T see_res2 = left | mid2 | right;
//        T see_res3 = left | mid3 | right;
//        cout << see_res2 << endl;
//        cout << see_res3 << endl;
//            auto right = temp >> (slot_size - shift);
//            auto right3 = temp >> (slot_size - shift - 1);
//            auto right2 = temp >> (shift);
//            a[start_index] = left | right;
        */
        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        auto after = a[start_index];
        cout << "H6" << endl;
        return;

    } else
        assert(false);

/*

    //todo 1) In h5, h4.5: Fix mid (use one).
    //todo 2) Fix this assertion, by dividing into cases.
    assert(new_end_index == end_index);
    const auto temp = a[start_index + 1];
    const auto temp2 = a[end_index];

    for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
        a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
    }
    a[a_size - 1] <<= shift;

    if (start_index == end_index) {
        auto maybe_new_val = (new_val == 0) or (new_val == 1) or (new_val == 3855);
        bool pos_cond = (prev_start == 0) and (prev_end == 12);
        auto break_point_cond = maybe_new_val and pos_cond and a[1];

        auto bit_start_rem = prev_start % slot_size;
        auto bit_end_rem = new_end_pos % slot_size;
        auto l_power = slot_size - (bit_start_rem);
        auto left = (l_power) ? a[start_index] & (~MASK(l_power)) : 0;
        auto right = temp >> (slot_size - shift);
        T mid = (a[start_index] & (MASK(prev_end % slot_size))) << shift;
        T mid2 = (a[start_index] & (MASK(bit_end_rem))) << shift;
        T mid3 = (a[start_index] & (MASK(new_end % slot_size))) << shift;
        auto mid_big2 = (a[start_index] & (MASK(new_end_pos % slot_size))) << shift;
        auto cond = (mid2 == mid_big2) && (mid2);
        T see_res = left | mid | right;
        T see_res2 = left | mid2 | right;
        T see_res3 = left | mid3 | right;
        cout << see_res << endl;
        cout << see_res2 << endl;
        cout << see_res3 << endl;
        a[start_index] = left | mid | right;
//            auto right = temp >> (slot_size - shift);
//            auto right3 = temp >> (slot_size - shift - 1);
//            auto right2 = temp >> (shift);
//            a[start_index] = left | right;

        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        auto after = a[start_index];
        a[start_index];
        cout << "H4" << endl;
        return;

    } else if (start_index < end_index) {
        if (prev_end % slot_size == 0) {
            auto maybe_new_val = (new_val == 0) or (new_val == 1) or (new_val == 493440);
            bool pos_cond = (prev_start == 13) and ((prev_end == 13) or (prev_end == 32));
            auto break_point_cond = maybe_new_val and pos_cond and a[1];
//                auto break_point_cond = (new_val == 1) and (prev_start == 13);

            auto left_mask = slot_size - (prev_start % slot_size);
            auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
            //todo check the shifting.
            auto right = temp2 >> (slot_size - shift);
            auto before = left | right;
            a[start_index] = left | right;
            update_element_with_fixed_size<T>(a, prev_start, new_end_pos, new_val, a_size);
            cout << "H4.5" << endl;
            auto after = a[start_index];
            return;
        }
        //todo clean-up
        auto break_point_cond = (new_val == 1) and (prev_start == 13);
        auto left_mask = slot_size - (prev_start % slot_size);
        auto mid_mask = prev_end % slot_size;
        auto new_mid_mask = new_end_pos % slot_size;
        auto bit_end_rem = new_end_pos % slot_size;
        auto right_mask = slot_size - bit_end_rem;
        auto right_shift = slot_size - shift;
        auto bits_to_leave = slot_size - (new_end_pos % slot_size);
        cout << "before a[start_index]: " << a[start_index] << endl;

        assert(new_end_index < end_index);
        auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
        auto mid = (a[start_index] & (MASK(prev_end % slot_size))) << shift;
        auto right = temp & MASK(right_mask);
        auto check = temp & MASK(right_mask);
//            right >>= (slot_size - bit_end_rem) - bits_to_leave;
        check >>= (slot_size - bit_end_rem) - shift;
//            assert(right == check);
        auto r1 = left | right;
//            auto r2 = check | right;
        a[start_index] = left | right;
//            a[start_index] = left | mid | right;


        update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
        cout << "H5" << endl;
        return;
    }

*/

}

template<typename T>
void
update_element_pull_att_helper(T *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end, T new_val,
                               size_t a_size) {
    T unchanged_a[a_size];
    for (int i = 0; i < a_size; ++i) { unchanged_a[i] = a[i]; }

    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    size_t prev_val_length = prev_end - prev_start;
    size_t new_val_length = new_end - new_start;
    int new_length_minus_prev = prev_val_length - new_val_length;

    auto prev_val = extract_symbol<T>(a, a_size, prev_start, prev_end);

    auto start_index = prev_start / slot_size;
    auto end_index = prev_end / slot_size;
    auto new_end_pos = prev_start + new_val_length;
    auto new_end_index = new_end_pos / slot_size;
    size_t shift = new_length_minus_prev;
/*
    ////
    const auto temp = a[end_index];
    for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
        a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
    }
    a[a_size - 1] <<= shift;

    auto bits_to_extract = slot_size - (new_end % slot_size);
    assert(bits_to_extract != 0);
    auto correct_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + bits_to_extract);


    auto prev_end_rem = prev_end % slot_size;
    auto bits_left_in_next_slot = slot_size - (prev_end % slot_size);
//        assert(shift <= bits_left_in_next_slot);
    auto left_mask = slot_size - (prev_start % slot_size);
    auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
    auto right_shift = (slot_size - bits_to_extract);
    T right2 = (temp << prev_end_rem) >> right_shift;
    assert(right2 == right2 & MASK(bits_to_extract));
    auto right_shift_att = (slot_size - bits_to_extract) - (prev_end_rem);
    assert(right_shift_att > 0);
//        auto right_r_shift = (slot_size - bits_to_extract);
//        T right = (temp << bits_to_extract) >> right_shift;
//        T right3 = (temp & MASK(bits_left_in_next_slot)) >> right_shift;

    assert(right_shift - bits_to_extract > 0);
//        auto right_validation = (temp & (MASK(slot_size - prev_end_rem))) >> (right_shift - bits_to_extract);
    assert(right2 == correct_right);
    a[start_index] = left | right2;

    update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
    auto after = a[start_index];
    cout << "H5" << endl;
    return;
    ////
*/


    const auto temp = a[start_index + 1];
    assert(start_index + 2 < a_size);
    const auto temp_next = a[start_index + 2];

    for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
        a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
    }
    a[a_size - 1] <<= shift;
/*

    auto bits_to_extract = slot_size - (new_end % slot_size);
    bool is_mid_necessary = (slot_size - (new_end % slot_size)) > shift;
    assert(!is_mid_necessary);

    auto correct_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + bits_to_extract);
    auto prev_end_rem = prev_end % slot_size;

    auto bit_start_rem = prev_start % slot_size;
    auto bit_end_rem = new_end_pos % slot_size;
    auto l_power = slot_size - (bit_start_rem);
    auto left = (l_power) ? a[start_index] & (~MASK(l_power)) : 0;

    auto right_shift = (slot_size - bits_to_extract);
    T right2 = (temp << prev_end_rem) >> right_shift;
    assert(right2 == right2 & MASK(bits_to_extract));
    assert(right2 == correct_right);

    T mid = (a[start_index] & (MASK(prev_end % slot_size))) << shift;
    T see_res = left | mid | right2;
    auto b_res = a[start_index];
    a[start_index] = left | mid | right2;
    */
/*
//        T mid2 = (a[start_index] & (MASK(bit_end_rem))) << shift;
//        T mid3 = (a[start_index] & (MASK(new_end % slot_size))) << shift;
//        auto mid_big2 = (a[start_index] & (MASK(new_end_pos % slot_size))) << shift;
//        auto cond = (mid2 == mid_big2) && (mid2);
//        T see_res2 = left | mid2 | right;
//        T see_res3 = left | mid3 | right;
//        cout << see_res2 << endl;
//        cout << see_res3 << endl;
//            auto right = temp >> (slot_size - shift);
//            auto right3 = temp >> (slot_size - shift - 1);
//            auto right2 = temp >> (shift);
//            a[start_index] = left | right;
    *//*

    update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
    auto after = a[start_index];
    cout << "H555" << endl;
    return;

*/

    /*if (prev_end % slot_size == 0){
        auto maybe_new_val = (new_val == 0) or (new_val == 1) or (new_val == 493440);
        bool pos_cond = (prev_start == 13) and ((prev_end == 13) or (prev_end == 32));
        auto break_point_cond = maybe_new_val and pos_cond and a[1];
//                auto break_point_cond = (new_val == 1) and (prev_start == 13);

        auto left_mask = slot_size - (prev_start % slot_size);
        auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
        //todo check the shifting.
        auto right = temp2 >> (slot_size - shift);
        auto before = left | right;
        a[start_index] = left | right;
        update_element_with_fixed_size<T>(a, prev_start, new_end_pos, new_val, a_size);
        cout << "H4.5" << endl;
        auto after = a[start_index];
        return;
    }
    */
    auto b_res = a[start_index];
    //todo clean-up
    auto break_point_cond = (new_val == 1) and (prev_start == 13);
    auto right_shift = slot_size - shift;
    auto prev_end_rem = prev_end % slot_size;
    /*
//        auto mid_mask = prev_end % slot_size;
//        auto new_mid_mask = new_end_pos % slot_size;
//        auto bit_end_rem = new_end_pos % slot_size;
//        auto right_mask = slot_size - bit_end_rem;
//        auto bits_to_leave = slot_size - (new_end_pos % slot_size);
//        cout << "before a[start_index]: " << a[start_index] << endl;
    */

    auto left_mask = slot_size - (prev_start % slot_size);
    auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
    auto new_end_rem = new_end_pos % slot_size;
    auto right_length = slot_size - (new_end_pos % slot_size);
    auto right = (temp >> (slot_size - right_length)) & MASK(right_length);
    auto mid_res = left | right;
    a[start_index] = left | right;
    update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
    auto after = left | right;
    cout << "H5" << endl;
/*

    //"right" should also take some bits from the a[index + 2]
    if (prev_end_rem + right_length > slot_size) {
        assert (prev_end_rem + right_length <= 2 * slot_size); // shift plus values length is not too big.
        auto bits_to_take_from_first_slot = (slot_size - prev_end_rem);
        auto bits_to_take_from_second_slot = right_length - bits_to_take_from_first_slot;
        auto first_right = temp & MASK(bits_to_take_from_first_slot);
        auto first_right_naive = extract_symbol<T>(unchanged_a, a_size, prev_end,
                                                   prev_end + bits_to_take_from_first_slot);
        assert(first_right == first_right_naive);
        auto second_right =
                (temp_next >> (slot_size - bits_to_take_from_second_slot)) & MASK(bits_to_take_from_second_slot);
        auto second_right_naive = extract_symbol<T>(unchanged_a, a_size, prev_end + bits_to_take_from_first_slot,
                                                    prev_end + right_length);
        assert(second_right == second_right_naive);

        right = (first_right << bits_to_take_from_second_slot) | second_right;
        unsigned long w = (first_right << bits_to_take_from_second_slot) | second_right;
        assert(w == right);
        auto naive_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + shift);
        assert(naive_right == right);
        cout << "H4.5" << endl;
    } else {
        right = (temp >> right_shift) & MASK(shift);
        auto naive_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + shift);
        assert(naive_right == right);
    }
*/


//        auto right_attempt = extract_symbol<T>(a, a_size, prev_end, prev_end + shift);
    /*
//        auto right_a = (temp & (~MASK())) >> right_shift;
//        auto mid = (a[start_index] & (MASK(prev_end % slot_size))) << shift;
//        auto right = temp & MASK(right_mask);
//        auto check = temp & MASK(right_mask);
    check >>= (slot_size - bit_end_rem) - shift;
//            assert(right == check);
    auto r1 = left | right;
//            auto r2 = check | right;
*/
//    a[start_index] = left | right;


//    update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
//    auto after = left | right;
//    cout << "H5" << endl;

}


template<typename T>
void update_element(T *a, size_t bit_start_pos, size_t bit_end_pos, T new_val, size_t a_size) {

    auto prev_val = extract_symbol<T>(a, a_size, bit_start_pos, bit_end_pos);
//    int bit_length_difference = get_numbers_bit_length_difference<T>(prev_val, new_val);
    size_t prev_val_length = bit_end_pos - bit_start_pos;
    size_t new_val_length = get_x_bit_length<T>(new_val);
    int new_length_minus_prev = new_val_length - prev_val_length;

    const size_t n = 6;
    string var_names[n] = {"prev_val", "new_val", "new_length_minus_prev", "new_val_length", "bit_start_pos",
                           "bit_end_pos"};
    size_t values[n] = {prev_val, new_val, size_t(new_length_minus_prev), new_val_length, bit_start_pos, bit_end_pos};

    table_print(n, var_names, values);


    if (new_val_length == prev_val_length) {
        update_element_with_fixed_size<T>(a, bit_start_pos, bit_end_pos, new_val, a_size);
        cout << "H0" << endl;
        return;
    }
    if (new_val_length > prev_val_length) {
        update_element_push(a, bit_start_pos, bit_end_pos, new_val, a_size);
    } else if (new_val_length < prev_val_length)
        update_element_pull(a, bit_start_pos, bit_end_pos, new_val, a_size);
}

template<typename T>
void update_element_push(T *a, size_t bit_start_pos, size_t bit_end_pos, T new_val, size_t a_size) {
    /*   auto prev_val = extract_symbol<T>(a, a_size, bit_start_pos, bit_end_pos);
       int bit_length_difference = get_numbers_bit_length_difference<T>(prev_val, new_val);
       size_t new_val_length = get_x_bit_length<T>(new_val);

       const size_t n = 6;
       string var_names[n] = {"prev_val", "new_val", "bit_length_difference", "new_val_length", "bit_start_pos",
                              "bit_end_pos"};
       size_t values[n] = {prev_val, new_val, size_t(bit_length_difference), new_val_length, bit_start_pos, bit_end_pos};

       table_print(n, var_names, values);


       if (bit_length_difference == 0) {
           update_element_with_fixed_size<T>(a, bit_start_pos, bit_end_pos, new_val, a_size);
           cout << "H0" << endl;
           return;
       }

       auto slot_size = sizeof(a[0]) * CHAR_BIT;
       auto start_index = bit_start_pos / slot_size;
       auto end_index = bit_end_pos / slot_size;
       auto new_end_pos = bit_start_pos + new_val_length;
       auto new_end_index = new_end_pos / slot_size;
   */
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    size_t prev_val_length = bit_end_pos - bit_start_pos;
    size_t new_val_length = get_x_bit_length<T>(new_val);
    int new_length_minus_prev = new_val_length - prev_val_length;

    auto prev_val = extract_symbol<T>(a, a_size, bit_start_pos, bit_end_pos);
//    auto bit_length_difference = get_numbers_bit_length_difference<T>(prev_val, new_val);
//    assert(bit_length_difference == get_numbers_bit_length_difference<T>(prev_val, new_val));
    assert(prev_val_length < new_val_length);

    auto start_index = bit_start_pos / slot_size;
    auto new_end_pos = bit_start_pos + new_val_length;
    auto new_end_index = new_end_pos / slot_size;
    /*todo
    size_t shift = bit_end_pos - bit_start_pos;
    assert(bit_end_pos > bit_start_pos);*/
    size_t shift = new_length_minus_prev;


    assert((0 < shift) && (shift < slot_size));
    for (auto i = a_size - 1; i > new_end_index; --i) {
        a[i] = (a[i] >> shift) | (a[i - 1] << (slot_size - shift));
        assert(a[i] <= MASK(slot_size));
    }
    // (new_end_index % slot_size == 0) --> (start_index < new_end_index)
    if (start_index < new_end_index) {
        a[new_end_index] >>= shift;

        update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
        cout << "H1" << endl;
        return;
    } else {
        auto left_mask = bit_start_pos % slot_size;
        auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
        auto right = a[start_index] & (MASK(bit_end_pos % slot_size));
        assert(a[start_index] == left | right);
        a[start_index] = left | (right >> shift);


        update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
        cout << "H2" << endl;
        return;
    }

}

template<typename T>
void update_element_pull(T *a, size_t bit_start_pos, size_t bit_end_pos, T new_val, size_t a_size) {

    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    size_t prev_val_length = bit_end_pos - bit_start_pos;
    size_t new_val_length = get_x_bit_length<T>(new_val);
    int new_length_minus_prev = new_val_length - prev_val_length;

    auto prev_val = extract_symbol<T>(a, a_size, bit_start_pos, bit_end_pos);
    assert(prev_val_length > new_val_length);

    auto start_index = bit_start_pos / slot_size;
    auto end_index = bit_end_pos / slot_size;
    auto new_end_pos = bit_start_pos + new_val_length;
    auto new_end_index = new_end_pos / slot_size;
    size_t shift = -new_length_minus_prev;

    const size_t num = 16;

    string var_names[num] = {"bit_start_pos", "start_array_index", "start_bit_rem",
                             "bit_end_pos", "end_array_index", "end_bit_rem",
                             "new_end", "new_end_array_index", "new_end_bit_rem",
                             "prev_val", "new_val", "prev_val_length", "new_val_length", "abs_length_diff", "shift",
                             "temp_Heir"};
    assert(start_index + 1 < a_size);
    size_t values[num] = {bit_start_pos, bit_start_pos / slot_size, bit_start_pos % slot_size,
                          bit_end_pos, bit_end_pos / slot_size, bit_end_pos % slot_size,
                          new_end_pos, new_end_pos / slot_size, new_end_pos % slot_size,
                          prev_val, new_val, prev_val_length, new_val_length, size_t(abs(new_length_minus_prev)),
                          shift, a[start_index + 1]};

    cout << string(32, '*') + "\tupdate_element_pull call\t" + string(32, '*') << endl;
    table_print(num, var_names, values);


    assert(bit_end_pos >= bit_start_pos);

    if (start_index < new_end_index) {
        for (auto i = new_end_index; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        cout << "bit_end_pos: " << bit_end_pos << endl;
        cout << "new_end_pos: " << new_end_pos << endl;
//        cout << "bit_length_difference: " << bit_length_difference << endl;
        cout << "length: " << new_end_pos - bit_start_pos << endl;
        update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);

//        assert(false);
        cout << "H3" << endl;
        return;

    } else if (start_index == new_end_index) {

        const auto temp = a[start_index + 1];

        for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        if (start_index == end_index) {
            /*auto maybe_new_val = (new_val == 0) or (new_val == 1) or (new_val == 3855);
            bool pos_cond = (bit_start_pos == 0) and (bit_end_pos == 12);
            auto break_point_cond = maybe_new_val and pos_cond and a[1];
            */
            auto bit_start_rem = bit_start_pos % slot_size;
            auto bit_end_rem = new_end_pos % slot_size;
            auto l_power = slot_size - (bit_start_rem);
            auto left = (l_power) ? a[start_index] & (~MASK(l_power)) : 0;
            /*T mid = (a[start_index] & (MASK(bit_end_pos % slot_size))) << shift;
            T mid2 = (a[start_index] & (MASK(bit_end_rem))) << shift;
            auto mid_big2 = (a[start_index] & (MASK(new_end_pos % slot_size))) << shift;
            auto cond = (mid2 == mid_big2) && (mid2);
            T see_res = left | mid2 | right;
            a[start_index] = left | mid2 | right;*/
            auto right = temp >> (slot_size - shift);
            auto right2 = temp >> (shift);
            a[start_index] = left | right;


            update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
            a[start_index];
            cout << "H4" << endl;
            return;

        } else if (start_index < end_index) {
            if (bit_end_pos % slot_size == 0) {
                auto break_point_cond = (new_val == 1) and (bit_start_pos == 13);

                auto left_mask = slot_size - (bit_start_pos % slot_size);
                auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
                //todo check the shifting.
                auto right = temp >> (slot_size - shift);
                auto before = left | right;
                a[start_index] = left | right;
                update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
                cout << "H4.5" << endl;
                auto after = a[start_index];
                return;
//                auto check = temp >> (slot_size - (shift + 1));
//                assert()
            }
            //todo clean-up
            auto break_point_cond = (new_val == 1) and (bit_start_pos == 13);
            auto left_mask = slot_size - (bit_start_pos % slot_size);
            auto mid_mask = bit_end_pos % slot_size;
            auto new_mid_mask = new_end_pos % slot_size;
            auto bit_end_rem = new_end_pos % slot_size;
            auto right_mask = slot_size - bit_end_rem;
            auto right_shift = slot_size - shift;
            auto bits_to_leave = slot_size - (new_end_pos % slot_size);
            cout << "before a[start_index]: " << a[start_index] << endl;

            assert(new_end_index < end_index);
            auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
            auto mid = (a[start_index] & (MASK(bit_end_pos % slot_size))) << shift;
            auto right = temp & MASK(right_mask);
            auto check = temp & MASK(right_mask);
            right >>= (slot_size - bit_end_rem) - bits_to_leave;
            check >>= (slot_size - bit_end_rem) - shift;
//            auto right = (temp << bit_end_rem) >> right_shift;
//            auto right = ((temp & MASK(right_mask)) >> (right_shift - ));
//            assert(right == right & MASK(bits_to_leave));
//            auto right = (temp >> (right_shift)) & MASK(bits_to_leave);
            assert(right == check);
            auto r1 = left | right;
            auto r2 = check | right;
            a[start_index] = left | right;

            /*
//            auto so_see_res = left | mid | right;
//            auto no_mid = left | right;
//            auto new_mid = (a[start_index] & (MASK(new_mid_mask))) << shift;
//            a[start_index] = left | right;
//            auto att = left | new_mid | right;

            cout << "after a[start_index]: " << a[start_index] << endl;
            cout << "left: " << left << endl;
            cout << "mid: " << mid << endl;
//            cout << "new_mid: " << new_mid << endl;
            cout << "right: " << right << endl;


            cout << "left_mask: " << left_mask << endl;
            cout << "mid_mask: " << mid_mask << endl;
            cout << "new_mid_mask: " << new_mid_mask << endl;
            cout << "right_shift: " << right_shift << endl;

            cout << "\nbit_start_pos: " << bit_start_pos << "\tnormalized: " << bit_start_pos % slot_size << endl;
            cout << "bit_end_pos: " << bit_end_pos << "\tnormalized: " << bit_end_pos % slot_size << endl;
            cout << "new_end_pos: " << new_end_pos << "\tnormalized: " << new_end_pos % slot_size << endl;
            cout << "bit_length_difference: " << bit_length_difference << endl;
            cout << "length: " << new_end_pos - bit_start_pos << endl;

*/


            update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
            cout << "H5" << endl;
            return;
        }
    } else
        assert(false);

//    update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);

}

template<typename T>
void update_element_with_fixed_size(T *a, size_t bit_start_pos, size_t bit_end_pos, T new_val, size_t a_size) {
    if (bit_start_pos == bit_end_pos) {
        cout << "bit_start_pos == bit_end_pos" << endl;
        cout << "J0" << endl;
        return;
    }
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    assert(bit_start_pos + slot_size >= bit_end_pos);


    auto start_index = bit_start_pos / slot_size;
    auto end_index = bit_end_pos / slot_size;

    if (bit_end_pos % slot_size == 0) {
        auto length = bit_end_pos - bit_start_pos;
        assert((length > 0) and (length <= slot_size));
        a[start_index] = (a[start_index] & (~MASK(length))) | new_val;
        cout << "J1" << endl;
        return;
    }

    if (start_index == end_index) {
        auto length = bit_end_pos - bit_start_pos;
        assert(length > 0);
        assert(length <= slot_size);
        assert(new_val <= MASK(length + 1u));
        auto start_rem = bit_start_pos % slot_size;
        auto end_rem = bit_end_pos % slot_size;

        //Sanity? Or not?
        assert((slot_size - start_rem) > (slot_size - end_rem));

        auto first_shift = (slot_size - start_rem);
        auto second_shift = (slot_size - end_rem);
        auto left = a[start_index] & MASK(second_shift);
        uint32_t right = (((a[start_index] >> first_shift) << length) | new_val) << second_shift;
        a[start_index] = right | left;
        cout << "J2" << endl;
        return;


        /*
        temp >>= first_shift;
        temp <<= length;
        temp |= new_val;
        temp <<= (second_shift);
        temp |= left;

          //        uint32_t  temp3 = (((a[start_index] >> first_shift) & (~MASK(length))) | new_val) << second_shift;
                    uint32_t temp2 = ((((a[start_index] >> first_shift) << length) | new_val) << second_shift) | left;

        //Maybe: shift_second  + 1 ;
        uint32_t temp_mask = ~(MASK(first_shift) & MASK(second_shift));
        uint32_t temp4 = a[start_index] & (temp_mask) | (new_val << second_shift);

//        bool c2 = temp3 == temp2;
//        bool c1 = true, c2 = true;
        bool c1 = temp2 == temp;
        bool c2 = temp4 == temp2;

        if (!(c1 && c2)) {
            bool c_array[2] = {c1, c2};
            for (int i = 0; i < 2; ++i) { if (!c_array[i]) { cout << "c" << i+1 << " failed." << endl; }}
//            printf("%u\n%u\n%u\n%u\n", temp, temp2, temp3, temp4);
            printf("%u\n%u\n%u\n", temp, temp2, temp4);

        }
        assert(c1 || c2);
        a[start_index] = temp;
        cout << "H2" << endl;
        return;*/

    } else if (start_index + 1 == end_index) {

        auto length = bit_end_pos - bit_start_pos;
        assert(length > 0);
        assert(new_val <= MASK(length + 1));

//        auto start_rem = bit_start_pos % slot_size;
        auto end_rem = bit_end_pos % slot_size;

        auto left_shift = length - end_rem;
        auto left_val = (a[start_index] & (~MASK(left_shift))) | (new_val >> end_rem);

        auto right_shift = slot_size - end_rem;
        auto right_val = (a[end_index]) & (MASK(right_shift)) | (new_val << right_shift);

        a[start_index] = left_val;
        a[end_index] = right_val;
        cout << "J3" << endl;
        return;

    } else {
        cout << "J4" << endl;
        assert(false);
    }
}

auto count_set_bits(uint32_t *a, size_t a_size) -> size_t {
    size_t counter = 0;
    for (int i = 0; i < a_size; ++i) {
        counter += __builtin_popcount(a[i]);
    }
    return counter;
}


template<typename T>
auto extract_symbol(const T *A, size_t a_size, size_t bit_start_index, size_t bit_end_index) -> T {
    if (bit_start_index == bit_end_index) {
//        cout << "H0" << endl;
        return 0;
    }
    auto slot_size = sizeof(A[0]) * CHAR_BIT;
    auto bit_start_rem = bit_start_index % slot_size;
    auto bit_end_rem = bit_end_index % slot_size;
    size_t shift_power = slot_size - bit_start_rem;
    uint32_t mask = SL(shift_power) - 1u;
    uint32_t shift_left = slot_size - (bit_end_rem);

    if (bit_end_rem == 0) {
        size_t array_start_index = bit_start_index / slot_size;
        auto temp = A[array_start_index] & mask;
//        cout << "H1" << endl;
        return temp;
    }
    size_t array_start_index = bit_start_index / slot_size, array_end_index = bit_end_index / slot_size;

    if (array_start_index == array_end_index) {
        auto temp = A[array_start_index] & mask;
        assert(shift_left > 0);

//        cout << "H2" << endl;
        return temp >> shift_left;

    } else if (array_start_index + 1 == array_end_index) {
        auto i = array_start_index;
        assert(i + 1 == array_end_index);
        assert(i + 1 < a_size);

        // a[i] = (a[i] << fp_size) | (a[i + 1] >> (BODY_BLOCK_SIZE - fp_size));
//        cout << "H3" << endl;
        return ((A[i] & mask) << bit_end_rem) | (A[i + 1] >> shift_left);
    } else
        assert(false);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// vector functions.

auto vector_last_k_bits_are_zero(vector<bool> *vec, size_t k) -> bool {
    auto size = vec->size();
    for (auto i = size - k; i < size; ++i) {
        if (vec->at(i) != 0) {
            return false;
        }
    }
    return true;
}


template<typename T>
auto read_T_word(const vector<bool> *v, size_t start, size_t end) -> T {
    assert(start <= end);
    assert(end <= v->size());

    T res = 0;
    for (size_t i = start; i < end; ++i) {
        res <<= 1ul;
        res |= v->at(i);
    }
    return res;
}

template<typename T>
auto equality_vec_array(const vector<bool> *v, const T *a, size_t a_size, size_t bits_lim) -> int {
    auto slot_size = sizeof(a[0]) * CHAR_BIT;
    size_t size = min(v->size() / slot_size, a_size);
    size = min(size, bits_lim / slot_size);
    size_t step = slot_size;
    for (size_t i = 0; i < size; ++i) {
        if (a[i] != read_T_word<T>(v, i * step, (i + 1) * step)) {
//            print_array_as_consecutive_memory(&a[i],a_size - i);

            cout << "\n\n equality_vec_array error in index: " << i << endl;
            print_array_as_consecutive_memory(a, a_size);
            print_bool_vector_no_spaces(v);
            cout << "\n" << endl;

            return i;
        }
    }
    return -1;
}


template<typename T>
void from_array_to_vector(vector<bool> *vec, const T *a, size_t a_size) {
    size_t slot_size = (sizeof(a[0]) * CHAR_BIT);
    size_t vec_new_size = slot_size * a_size, vec_index = 0;
    vec->resize(vec_new_size);
    for (size_t i = 0; i < a_size; ++i) {
        size_t b = 1ULL << (slot_size - 1);
        for (size_t j = 0; j < slot_size; ++j) {
            vec->at(vec_index) = (b & a[i]);
            b >>= 1ULL;
            vec_index++;
        }
    }
}

template<typename T>
void from_vector_to_array(const vector<bool> *vec, T *a, size_t a_size) {
    size_t slot_size = (sizeof(a[0]) * CHAR_BIT);
    assert(a_size * slot_size >= vec->size());

    size_t expected_size = (vec->size() / slot_size) + (vec->size() % slot_size != 0);
    assert(a_size == expected_size);

    for (int i = 0; i < a_size; ++i) {
        size_t start = i * slot_size;
        size_t end = start + slot_size;
        a[i] = sub_vector_to_word<T>(vec, start, end);
    }
/*

    for (size_t i = 0; i < a_size - 1; ++i) {
        ulong b = (1ul << (slot_size - 1u));
        for (int j = 0; j < slot_size; ++j) {
            assert(b > 0);
            if (vec->at(slot_size * i + j)) {
                a[i] |= b;
            }
            b >>= 1ul;
        }
    }
    ulong b = (1ul << 31ul);
    for (size_t k = 0; k < vec->size() % slot_size; ++k) {
        if (vec->at(slot_size * (a_size - 1) + k)) {
            a[a_size - 1] |= b;
        }
        b >>= 1ul;
    }
*/
}


template<typename T>
auto sub_vector_to_word(const vector<bool> *v, size_t start, size_t end) -> T {
    T res = 0;
    for (int i = start; i < end; ++i) {
        res <<= 1u;
        res |= v->at(i);
    }
    return res;
}

void vector_find_kth_interval_simple(vector<bool> *vec, size_t k, size_t *start_index, size_t *end_index) {
    size_t set_bit_counter = 0, continue_from_index = 0;
    for (size_t i = 0; i < vec->size(); ++i) {
        if (set_bit_counter == k) {
            *start_index = i;
            continue_from_index = i;
            break;
        }
        if (vec->at(i))
            set_bit_counter++;
    }
    assert(*start_index < vec->size());

    for (size_t i = continue_from_index; i < vec->size(); ++i) {
        if (vec->at(i)) {
            *end_index = i;
            return;
        }
    }
    cout << "vector_find_kth_interval_simple: reached end of vector" << endl;
    assert(false);
}

auto vector_find_first_set_bit(vector<bool> *vec) -> size_t {
    for (int i = 0; i < vec->size(); ++i) { if (vec->at(i)) return i; }
    assert(false);
}

auto vector_extract_symbol(vector<bool> *vec, size_t *start_index, size_t *end_index) -> uint32_t {
//    return sub_vector_to_word<()
}

template<typename T>
void vector_update_element_with_fixed_size(vector<bool> *vec, size_t start, size_t end, T new_val) {
    assert(0 <= start);
    assert(start <= end);
    assert(end <= vec->size());
    auto length = end - start;
    size_t pos = end - 1;
    for (int j = 0; j < length; ++j) {
        vec->at(pos) = 1u & new_val;
        new_val >>= 1u;
        pos--;
    }
}

template<typename T>
void vector_update_element(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                           T new_val) {
    auto prev_length = prev_end - prev_start;
    auto new_length = new_end - new_start;

    if (prev_length == new_length) {
        assert(prev_start == new_start);
        vector_update_element_with_fixed_size<T>(vec, new_start, new_end, new_val);
//        cout << "S0" << endl;
        return;
    } else if (prev_length < new_length) {
//        cout << "S1" << endl;
        vector_update_push<T>(vec, prev_start, prev_end, new_start, new_end, new_val);
    } else {
//        cout << "S2" << endl;
        vector_update_pull<T>(vec, prev_start, prev_end, new_start, new_end, new_val);
    }


}

template<typename T>
void
vector_update_push(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end, T new_val) {
    auto prev_length = prev_end - prev_start;
    auto new_length = new_end - new_start;
    assert(prev_length < new_length);
    auto shift = new_length - prev_length;
    bool BRC = (new_val == 252645135);

    assert(vector_last_k_bits_are_zero(vec, shift));
    assert(shift <= new_end);
    for (auto i = vec->size() - 1; i >= new_end; --i) { vec->at(i) = vec->at(i - shift); }

    assert(new_start == prev_start);
    vector_update_element_with_fixed_size<T>(vec, new_start, new_end, new_val);

}

template<typename T>
void
vector_update_pull(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end, T new_val) {
    auto prev_length = prev_end - prev_start;
    auto new_length = new_end - new_start;
    assert(prev_length > new_length);

    auto shift = prev_length - new_length;

    for (auto i = new_end; i < (vec->size() - shift); ++i) { vec->at(i) = vec->at(i + shift); }

    assert(new_start == prev_start);
    vector_update_element_with_fixed_size<T>(vec, new_start, new_end, new_val);

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Templates definitions.



template auto get_numbers_bit_length_difference<uint32_t>(const uint32_t x, const uint32_t y) -> int;

template auto get_x_bit_length<uint32_t>(const uint32_t x) -> size_t;

template size_t find_first_set_bit<uint32_t>(uint32_t *a, size_t a_size);

template void find_kth_interval_simple<uint32_t>(uint32_t *a, size_t a_size, size_t k, size_t *start, size_t *end);

template void from_array_to_vector<uint32_t>(vector<bool> *vec, const uint32_t *a, size_t a_size);

template void from_vector_to_array<uint32_t>(const vector<bool> *vec, uint32_t *a, size_t a_size);

template uint32_t sub_vector_to_word<uint32_t>(const vector<bool> *v, size_t start, size_t end);

template void
update_element_with_fixed_size<uint32_t>(uint32_t *a, size_t bit_start_pos, size_t bit_end_pos,
                                         uint32_t new_val, size_t a_size);

template void
update_element<uint32_t>(uint32_t *a, size_t bit_start_pos, size_t bit_end_pos, uint32_t new_val, size_t a_size);

template void
update_element_att<uint32_t>(uint32_t *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                             uint32_t new_val, size_t a_size);

template void
update_element_pull_att<uint32_t>(uint32_t *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                                  uint32_t new_val, size_t a_size);

template void
update_element_push_att<uint32_t>(uint32_t *a, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                                  uint32_t new_val, size_t a_size);

template auto
extract_symbol<uint32_t>(const uint32_t *A, size_t a_size, size_t bit_start_index, size_t bit_end_index) -> uint32_t;

//template auto read_T_word<uint32_t>(const vector<bool> *v, size_t start, size_t end) -> uint32_t;

template auto read_T_word<unsigned long long>(const vector<bool> *v, size_t start, size_t end) -> unsigned long long;

template auto
equality_vec_array<uint32_t>(const vector<bool> *v, const uint32_t *a, size_t a_size, size_t bits_lim) -> int;

template
void vector_update_element_with_fixed_size<uint32_t>(vector<bool> *vec, size_t bit_start_pos, size_t bit_end_pos,
                                                     uint32_t new_val);

template
void vector_update_element_with_fixed_size<size_t>(vector<bool> *vec, size_t bit_start_pos, size_t bit_end_pos,
                                                   size_t new_val);

template void
vector_update_element<uint32_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                                uint32_t new_val);

template void
vector_update_element<size_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                              size_t new_val);


template void
vector_update_push<uint32_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                             uint32_t new_val);

template void
vector_update_push<size_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                           size_t new_val);

template void
vector_update_pull<uint32_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                             uint32_t new_val);


template void
vector_update_pull<size_t>(vector<bool> *vec, size_t prev_start, size_t prev_end, size_t new_start, size_t new_end,
                           size_t new_val);





/*auto slot_size = sizeof(a[0]) * CHAR_BIT;
auto start_index = bit_start_pos / slot_size;
auto end_index = bit_end_pos / slot_size;
auto new_end_pos = bit_start_pos + new_val_length;
auto new_end_index = new_end_pos / slot_size;
*/
// LONGER ELEMENT!
/*floor(log2(prev_val)) < floor(log2(new_val))
if (bit_length_difference > 0) {
   update_element_push(a, bit_start_pos, bit_end_pos, new_val, a_size);
   return;
   //todo
//        size_t shift = bit_end_pos - bit_start_pos;
//        assert(bit_end_pos > bit_start_pos);
   size_t shift = bit_length_difference;


   assert((0 < shift) && (shift < slot_size));
   for (auto i = a_size - 1; i > new_end_index; --i) {
       a[i] = (a[i] >> shift) | (a[i - 1] << (slot_size - shift));
       assert(a[i] <= MASK(slot_size));
   }
   // (new_end_index % slot_size == 0) --> (start_index < new_end_index)
   if (start_index < new_end_index) {
       a[new_end_index] >>= shift;

       update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
       cout << "H1" << endl;
       return;
   } else {
       auto left_mask = bit_start_pos % slot_size;
       auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
       auto right = a[start_index] & (MASK(bit_end_pos % slot_size));
       assert(a[start_index] == left | right);
       a[start_index] = left | (right >> shift);


       update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
       cout << "H2" << endl;
       return;
   }*/
//*/
//    }
//    update_element_pull(a, bit_start_pos, bit_end_pos, new_val, a_size);
/*
    //// Shorter element!
    auto length = bit_end_pos - bit_start_pos;
    assert(length == -bit_length_difference + 1);
    size_t shift = -bit_length_difference;
//    size_t shift = bit_end_pos - bit_start_pos;
//    if (shift != length){
//        cout << "M1" << endl;
//    }
    assert(bit_end_pos > bit_start_pos);

    if (start_index < new_end_index) {
        for (auto i = new_end_index; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        cout << "bit_end_pos: " << bit_end_pos << endl;
        cout << "new_end_pos: " << new_end_pos << endl;
        cout << "bit_length_difference: " << bit_length_difference << endl;
        cout << "length: " << new_end_pos - bit_start_pos << endl;
        update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);


        cout << "H3" << endl;
        return;

    } else if (start_index == new_end_index) {

        const auto temp = a[start_index + 1];
        for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        if (start_index == end_index) {
            auto break_point_cond = (new_val == 0) and (bit_start_pos == 0) && a[1];

            auto bit_start_rem = bit_start_pos % slot_size;
            auto bit_end_rem = new_end_pos % slot_size;
            auto l_power = slot_size - (bit_start_rem);
            auto left = (l_power) ? a[start_index] & (~MASK(l_power)) : 0;


//            T mid = (a[start_index] & (MASK(bit_end_pos % slot_size))) << shift;
//            T mid2 = (a[start_index] & (MASK(bit_end_rem))) << shift;
//            auto mid_big2 = (a[start_index] & (MASK(new_end_pos % slot_size))) << shift;
//            auto cond = (mid2 == mid_big2) && (mid2);
//            T see_res = left | mid2 | right;
//            a[start_index] = left | mid2 | right;


            auto right = temp >> (slot_size - shift);
            auto right2 = temp >> (shift);
            a[start_index] = left | right;


            update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
            a[start_index];
            cout << "H4" << endl;
            return;

        } else if (start_index < end_index) {
            if (bit_end_pos % slot_size == 0) {
                auto break_point_cond = (new_val == 1) and (bit_start_pos == 13);

                auto left_mask = slot_size - (bit_start_pos % slot_size);
                auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
                //todo check the shifting.
                auto right = temp >> (slot_size - shift);
                auto before = left | right;
                a[start_index] = left | right;
                update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
                cout << "H4.5" << endl;
                auto after = a[start_index];
                return;
//                auto check = temp >> (slot_size - (shift + 1));
//                assert()
            }
            auto break_point_cond = (new_val == 1) and (bit_start_pos == 13);
            auto left_mask = slot_size - (bit_start_pos % slot_size);
            auto mid_mask = bit_end_pos % slot_size;
            auto new_mid_mask = new_end_pos % slot_size;
            auto bit_end_rem = new_end_pos % slot_size;
            auto right_mask = slot_size - bit_end_rem;
            auto right_shift = slot_size - shift;
            auto bits_to_leave = slot_size - (new_end_pos % slot_size);
            cout << "before a[start_index]: " << a[start_index] << endl;

            assert(new_end_index < end_index);
            auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
            auto mid = (a[start_index] & (MASK(bit_end_pos % slot_size))) << shift;
            auto right = temp & MASK(right_mask);
            auto check = temp & MASK(right_mask);
            right >>= (slot_size - bit_end_rem) - bits_to_leave;
            check >>= (slot_size - bit_end_rem) - shift;
//            auto right = (temp << bit_end_rem) >> right_shift;
//            auto right = ((temp & MASK(right_mask)) >> (right_shift - ));
//            assert(right == right & MASK(bits_to_leave));
//            auto right = (temp >> (right_shift)) & MASK(bits_to_leave);
            assert(right == check);
            auto r1 = left | right;
            auto r2 = check | right;
            a[start_index] = left | right;
*/

/*
//            auto so_see_res = left | mid | right;
//            auto no_mid = left | right;
//            auto new_mid = (a[start_index] & (MASK(new_mid_mask))) << shift;
//            a[start_index] = left | right;
//            auto att = left | new_mid | right;

cout << "after a[start_index]: " << a[start_index] << endl;
cout << "left: " << left << endl;
cout << "mid: " << mid << endl;
//            cout << "new_mid: " << new_mid << endl;
cout << "right: " << right << endl;


cout << "left_mask: " << left_mask << endl;
cout << "mid_mask: " << mid_mask << endl;
cout << "new_mid_mask: " << new_mid_mask << endl;
cout << "right_shift: " << right_shift << endl;

cout << "\nbit_start_pos: " << bit_start_pos << "\tnormalized: " << bit_start_pos % slot_size << endl;
cout << "bit_end_pos: " << bit_end_pos << "\tnormalized: " << bit_end_pos % slot_size << endl;
cout << "new_end_pos: " << new_end_pos << "\tnormalized: " << new_end_pos % slot_size << endl;
cout << "bit_length_difference: " << bit_length_difference << endl;
cout << "length: " << new_end_pos - bit_start_pos << endl;
update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);
cout << "H5" << endl;
return;
}
} else
assert(false);

update_element_with_fixed_size<T>(a, bit_start_pos, new_end_pos, new_val, a_size);

*/
/*
    auto left = a[start_index] & (~MASK(bit_start_pos % slot_size));
    auto right = a[start_index] & (MASK(bit_end_pos % slot_size));
    assert(a[start_index] == left | right);
a[start_index] = left | (right << shift);*/
/*





auto fp_size = bit_length_difference;
auto bit_index = new_end_pos;
auto size = a_size;
size_t left_fp_start_index = slot_size - bit_index;

if (slot_size >= fp_size + bit_index) {
    ulong shift = left_fp_start_index;
    ulong mask = MASK(left_fp_start_index);
    ulong upper = a[new_end_index] & (~mask);
    BODY_BLOCK_TYPE mid = (a[new_end_index] & MASK(left_fp_start_index - fp_size)) << fp_size;
    BODY_BLOCK_TYPE lower = (a[new_end_index + 1]) >> (slot_size - fp_size);
    a[new_end_index] = (upper | lower | mid);

    if (DB) assert(shift >= fp_size);
    if (DB) assert(slot_size - fp_size >= 0);

    for (size_t i = new_end_index + 1; i < size - 1; ++i) {
        a[i] = (a[i] << fp_size) | (a[i + 1] >> (slot_size - fp_size));
    }
    a[size - 1] <<= fp_size;

} else {
    ulong shift = left_fp_start_index;
    ulong mask = MASK(left_fp_start_index);
    ulong upper = a[new_end_index] & (~mask);
    ulong lower_shift = slot_size - fp_size;
    BODY_BLOCK_TYPE lower = a[new_end_index + 1] >> lower_shift;
    lower &= MASK(left_fp_start_index);
    a[new_end_index] = upper | lower;

    for (size_t i = new_end_index + 1; i < size - 1; ++i) {
        a[i] = (a[i] << fp_size) | (a[i + 1] >> (slot_size - fp_size));
    }
    a[size - 1] <<= fp_size;

    if (DB) assert(0 <= shift and shift < fp_size);
    if (DB) assert(0 <= lower_shift and lower_shift < slot_size);
}*/
/*
if (new_end_pos % slot_size == 0) {

}
assert((0 < shift) && (shift < slot_size));
for (auto i = end_index; i > end_index; ++i) {
    a[i] = (a[i] >> shift) | (a[i - 1] << (slot_size - shift));
    assert(a[i] <= MASK(slot_size));
}
//todo this is probably wrong.
if (start_index == new_end_index){

}
if (start_index <= end_index) {
    a[end_index] >>= shift;
} else {
    auto left = a[start_index] & (~MASK(bit_start_pos % slot_size));
    auto right = a[start_index] & (MASK(bit_end_pos % slot_size));
    assert(a[start_index] == left | right);
    a[start_index] = left | (right >> shift);
}
update_element_with_fixed_size<T>(a, bit_start_pos, bit_end_pos + shift, new_val, a_size);
return;
*/






/*else if (case2) {
        assert(new_end_index < end_index);

        const auto temp = a[start_index + 1];
        assert(start_index + 2 < a_size);
        const auto temp_next = a[start_index + 2];
        const auto temp2 = a[end_index];
        assert((temp == temp2) and case2);

        for (auto i = new_end_index + 1; i < a_size - 1; ++i) {
            a[i] = (a[i] << shift) | (a[i + 1] >> (slot_size - shift));
        }
        a[a_size - 1] <<= shift;

        *//*if (prev_end % slot_size == 0){
            auto maybe_new_val = (new_val == 0) or (new_val == 1) or (new_val == 493440);
            bool pos_cond = (prev_start == 13) and ((prev_end == 13) or (prev_end == 32));
            auto break_point_cond = maybe_new_val and pos_cond and a[1];
//                auto break_point_cond = (new_val == 1) and (prev_start == 13);

            auto left_mask = slot_size - (prev_start % slot_size);
            auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
            //todo check the shifting.
            auto right = temp2 >> (slot_size - shift);
            auto before = left | right;
            a[start_index] = left | right;
            update_element_with_fixed_size<T>(a, prev_start, new_end_pos, new_val, a_size);
            cout << "H4.5" << endl;
            auto after = a[start_index];
            return;
        }
        *//*
        auto b_res = a[start_index];
        //todo clean-up
        auto break_point_cond = (new_val == 1) and (prev_start == 13);
        auto left_mask = slot_size - (prev_start % slot_size);
        auto right_shift = slot_size - shift;
        auto prev_end_rem = prev_end % slot_size;
        *//*
//        auto mid_mask = prev_end % slot_size;
//        auto new_mid_mask = new_end_pos % slot_size;
//        auto bit_end_rem = new_end_pos % slot_size;
//        auto right_mask = slot_size - bit_end_rem;
//        auto bits_to_leave = slot_size - (new_end_pos % slot_size);
//        cout << "before a[start_index]: " << a[start_index] << endl;
        *//*

        auto left = (left_mask) ? a[start_index] & (~MASK(left_mask)) : 0;
        auto right_length = shift;
        auto right = 0;

        //"right" should also take some bits from the a[index + 2]
        if (prev_end_rem + right_length > slot_size) {
            assert (prev_end_rem + right_length <= 2 * slot_size); // shift plus values length is not too big.
            auto bits_to_take_from_first_slot = (slot_size - prev_end_rem);
            auto bits_to_take_from_second_slot = right_length - bits_to_take_from_first_slot;
            auto first_right = temp & MASK(bits_to_take_from_first_slot);
            auto first_right_naive = extract_symbol<T>(unchanged_a, a_size, prev_end,
                                                       prev_end + bits_to_take_from_first_slot);
            assert(first_right == first_right_naive);
            auto second_right =
                    (temp_next >> (slot_size - bits_to_take_from_second_slot)) & MASK(bits_to_take_from_second_slot);
            auto second_right_naive = extract_symbol<T>(unchanged_a, a_size, prev_end + bits_to_take_from_first_slot,
                                                        prev_end + right_length);
            assert(second_right == second_right_naive);

            right = (first_right << bits_to_take_from_second_slot) | second_right;
            unsigned long w = (first_right << bits_to_take_from_second_slot) | second_right;
            assert(w == right);
            auto naive_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + shift);
            assert(naive_right == right);
            cout << "H4.5" << endl;
        } else {
            right = (temp >> right_shift) & MASK(shift);
            auto naive_right = extract_symbol<T>(unchanged_a, a_size, prev_end, prev_end + shift);
            assert(naive_right == right);
        }


//        auto right_attempt = extract_symbol<T>(a, a_size, prev_end, prev_end + shift);
        auto mid_res = left | right;*/
/*
//        auto right_a = (temp & (~MASK())) >> right_shift;
//        auto mid = (a[start_index] & (MASK(prev_end % slot_size))) << shift;
//        auto right = temp & MASK(right_mask);
//        auto check = temp & MASK(right_mask);
check >>= (slot_size - bit_end_rem) - shift;
//            assert(right == check);
auto r1 = left | right;
//            auto r2 = check | right;
*/
/*a[start_index] = left | right;


update_element_with_fixed_size<T>(a, new_start, new_end, new_val, a_size);
auto after = left | right;
cout << "H5" << endl;
return;

}*/