#include "dict.hpp"

template<class D, class S>
dict<D, S>::dict(size_t number_of_pd, size_t quotient_range, size_t single_pd_capacity, size_t remainder_length)
        :number_of_pd(number_of_pd),
        capacity(0),
        quotient_range(quotient_range),
         single_pd_capacity(single_pd_capacity),
         remainder_length(remainder_length),
         pd_index_length(ceil(log2(number_of_pd))),
         quotient_length(ceil(log2(single_pd_capacity + 1))),
         spare()

         {
    pd_capacity_vec.resize(number_of_pd);

    for (size_t i = 0; i < number_of_pd; ++i) {
        pd_vec.emplace_back(D(quotient_range, single_pd_capacity, remainder_length));
    }
}

template<class D, class S>
bool dict<D, S>::lookup(string *s) {
    return false;
}

template<class D, class S>
void dict<D, S>::insert(string *s) {

}

template<class D, class S>
void dict<D, S>::remove(string *s) {

}


template
class dict<cg_PD, hash_table<D_TYPE>>;
