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
#include "Layer.h"
#include "Matrix.h"

namespace Boltzmann {
    class Network {
    public:
        Network(size_t soBL,  BoltzmannDistribution bd = BoltzmannDistribution(1));
        void updateBoltDist(BoltzmannDistribution bdNew) { dist = bdNew; }
        
        void pushLayer(Layer l);
        void swapOutInput(std::vector<bool> inputs);
        void iterateLearnCycle(double learningRate);
        
    private:
        std::vector<Layer*> listOfLayers;
        size_t numLayers;
        size_t sizeOfBaseLayer;
        BoltzmannDistribution dist;
        std::vector<Matrix> listOfWeightMatrices;
    };
}

#endif /* defined(__RBM__Network__) */
