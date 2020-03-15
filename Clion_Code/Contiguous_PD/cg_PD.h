//
// Created by tomer on 11/24/19.
//
//todo:  (deal_with_joined_slot == false) Implies

#ifndef CLION_CODE_CG_PD_H
#define CLION_CODE_CG_PD_H


#include <ostream>
#include "../Global_functions/basic_functions.h"
#include "../bit_operations/bit_op.h"

#define CG_TYPE uint32_t
#define CG_TYPE_SIZE (sizeof(CG_TYPE) * (CHAR_BIT))


class cg_PD {
    CG_TYPE *a;
    const uint_fast16_t fp_size, max_capacity, size;
    const bool deal_with_joined_slot;

public:
    cg_PD(size_t m, size_t f, size_t l);

//    virtual ~cg_PD();
//    ~cg_PD();

    bool lookup(CG_TYPE q, CG_TYPE r);

    void insert(CG_TYPE q, CG_TYPE r);

    void remove(CG_TYPE q, CG_TYPE r);

    bool conditional_remove(CG_TYPE q, CG_TYPE r);

    bool naive_conditional_remove(CG_TYPE q, CG_TYPE r);

    size_t get_last_a_index_containing_the_header();

    void print_as_consecutive_memory();

    size_t get_capacity();

private:
    bool header_lookup(CG_TYPE q, size_t *start_index, size_t *end_index);

    void header_insert(CG_TYPE q, size_t *start_index, size_t *end_index);

    void header_remove(CG_TYPE q, size_t *start_index, size_t *end_index);

    void header_find(CG_TYPE q, size_t *start, size_t *end);

    void header_push(size_t end_index);

    void header_pull(size_t end_index);

    size_t get_number_of_bits_in_a(size_t m, size_t f, size_t l);

    size_t get_header_bit_index();

    inline size_t get_header_size_in_bits() {
        return max_capacity << 1u;
    }

    size_t get_joined_slot_index();

    bool body_find(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index, size_t *p_array_index,
                   size_t *p_bit_index);

    void body_insert(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index);

    void body_push(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index);

    void body_remove(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index);

    bool body_conditional_remove(CG_TYPE r, size_t unpacked_start_index, size_t unpacked_end_index);

    void body_pull(size_t B_index, size_t bit_index);

public:
    /*For testing*/
    uint32_t *get_a() const;

    const uint_fast16_t get_fp_size() const;

    const uint_fast16_t get_max_capacity() const;

    const uint_fast16_t get_size() const;

    const bool get_deal_with_joined_slot() const;

    void print_as_array() const;


    friend ostream &operator<<(ostream &os, const cg_PD &pd);

};

static size_t get_a_size(size_t m, size_t f, size_t l);


static inline void body_find_helper(size_t current_b_index, size_t bits_left, size_t *p_B_index, size_t *p_bit_index) {
    *p_B_index = current_b_index;
    *p_bit_index = BODY_BLOCK_SIZE - bits_left;
}

static bool should_deal_with_joined_slot(size_t m, size_t f, size_t l) {
    return bool((f * 2) % CG_TYPE_SIZE);
}


#endif //CLION_CODE_CG_PD_H
