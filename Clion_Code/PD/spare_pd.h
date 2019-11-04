//
// Created by tomer on 11/4/19.
//

#ifndef CLION_CODE_SPARE_PD_H
#define CLION_CODE_SPARE_PD_H

#include "PD.h"

class spare_pd : public PD {


public:



    /**
     * Element is removed only if it is found in the pd.
     * @param quotient
     * @param remainder
     * @return
     */
    bool conditional_remove(size_t quotient, FP_TYPE remainder);

    void
    partial_match_conditional_remove(size_t quotient, uint32_t partial_remainder, size_t partial_remainder_length,
                                     uint32_t *origin_remainder);


};


#endif //CLION_CODE_SPARE_PD_H
