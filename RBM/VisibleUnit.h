//
//  VisibleUnit.h
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__VisibleUnit__
#define __RBM__VisibleUnit__

#include <stdio.h>
#include "Unit.h"

namespace Boltzmann {
    class VisibleUnit: public Unit {
    public:
        VisibleUnit(bool clamp): clampedState(clamp) {}
        VisibleUnit(): clampedState(false) {}
        VisibleUnit(const VisibleUnit& rhs) {clampedState = rhs.clampedState;}
        
        bool ping(double e = -1, BoltzmannDistribution b = BoltzmannDistribution(-1)) const { return clampedState; }
        ~VisibleUnit() {delete this;}
    private:
        bool clampedState;
    };
}

#endif /* defined(__RBM__VisibleUnit__) */
