//
// Created by tomer on 4/10/20.
//

#include "validate_counter_PD.hpp"


auto v_CPD(size_t reps, size_t max_capacity, size_t element_length, size_t counter_size, double working_load_factor,
           double variance, bool to_seed) -> bool {
    CPD_validator vd(max_capacity, element_length, counter_size);

    std::multiset<uint32_t> my_set;
    std::multiset<uint32_t> out_set;
    std::multiset<uint32_t> in_set;


    std::mt19937 gen{1};
    if (to_seed) { gen.seed(clock()); }
    std::normal_distribution<> d{working_load_factor * max_capacity, variance};

    size_t counter = 0;
    while (out_set.size() < max_capacity) {
        assert(counter++ < 1E5);
        out_set.insert(out_set.end(), random() & MASK(element_length));
    }

    counter = 0;
    while (my_set.size() < (max_capacity * working_load_factor)) {
        assert(counter++ < 1E5);
        auto index = random() % out_set.size();
        auto it = std::begin(out_set);
        std::advance(it, index);
        uint32_t el = *it;

        out_set.erase(el);
        in_set.insert(el);

//        v_HT_insert(el, &ht, &my_set);
    }

    for (int i = 0; i < reps; ++i) {
        bool to_insert;
        if (vd.is_empty())
            to_insert = true;
        else if (vd.is_full())
            to_insert = false;
        else {
            to_insert = d(gen) > vd.get_capacity();
        }

        if (to_insert) return true;
    }
}

auto op_sequence_iter(size_t reps, size_t max_capacity, size_t element_length, size_t counter_size,
                      double working_load_factor, double variance, bool to_seed) -> bool {
    CPD_validator vd(max_capacity, element_length, counter_size);


    vector<std::tuple<CPD_TYPE, CPD_TYPE>> el_vec;
    CPD_TYPE remainder_mask = MASK(element_length);
    CPD_TYPE counter_mask = MASK(counter_size);
    for (int i = 0; i < max_capacity; ++i) {
        CPD_TYPE q = random() % max_capacity;
        CPD_TYPE r = random() & remainder_mask;
        while (r == 0) {
            r = random() & remainder_mask;
        }
        std::tuple<CPD_TYPE, CPD_TYPE> temp_el = std::make_tuple(q, r);
        el_vec.insert(el_vec.begin(), temp_el);
    }

    const size_t max_power = 7;
    size_t power_array[max_power] = {2, 4, 8, 16, 32, 64, 128};
    /**Element in the 2^i position with be inserted i times. max is 7*/
    for (int i = 0; i < max_capacity; ++i) {
        for (unsigned long power : power_array) {
            if (i % power != 0)
                break;

            auto temp_el = el_vec[i];
            CPD_TYPE q, r;
            std::tie(q, r) = temp_el;
//            bool BPC = (q == 35) and (i == 44);
            vd.insert(q, r);
        }
    }

    /** lookup*/
    for (int i = 0; i < max_capacity; ++i) {
        if (i % 2 == 1) {
            auto temp_el = el_vec[i];
            CPD_TYPE q, r;
            std::tie(q, r) = temp_el;
            if (!v_lookup_helper(&vd, q, r, false)) {
                v_lookup_helper(&vd, q, r, false);
                return false;
            }
        } else {
            auto temp_el = el_vec[i];
            CPD_TYPE q, r;
            std::tie(q, r) = temp_el;
            if (!v_lookup_helper(&vd, q, r, true)) {
                v_lookup_helper(&vd, q, r, true);
                return false;
            }

            for (int j = 1; j < max_power; ++j) {
                if (i % power_array[j] != 0) {
                    size_t exp_res = j;
                    if (!v_lookup_multi_helper(&vd, q, r, exp_res)) {
                        v_lookup_multi_helper(&vd, q, r, exp_res);
                        return false;
                    }
                    break;
                }
            }
        }
    }


    /**removing elements*/
    for (int i = 0; i < max_capacity; ++i) {
        size_t temp = i;
        size_t counter = 0;
        while (temp % 4 == 0) {
            auto temp_el = el_vec[i];
            CPD_TYPE q, r;
            std::tie(q, r) = temp_el;
            v_remove_helper(&vd, q, r, OK);
            temp /= 4;
//            counter_status exp_res = (SL(++counter) == i) ? dec_underflow : OK;
            /*if (!v_remove_helper(&vd, q, r, OK)) {
                v_remove_helper(&vd, q, r, OK);
                return false;
            }*/
        }
    }

    /** lookup*/
    for (int i = 0; i < max_capacity; ++i) {
        if (i % 2 == 1) {
            auto temp_el = el_vec[i];
            CPD_TYPE q, r;
            std::tie(q, r) = temp_el;

            if (!v_lookup_helper(&vd, q, r, false)) {
                v_lookup_helper(&vd, q, r, false);
                return false;
            }
        }
    }

    return true;

}

auto v_lookup_helper(CPD_validator *vd, CPD_TYPE q, CPD_TYPE r, bool exp_res) -> bool {
    return (vd->lookup(q, r) == exp_res);
}

auto v_lookup_multi_helper(CPD_validator *vd, CPD_TYPE q, CPD_TYPE r, size_t exp_res) -> bool {
    auto res = vd->lookup_multi(q, r);
//    cout << "vd->lookup_multi(q, r) " << vd->lookup_multi(q, r) << endl;
    return (vd->lookup_multi(q, r) == exp_res);
}

void v_remove_helper(CPD_validator *vd, CPD_TYPE q, CPD_TYPE r, counter_status exp_res) {
    vd->remove(q, r);
}

auto do_op(CPD_validator &vd, operation op) {

}

auto get_operation(CPD_validator &vd, double max_load_factor) -> operation {
    return op_insert;
}

auto lookup(CPD_validator &vd, CPD_TYPE q, CPD_TYPE r) -> bool {
    return false;
}

auto v_lookup_multi_wrapper(CPD_validator &vd, CPD_TYPE q, CPD_TYPE r) -> bool {
    vd.lookup(q, r);
    return vd.lookup_multi(q, r);
}

auto insert(CPD_validator &vd, CPD_TYPE q, CPD_TYPE r) -> bool {
    return false;
}

auto remove(CPD_validator &vd, CPD_TYPE q, CPD_TYPE r) -> bool {
    return false;
}
