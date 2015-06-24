//
//  Machine.h
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__Machine__
#define __RBM__Machine__

#include <stdio.h>
#include "Layer.h"
#include "Matrix.h"

namespace Boltzmann {
    class Machine {
        friend class Network;
    public:
        Machine(size_t sizeOfBase, size_t sizeOfTop);
        Machine(Layer* vis, Layer* hid);
        
        void stochasticUpPass(double learnRate, BoltzmannDistribution bd);
        void stochasticDownPass(double learnRate, BoltzmannDistribution bd);
        void generateData(BoltzmannDistribution bd);
        void iterateLearning(double learnRate, BoltzmannDistribution bd, size_t numberOfExchanges = 100);
        void replaceVisibleLayer(std::vector<bool> inputs);
        
        ~Machine() { delete hiddenLayer; delete visibleLayer; }
    private:
        Layer* hiddenLayer;
        Layer* visibleLayer;
        Matrix weights;
        size_t hiddenSize, visSize;
    };
}

#endif /* defined(__RBM__Machine__) */
