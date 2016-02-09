//
//  Machine.h
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//
//  Class Machine:
//      - The "Machine" is highest level element of the Boltzmann Machine.
//      - Machines are composed of *two* and only *two* Layers.
//      - The Machine manages the interactions between it's two associated Layers.
//      - Layers may coexist across several different Machines (Machines store Layer pointers, not Layers).
//          + For example, the top Layer of one Machine could be the bottom Layer of another Machine.
//          + Accordingly, a single machine can feed or fork into multiple other machines.
//      - The weights of the connections between Units of a Machine's respective layers are stored in the Machine class.


#ifndef __RBM__Machine__
#define __RBM__Machine__

#include <stdio.h>
#include "Layer.h"
#include <armadillo>

namespace Boltzmann {
    class Machine {
        friend class Network;
    public:
        //  Constructors
            Machine(size_t botSize, size_t topSize);
            Machine(Layer* const low, Layer* const top);

        //  Misc. Essential Methods
            void stochasticUpPass(BoltzmannDistribution& bd);
            void stochasticDownPass(BoltzmannDistribution& bd);
            void determinsticUpPass();
            void backPropagationTuning(double learnRate, BoltzmannDistribution& bd, size_t numberOfExchanges = 100, bool softMax = false, double decayRate=.1, unsigned decayStep = 20);
            void replaceVisibleLayer(arma::vec inputs);
        
        /*  Begin Experimental Section */
            void softMaxDeterministicUpPass();
            void displayMachineState();
            void emplaceRandomVisibleLayer();
        /*  End Experimental Section */
        
        //  Machine Destructor
            ~Machine();
    private:
        void adjustWeights(bool increment, double learnRate);
        Layer* botLayer;
        Layer* topLayer;
        arma::mat weights;
        size_t topSize, botSize;
    };
}

#endif /* defined(__RBM__Machine__) */
