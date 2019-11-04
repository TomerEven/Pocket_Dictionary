////
//// Created by tomer on 11/4/19.
////
////
//// A space-inefficient dictionary.


#ifndef CLION_CODE_SID_H
#define CLION_CODE_SID_H

//#include "../Global_functions/basic_functions.h"
#include "../Hash/Hash.h"
#include "CSD.h"



class SID {
    vector<CSD> csd_vec;
    D_TYPE **ll_array;
    size_t size, csd_size, capacity, remainder_length, pd_index_length;
    const Hash *h;
public:

    SID(size_t number_of_csd, size_t csd_size, const Hash *h, size_t remainder_length, size_t org_pd_index_length);

    bool lookup(size_t csd_index, D_TYPE x);

    void insert(size_t csd_index, D_TYPE x);

    void remove(size_t csd_index, D_TYPE x);

    /**
     * Called whenever a PD is no longer full due to deletion (of x).
     * @param x
     * @return An element y (in SID) s.t h(y) == h(x). Removes y from SID.
     */
    uint32_t pop(D_TYPE x);

private:
    D_TYPE get_org_pd_index(D_TYPE x);
};


#endif //CLION_CODE_SID_H
