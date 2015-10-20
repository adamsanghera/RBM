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
#include <string>
//#include "CIMG/CImg.h"

namespace Boltzmann {
    class Network {
    public:
        //  Constructors
            Network(size_t soBL, size_t soHL = 50,  BoltzmannDistribution bd = BoltzmannDistribution(1));
        
        //  Misc. Essential Methods
            void updateBoltDist (BoltzmannDistribution bdNew) { dist = bdNew; }
            void pushLayer (size_t sizeOfNewLayer);
            void swapOutInput (std::vector<bool> inputs);
            void iterateLearnCycle (double learningRate, size_t numberOfIts, bool softMaxTop = false);
            void swapWithRandomInput();
            void generateInput();

        //  Misc. Helpful Methods
            std::string extractVisibleLayerAsString();
            void printNetwork();
        
        //  Destructor
            ~Network();
    private:
        std::vector<Machine*> listOfMachines;
        BoltzmannDistribution dist;
        size_t numMachines, sizeOfBaseLayer;
        
    };
}

#endif /* defined(__RBM__Network__) */
