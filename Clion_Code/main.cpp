#include <iostream>
#include "PD/Header.h"
#include "Tests/validation_tests.h"
#include "POW2C/pow2c_filter.h"
#include "Tests/benchmark_tests.h"
#include "POW2C/pow2c_naive_filter.h"

//todo: naive pow2c_naive_filter validation. benchmark comparing. profiling.

using namespace std;

//#define SEP ("################################################################")

u32 msbDeBruijn32(u32 v) {
    static const int MultiplyDeBruijnBitPosition[32] =
            {
                    0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
                    8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
            };

    v |= v >> 1; // first round down to one less than a power of 2
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    return MultiplyDeBruijnBitPosition[(u32) (v * 0x07C4ACDDU) >> 27];
}

void shifting() {
    int ai = 8;
    size_t at = 8;
    uint32_t au = 8;

    for (uint32_t i = 0; i < 8; ++i) {
        cout << i << ", " << (ai << (i - 4));
        cout << ", " << (at << (i - 4));
        cout << ", " << (au << (i - 4));
        cout << ", " << (1ULL << (i - 4)) << endl;
    }
}

tuple<int, int> tp(int x, int y);


void my_size_of();

void my_resize(vector<int> *v, size_t new_size);

void change_v_by_pointer(vector<int> *v);

void rotate_right(vector<int> *vec, size_t start_index, size_t end_index);

void validate_rank();

int main() {
    std::cout << "Hello, World!" << std::endl;
/*

    uint32_t a[2] = {1,1};
    uint64_t t = *a,r = (1ULL<<32ul) | 1ul;

    bool b = (t == r);
    if (!b){
        printf("got %zu instead of %zu\n",t, r);
    }
    cout << b << endl;
*/
//    validate_rank();
    /*cout << my_bit_rank(0,1) << endl;
    cout << my_bit_rank(0,0) << endl;
    cout << my_bit_rank(~0UL,1) << endl;
    cout << my_bit_rank(~0UL,0) << endl;
    cout << bit_rank(0,1) << endl;
    cout << bit_rank(0,0) << endl;
    cout << bit_rank(~0UL,1) << endl;
    cout << bit_rank(~0UL,0) << endl;
    cout << bit_rank(~0UL,2) << endl;
    cout << endl;
    cout << bit_rank(0,-1) << endl;
    cout << bit_rank(~0UL,-1) << endl;
    cout << bit_rank(~0UL,-2) << endl;
    *//*uint64_t x = 2, y = 3, z = 7, t = 1, w = -1, a = 43690;

    cout << bit_rank(t, 0) << endl;
    cout << bit_rank(t, 1) << endl;
    cout << bit_rank(x, 0) << endl;
    cout << bit_rank(x, 1) << endl;
    cout << bit_rank(y, 0) << endl;
    cout << bit_rank(y, 1) << endl;
    cout << bit_rank(z, 0) << endl;
    cout << bit_rank(z, 1) << endl;
    cout << bit_rank(z, 2) << endl;
    cout << bit_rank(z, 3) << endl;
    cout << bit_rank(z, 4) << endl;

    cout << x << ", " << count(x, 0) << endl;
    cout << w << ", " << count(z, 0) << endl;
    cout << w << ", " << count(z, 16) << endl;
    cout << w << ", " << count(z, 32) << endl;
    cout << w << ", " << count(z, 48) << endl;
    cout << w << ", " << count(z, 64) << endl;

    for (int i = -16; i < 16; ++i) {
        cout << i << ":\t" << count(a, i) << endl;
    }
    for (u_long i = 0; i < 64; ++i) {
        uint64_t temp = (1ull << i) - 1;
        cout << temp << ":\t" << count(temp, i) << endl;
    }
    std::cout << "End!" << std::endl;

    return 1;*/
    /*  int a[10] = {1,2,3,4,5,6,7,8,9,10};
      vector<int> v;
      for (int i = 0; i < 10; ++i) v.push_back(i);

      print_vector(&v);
      rotate_right(&v, 1, 0);
      print_vector(&v);
      rotate_right(&v, 1, 7);
      print_vector(&v);

      return 1;
  */
//    return 1;
    assert(filter_r0(32, 0.75, 128 + 32, 64, 12));
    assert(filter_naive_r0(32, 0.75, 128 + 32, 64, 12));



/*
//    PD d1 = PD(m, f, l);
//    naive_PD d2 = naive_PD(m, f, l);
//    safe_PD d3 = safe_PD(m, f, l);
//    pow2c_naive_filter d = pow2c_naive_filter(pd_num, l, m, f);
//    r0_core_template(256, &d1, m, f, l);
//    r0_core_template(256, &d2, m, f, l);
//    r0_core_template(256, &d3, m, f, l);
*/

    /*pow2c_naive_filter d(pd_num, m, f, l);
    string a = "a", b = "b", c = "c", e = "e";

    d.insert(&a);
    assert(d.lookup(&a));
    d.remove(&a);
    assert(!d.lookup(&a));
    d.insert(&a);
    d.insert(&b);
    d.insert(&c);
    d.insert(&e);
    assert(d.lookup(&a));
    assert(d.lookup(&b));
    assert(d.lookup(&c));
    assert(d.lookup(&e));
    d.remove(&e);
    assert(!d.lookup(&e));
    d.remove(&c);
    assert(!d.lookup(&c));
    d.remove(&b);
    assert(!d.lookup(&b));
    d.remove(&a);
    assert(!d.lookup(&a));
*/


//    cout << filter_r1(pd_num, 0.75, m, f, l) << endl;
//    cout << filter_r0(pd_num, 0.75, m, f, l) << endl;
//    cout << filter_naive_r0(pd_num, 0.75, m, f, l) << endl;
//    r0(128);

stringstream s;
    size_t pd_num = 1<<12, fp_size = 6, m = 32, pd_capacity = 32;

    for (int i = 0; i < 11; ++i) {
        auto load_factor = (i) * (0.1);
//        cout << "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU" << endl;
        cout << "load_factor is: " << load_factor << ". ";
        b0(pd_num, load_factor, pd_capacity, m, fp_size, pd_capacity * pd_num, s);
        cout << "----------------------------------------------------------------" << endl;
//        b0_naive(pd_num, load_factor, pd_capacity, m, fp_size, pd_capacity * pd_num, s);
//        cout << "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD" << endl;
    }


    /*cout  << log(M_E) << endl;
    cout  << log(1) << endl;
    cout  << log(2) << endl;
    cout  << log2(2) << endl;
    cout  << ceil(log2(3)) << endl;*/
//    assert(sizeof(int) == sizeof(uint32_t));
    /*assert (t1());
    assert (t2());
    assert(t3());
    assert(t4());
    for (size_t i = 5; i < 25; ++i) {
        cout << "l is " << i << "\t";
        assert(t5(30, 25, i));
    }
    for (size_t i = 0; i < 3; ++i) {
        for (size_t k = 0; k < 6; ++k) {
            size_t reps = 1ULL << (7 + i);
            r0(reps);
        }
    }

    r0(128);
    cout << "r tests done!" << endl;
    s0(128);
    s0(128);
    s0(128);
    s0(128);*/
//    cout  << r0(128, 0) << endl;


//    t2(true);
//    cout << t2() << endl;

//    auto temp = tp(3, 7);
//    cout << get<0>(temp) << ", " << get<1>(temp) << endl;
/*
//    cout << (MASK(HEADER_BLOCK_SIZE)) << endl;
//    cout << (SL((HEADER_BLOCK_SIZE - 1))) << endl;
//    cout << "size of int: " << sizeof(int) << endl;
//    cout << "size of uint8_t: " << sizeof(uint8_t) << endl;
//    uint8_t x = 1;
//    int y = (uint) x;
//    cout << "x: " << x << endl;
//    cout << "(int)x: " << (int)x << endl;
//    cout << "y: " << y << endl;
*/

//    vector<tuple<int, int>> v;

//    r1(1,1);
/*
//    default_random_engine generator;
//    uniform_int_distribution<int> distribution(31, 32);
//    size_t m = distribution(generator);

    for (int i = 0; i < 32; ++i) {
        cout << distribution(generator) << endl;
    }
*/

    /*for (int i = 0; i < (1 << 12); ++i) {
        if (msb32(i) != naive_msb32(i)) {
            cout << i << endl;
            printf("%d,%d\n",msb32(i) ,naive_msb32(i));
            break;
        }*/
    /*
//        assert(msb32(i) == naive_msb32(i));
//    }
    for (uint8_t i = 0; i < 16; ++i) {
        cout << i << ", " << ", " << msb32(i) << ", " << msb8(i) << endl;
    }
    //255 - 128 = "1011 1111"
*/
    /*HEADER_BLOCK_TYPE a[4] = {170, 170, 170, 170};
    HEADER_BLOCK_TYPE a2[4] = {216, 216, 170, 170};
    HEADER_BLOCK_TYPE a3[4] = {119, 119, 119, 119};
    size_t start, end;
    size_t *p_start = &start, *p_end = &end;

    for (int i = 0; i < 4; ++i) {
        get_interval(a, i, p_start, p_end);
        printf("%d\t(%d, %d)\n", i, start, end);
    }
    cout << endl;
    for (int i = 0; i < 4; ++i) {
        get_interval(a2, i, p_start, p_end);
        printf("%d\t(%d, %d)\n", i, start, end);
    }
    cout << endl;
    for (int i = 0; i < 8; ++i) {
        get_interval_old(a3, i, p_start, p_end);
        printf("%d\t(%d, %d)\n", i, start, end);
    }*/

    /*
    int num = 1;
    uint x = 1;
    cout << (x<<32) << endl;
    cout << (x<<31) << endl;
    cout << "end" << endl;
    if (*(char *) &num == 1) {
        printf("Little-Endian\n");
    } else {
        printf("Big-Endian\n");
    }
    for (int i = 0; i < 16; ++i) {
        cout << i << ", " << msbDeBruijn32(i) << ", " << (i ^ (i & (i - 1))) << ", " << msb32(i) << endl;
    }

*/
    std::cout << "End!" << std::endl;
    return 0;
}


tuple<int, int> tp(int x, int y) {
//    auto temp = make_tuple(1, 1);
//    cout << temp << endl;
//    ret
    return make_tuple(x, y);
}


void my_resize(vector<int> *v, size_t new_size) {
    v->resize(new_size);
}

void my_size_of() {
    uint32_t a1[] = {1, 2, 3};
    uint16_t a2[] = {1, 2, 3};
    uint8_t a3[] = {1, 2, 3};
    cout << "size of (uint32_t) a1[0]: " << sizeof(a1[0]) << endl;
    cout << "size of (uint16_t) a2[0]: " << sizeof(a2[0]) << endl;
    cout << "size of (uint8_t) a3[0]: " << sizeof(a3[0]) << endl;
}

void change_v_by_pointer(vector<int> *v) {
    for (int i = 0; i < v->size(); ++i) {
        v->at(i) = i + 1;
    }
}

void vector_printing() {

    //    vector<int> v;
////    print_vector(&v);
//    cout << v.size() << endl;
//
//    my_resize(&v, 10);
//    print_vector(&v);
//    cout << v.size() << endl;
//
//    change_v_by_pointer(&v);
//    print_vector(&v);
//    cout << v.size() << endl;
}

void rotate_right(vector<int> *vec, size_t start_index, size_t end_index) {
    rotate(vec->rbegin(), vec->rbegin() + 1, vec->rend() - end_index);
}

void validate_counter() {
    size_t reps = 1ULL << 10;
    for (int i = 0; i < reps; ++i) {
        uint32_t temp = rand();
        if (bit_count(temp) != my_count(temp)) {
            cout << i << ", " << temp << ":\t" << bit_count(temp) << ", " << my_count(temp) << endl;
            break;
        }
    }
}

void validate_rank() {
    size_t reps = 1ULL << 10;
    for (int i = 0; i < reps; ++i) {
        uint64_t temp = rand();
        uint32_t rank = rand() % 64;
        if (!rank) continue;
        auto res = bit_rank(temp, rank), exp = my_bit_rank(temp, rank);

        if (res != exp and exp != 64) {
            printf("i=%d, (temp, rank) = (%zu,%u).\t res:%u, exp:%u\n", i, temp, rank, res, exp);
//            cout << i << "| " << temp << ", " << rank << ":\t" << bit_rank(temp, rank) << ", "
//                 << my_bit_rank(temp, rank) << endl;
            break;
        }
    }
}