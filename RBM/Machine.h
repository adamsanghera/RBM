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
        //  Constructors
            Machine(size_t sizeOfBase, size_t sizeOfTop);
            Machine(Layer* const vis, Layer* const hid);

        //  Misc. Essential Methods
            void stochasticUpPass(BoltzmannDistribution& bd);
            void stochasticDownPass(BoltzmannDistribution& bd);
            void determinsticUpPass();
            void iterateLearning(double learnRate, BoltzmannDistribution& bd, size_t numberOfExchanges = 100);
            void replaceVisibleLayer(std::vector<bool> inputs);
        
        /*  Begin Experimental Section */
            void softMaxClamp(size_t numberOfUnitsToClamp);
        /*  End Experimental Section */
        
        //  Machine Destructor
            ~Machine();
    private:
        void adjustWeights(bool increment, double learnRate);
        Layer* hiddenLayer;
        Layer* visibleLayer;
        Matrix weights;
        size_t hiddenSize, visSize;
    };
}

#endif /* defined(__RBM__Machine__) */
