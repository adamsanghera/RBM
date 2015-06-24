//
//  Unit.h
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__Unit__
#define __RBM__Unit__

#include <stdio.h>
#include "BoltzmannDistribution.h"
#include "time.h"
#include "random"
#include "iostream"

namespace Boltzmann {
    class Unit {
    public:
        Unit(bool state): state(state) {}
        bool pingState()  {
            return state;
        }
        bool ping(double energyDifferential, BoltzmannDistribution b);
        ~Unit() { }
    private:
        bool state;
    };
}

#endif /* defined(__RBM__Unit__) */
