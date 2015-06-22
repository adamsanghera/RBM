//
//  HiddenUnit.h
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__HiddenUnit__
#define __RBM__HiddenUnit__

#include <stdio.h>
#include "Unit.h"
#include <random>
#include <math.h>
#include <time.h>
#include <iostream>
#include <sys/types.h>

namespace Boltzmann {
    class HiddenUnit: public Unit {
    public:
        HiddenUnit() {}
        bool ping(double energyDifferential, BoltzmannDistribution b) const;
        ~HiddenUnit() {}
    private:
    
    };
}


#endif /* defined(__RBM__HiddenUnit__) */
