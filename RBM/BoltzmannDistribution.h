//
//  BoltzmannDistribution.h
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__BoltzmannDistribution__
#define __RBM__BoltzmannDistribution__

#include <stdio.h>
#include <math.h>


namespace Boltzmann {
    class BoltzmannDistribution {
    public:
        BoltzmannDistribution(double tValue): tValue(tValue) {}
        double getProb(double input) const;
    private:
        double tValue;
    };
}


#endif /* defined(__RBM__BoltzmannDistribution__) */
