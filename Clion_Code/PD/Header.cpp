//
// Created by tomer on 10/24/19.
//

#include "Header.h"

Header::Header(size_t m, size_t f, size_t l) : capacity(0), max_capacity(f) {
    size_t number_of_bits = ((m + f) << 1ULL) + 1;
    if (HEADER_BLOCK_SIZE != (8 * sizeof(HEADER_BLOCK_TYPE))) {
        assert(false);
    }
    size = (number_of_bits / HEADER_BLOCK_SIZE) + 1;
    H = new HEADER_BLOCK_TYPE[size]();

//    this->vec.resize(number_of_bits);
}

bool Header::lookup(uint_fast16_t quotient, size_t *start_index, size_t *end_index) {
    this->get_quotient_start_and_end_index(quotient, start_index, end_index);
    return *start_index != *end_index;
}

void Header::insert(uint_fast16_t quotient, size_t *start_index, size_t *end_index) {
    assert(capacity < max_capacity);
    get_quotient_start_and_end_index(quotient, start_index, end_index);
    push(quotient, *start_index, *end_index);

//    vector_insert(quotient);
//    validate_get_interval(quotient);

    capacity++;
}

void Header::remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index) {
    get_quotient_start_and_end_index(quotient, start_index, end_index);
    assert (*end_index > *start_index); //deleting from empty run.

    pull(quotient, *start_index, *end_index);

//    vector_remove(quotient);
//    validate_get_interval(quotient);
    capacity--;
}

bool Header::conditional_remove(uint_fast16_t quotient, size_t *start_index, size_t *end_index) {
    //todo
    /*get_quotient_start_and_end_index(quotient, start_index, end_index);
    assert (*end_index > *start_index); //deleting from empty run.

    pull(quotient, *start_index, *end_index);

    capacity--;*/
}

void Header::push(uint_fast16_t quotient, size_t start, size_t end) {
    size_t index;
//    get_quotient_start_and_end_index(quotient, &start, &end);
    index = end / HEADER_BLOCK_SIZE;

    for (uint_fast16_t i = size - 1; i > index; --i) {
        this->H[i] = ((ulong) (H[i]) >> 1ul) | (H[i - 1] & 1ul) << ((ulong) (HEADER_BLOCK_SIZE - 1));
    }

    uint_fast16_t bit_index = end % HEADER_BLOCK_SIZE;
    uint_fast16_t shift = HEADER_BLOCK_SIZE - bit_index;
    HEADER_BLOCK_TYPE upper = (shift < HEADER_BLOCK_SIZE) ? (((ulong) H[index]) >> shift) << shift : 0;
//    HEADER_BLOCK_TYPE upper = (this->H[index] >> shift) << shift;
    HEADER_BLOCK_TYPE lower = ((ulong) H[index] >> 1ul) & (MASK(shift));
    this->H[index] = ((ulong) upper | lower | SL((ulong) shift - 1));
    /*
    shift = block_size - index
    upper = (n >> shift) << shift
    lower = (n >> 1) & ((1 << shift) - 1)
    return upper + lower
    */

}

void Header::pull(uint_fast16_t quotient, size_t start, size_t end) {
    size_t index;

    index = (end - 1) / HEADER_BLOCK_SIZE;
    if (index == size - 1) {
        uint_fast16_t bit_index = (end - 1) % HEADER_BLOCK_SIZE;
        uint_fast16_t shift = HEADER_BLOCK_SIZE - bit_index;
        HEADER_BLOCK_TYPE upper = (shift < HEADER_BLOCK_SIZE) ? ((ulong) H[index] >> shift) << shift : 0;
//        HEADER_BLOCK_TYPE upper = (this->H[index] >> shift) << shift;
        HEADER_BLOCK_TYPE mid = ((ulong) H[index] << 1ul) & (MASK(shift));
//        HEADER_BLOCK_TYPE lower = (this->H[index + 1]) >> (HEADER_BLOCK_SIZE - 1);
        this->H[index] = upper | mid;

        assert(H[index] ^ SL((ulong) bit_index - 2)); //Making sure the run's end, marked by zero, is not deleted.
    }
    HEADER_BLOCK_TYPE lower = ((ulong) H[index + 1]) >> ((ulong) (HEADER_BLOCK_SIZE - 1));

    for (size_t i = index + 1; i < this->size - 1; ++i) {
        this->H[i] = ((ulong) H[i] << 1ul) | ((ulong) H[i + 1] >> ((ulong) (HEADER_BLOCK_SIZE - 1)));
    }
    this->H[this->size - 1] <<= 1ul;

    uint_fast16_t bit_index = (end - 1) % HEADER_BLOCK_SIZE;
    uint_fast16_t shift = HEADER_BLOCK_SIZE - bit_index;
    HEADER_BLOCK_TYPE upper = (shift < HEADER_BLOCK_SIZE) ? ((ulong) H[index] >> shift) << shift : 0;
//    HEADER_BLOCK_TYPE upper = (this->H[index] >> shift) << shift;
    HEADER_BLOCK_TYPE mid = ((ulong) H[index] << 1ul) & (MASK(shift));

    this->H[index] = (ulong) upper | mid | lower;// | SL(shift);
//todo: why here?    assert(H[index] ^ SL((ulong)bit_index - 2)); //Making sure the run's end, marked by zero, is not deleted.
}

void Header::get_quotient_start_and_end_index(size_t quotient, size_t *start_index, size_t *end_index) {
    get_interval_attempt(H, size, quotient, start_index, end_index);
//    validate_get_interval(quotient);

}

void
get_interval_attempt(const HEADER_BLOCK_TYPE *a, size_t a_size, size_t quotient, size_t *start_index, size_t *end_index) {
    size_t zero_counter = -1, continue_from_a_index = 0, continue_from_bit_index = -1;
    bool to_break = false;
    for (size_t i = 0; i < a_size; ++i) {
        ulong b = 1ULL << (ulong) (HEADER_BLOCK_SIZE - 1);
        for (int j = 0; j < HEADER_BLOCK_SIZE; ++j) {
            assert(b > 0);
            if (zero_counter == quotient - 1) {
                *start_index = i * HEADER_BLOCK_SIZE + j;
                continue_from_a_index = i;
                continue_from_bit_index = j;
                to_break = true;
                break;
            }
            if (not(a[i] & b))
                zero_counter++;

            b >>= 1ul;
        }
        if (to_break) break;
    }
    assert(continue_from_bit_index >= 0);

    size_t j = continue_from_bit_index;
    ulong b = 1ULL << (ulong) (HEADER_BLOCK_SIZE - 1 - j);
    for (size_t i = continue_from_a_index; i < a_size; ++i) {
        for (; j < HEADER_BLOCK_SIZE; ++j) {
            if (not(a[i] & b)) {
                *end_index = i * HEADER_BLOCK_SIZE + j;
                return;
            }
            b >>= 1ul;
        }
        b = 1ULL << (ulong) (HEADER_BLOCK_SIZE - 1);
        j = 0;
    }
    assert(false);
}

void Header::print() {
    cout << "[" << H[0];
    for (size_t i = 1; i < size; ++i) {
        cout << ", " << H[i];
    }
    cout << "]" << endl;

}

void Header::print_as_bool_array() {
    size_t a_size = size * HEADER_BLOCK_SIZE;
    bool a[a_size];
    header_to_bool_array(a);
    print_bool_array(a, a_size);
}

void Header::header_to_bool_array(bool *a) {
    size_t counter = 0;
    for (size_t i = 0; i < size; ++i) {
        size_t b = 1ULL << (ulong) (HEADER_BLOCK_SIZE - 1);
        for (int j = 0; j < HEADER_BLOCK_SIZE; ++j) {
            a[counter] = H[i] & b;
            counter++;
            b >>= 1ul;
        }
    }
}

void Header::pretty_print() {
    size_t a_size = size * HEADER_BLOCK_SIZE;
    bool a[a_size];
    header_to_bool_array(a);

    int run_length_array[max_capacity];
    size_t run_index = 0;
    size_t index = 0;

    while ((index < a_size) and (run_index < max_capacity)) {
        size_t counter = 0;
        while (a[index] != 0) {
            counter++;
            index++;
        }
        run_length_array[run_index] = counter;
        index++;
        run_index++;
    }

    assert(run_index == max_capacity);
    cout << "[(0:" << run_length_array[0] << ")";
    for (size_t i = 1; i < max_capacity; ++i) {
        cout << ", (" << i << ":" << run_length_array[i] << ")";
    }
    cout << "]" << endl;

}

void Header::print_as_word() {
    size_t const_factor = (32 / HEADER_BLOCK_SIZE);
    size_t a_size = INTEGER_ROUND(size, const_factor);
    uint32_t a[a_size];
    header_to_word_array(a, a_size);
    cout << "[" << a[0];
    for (size_t i = 1; i < a_size; ++i)
        cout << ", " << a[i];
    cout << "]" << endl;
    /*size_t lim = size / const_factor;
    for (size_t i = 0; i < lim; ++i) {
        ulong x = H[i * 4];
        for (int j = 1; j < const_factor; ++j) {
            x <<= 1ul;
            x = H[i * 4 + j];
        }
    }*/
}

void Header::header_to_word_array(uint32_t *a, size_t a_size) {
    size_t const_factor = (32 / HEADER_BLOCK_SIZE);
    size_t lim = size / const_factor;
    size_t a_index = 0;
    for (size_t i = 0; i < lim; ++i) {
        a[a_index] = ((uint32_t) H[(i * 4)]) << 24ul | ((uint32_t) H[(i * 4 + 1)]) << 16ul |
                     ((uint32_t) H[(i * 4) + 2]) << 8ul | ((uint32_t) H[(i * 4) + 3]);
        /*
//        ulong x = H[i * 4];
//        for (size_t j = 1; j < const_factor; ++j) {
//            x <<= 1ul;
//            x = H[i * 4 + j];
//        }
//        a[a_index] = x;
*/
        a_index++;
    }
    if (size % const_factor == 0)
        return;

    size_t bits_left_counter = size % const_factor;
    size_t i = lim;

    if (bits_left_counter == 1)
        a[a_index] = (ulong) H[(i * 4)] << 24ul | (ulong) H[(i * 4 + 1)] << 16ul | (ulong) H[(i * 4) + 2] << 8ul;
    else if (bits_left_counter == 2)
        a[a_index] = (ulong) H[(i * 4)] << 24ul | (ulong) H[(i * 4 + 1)] << 16ul;
    else if (bits_left_counter == 3)
        a[a_index] = (ulong) H[(i * 4)] << 24ul;

    else {
        assert(const_factor == 4);
        assert(false);
    }
}

ostream &operator<<(ostream &os, const Header &header) {
    os << "H: " << header.H;
    return os;
}

size_t Header::get_size() const {
    return size;
}

uint8_t *Header::get_h() const {
    return H;
}


/*
void Header::print_bool_array(bool *a, size_t a_size) {
    cout << "[" << a[0];
    for (size_t i = 0; i < a_size; ++i) {
        cout << ", " << a[i];
    }
    cout << "]" << endl;
}*/

/*

void Header::vector_get_interval(size_t quotient, size_t *start_index, size_t *end_index) {
    size_t zero_counter = -1, continue_from_index = 0;

    for (size_t i = 0; i < vec.size(); ++i) {
        if (zero_counter == quotient - 1) {
            *start_index = i;
            continue_from_index = i;
            break;
        }
        if (vec[i] == 0)
            zero_counter++;
    }

    for (size_t i = continue_from_index; i < vec.size(); ++i) {
        if (vec[i] == 0) {
            *end_index = i;
            return;
        }
    }
    assert(false);
}

void Header::vector_insert(size_t quotient) {
    size_t a = -1, b = -1;
    this->vector_get_interval(quotient, &a, &b);
    vec.insert(vec.begin() + a, true);
    vec.pop_back();
}

void Header::vector_remove(uint_fast16_t quotient) {
    size_t a = -1, b = -1;
    this->vector_get_interval(quotient, &a, &b);
    assert(a < b);
    vec.erase(vec.begin() + a);
    vec.push_back(false);
}

uint32_t Header::sum_vector() {
    size_t sum = 0;
    for (auto b  : vec)
        if (b) sum++;
    return sum;
}

void Header::validate_get_interval(size_t quotient) {
    size_t a = -1, b = -1, va = -1, vb = -1, c = -1, d = -1;
    vector_get_interval(quotient, &va, &vb);
    get_interval_attempt(H, size, quotient, &c, &d);
    bool cond2 = (c == va) && (d == vb);
    if (not cond2) {
        cout << "header as word is: ";
        this->print_as_word();
        cout << "vector as word is: ";
        print_vector_as_words(&vec);

    }
    assert(c == va);
    assert(d == vb);
*/
/*
//        cout << endl;
//        cout << endl;
//        this->print_as_bool_array();
//        print_vector(&vec);
//        cout << endl;
//        cout << endl;
        cout << "vector sum is: " << sum_vector() << endl;
*//*


*/
/*
    //    get_interval_old(H, size, quotient, &a, &b);
//    bool cond = (a == va) && (b == vb);
//    if (cond and !cond2){
//        cout << a << ", " << b << endl;
//        get_interval_attempt(H, size, quotient, &c, &d);
//    }
//    assert(not (cond2 ^ cond));
*//*

}
*/




void
get_interval_old(const HEADER_BLOCK_TYPE *a, size_t a_size, size_t quotient, size_t *start_index, size_t *end_index) {
    if (quotient == 0) {
        *start_index = 0;
        size_t b = 1 << (HEADER_BLOCK_SIZE - 1);

        if (a[0] < b) {
            *end_index = 0;
            return;
        }

        size_t one_counter = 1;
        b >>= 1ULL;
        for (size_t a_index = 0; a_index < a_size; ++a_index) {
            for (int i = 0; i < HEADER_BLOCK_SIZE; ++i) {
                if (a[a_index] & b)
                    one_counter++;
                else {
                    *end_index = one_counter;
                    return;
                }
                b >>= 1ULL;
            }
            b = 1 << (HEADER_BLOCK_SIZE - 1);
        }
        assert(false);
/*
        for (int i = 0; i <; ++i) {

        }

        bool cond = true;
        size_t i = 0;
        uint b;

        size_t zero_counter = 1;
        size_t array_index = -1;
        size_t bit_index = 0;

        while (cond) {
            for (i; i < HEADER_BLOCK_SIZE; i++) {
                if (b & (a[array_index]))
                    bit_index++;
                else {
                    cond = false;
                    break;
                }
                b >>= 1;
            }
            b = SL((HEADER_BLOCK_SIZE - 1));
            i = 0;
            array_index++;
        }
        *end_index = bit_index + 1;
        for (int i = 0; i < a_size; ++i) {
            auto reversed = (a[i]) ^((MASK(HEADER_BLOCK_SIZE)));
            u32 floor_log = floor_log2(reversed);
            *end_index = HEADER_BLOCK_SIZE - floor_log - 1;

        }
        auto reversed = (a[index]) ^((MASK(HEADER_BLOCK_SIZE)));
        u32 floor_log = floor_log2(reversed);
        *end_index = HEADER_BLOCK_SIZE - floor_log - 1;
//        if ()
        size_t index = 0;
        while (true) {
            if (a[index] == 0) {
                index++;
                continue;
            }
            auto reversed = (a[index]) ^((MASK(HEADER_BLOCK_SIZE)));
            u32 floor_log = floor_log2(reversed);
            *end_index = HEADER_BLOCK_SIZE - floor_log - 1;
            return;*/
        /*
//            cout << "reversed is: " << reversed << endl;

//            cout << "floor_log: " << floor_log << endl;
//            cout << "res: " << HEADER_BLOCK_SIZE - floor_log - 1 << endl;
        return;
        if (floor_log) {
            cout << "msb is: " << floor_log << endl;
            cout << "res: " << HEADER_BLOCK_SIZE - floor_log << endl;
            *end_index = HEADER_BLOCK_SIZE - floor_log;
            return;
        }*/
    }
    uint b;
    size_t zero_counter = 1;
    size_t array_index = -1;
    size_t bit_index = 0;

    bool cond = true;
    while (cond) {
        assert(zero_counter <= quotient);
        array_index++;
        b = SL((HEADER_BLOCK_SIZE - 1));
        for (int i = 0; i < HEADER_BLOCK_SIZE; ++i) {
            if (not(b & (a[array_index]))) {
                zero_counter++;
                if (zero_counter > quotient) {
                    cond = false;
                    break;
                }
            }
            bit_index++;
            b >>= 1;
        }
    }
    *start_index = bit_index + 1;
    b >>= 1;
//    assert(b);
    size_t i = (*start_index) % HEADER_BLOCK_SIZE;


    /*else {
       array_index++;
       *start_index = 0;
       b = (1ULL << (HEADER_BLOCK_SIZE - 1));
   }*/
    cond = true;
    while (cond) {
        for (i; i < HEADER_BLOCK_SIZE; i++) {
            if (b & (a[array_index]))
                bit_index++;
            else {
                cond = false;
                break;
            }
            b >>= 1;
        }
        b = SL((HEADER_BLOCK_SIZE - 1));
        i = 0;
        array_index++;
    }
    *end_index = bit_index + 1;

}
