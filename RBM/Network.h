//
//  Network.h
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__Network__
#define __RBM__Network__

#include <stdio.h>
#include "Machine.h"
#include "Matrix.h"

namespace Boltzmann {
    class Network {
    public:
        Network(size_t soBL,  BoltzmannDistribution bd = BoltzmannDistribution(1));
        
        void updateBoltDist     (BoltzmannDistribution bdNew) { dist = bdNew; }
        void pushLayer          (size_t sizeOfNewLayer);
        void swapOutInput       (std::vector<bool> inputs);
        void iterateLearnCycle  (double learningRate);
        
        ~Network();
    private:
        std::vector<Machine*> listOfMachines;
        BoltzmannDistribution dist;
        size_t numMachines, sizeOfBaseLayer;
    };
}

#endif /* defined(__RBM__Network__) */
