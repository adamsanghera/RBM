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
#include "Matrix.h"

namespace Boltzmann {
    class Machine {
        friend class Network;
    public:
        /*  Constructors    */
            Machine(size_t sizeOfBase, size_t sizeOfTop);
            Machine(Layer* const vis, Layer* const hid);
        
            Machine(Layer* const vis, Layer* const hid, size_t machineType);    // Links two layers in a specific manner

        /*  Misc. Essential Methods */
            void forward(BoltzmannDistribution& bd, bool constant);            // Experimental: generalized forward pass
            void back(BoltzmannDistribution& bd, bool constant);               // Experimental: generalized backward pass
            void stochasticUpPass(BoltzmannDistribution& bd);   // This might become a private method
            void stochasticDownPass(BoltzmannDistribution& bd); // This, too, might become a private method
            void determinsticUpPass();                          // This, finally, might become a private method
        
            // This should stay public
            void backPropagationTuning(double learnRate, BoltzmannDistribution& bd, size_t numberOfExchanges = 100, double decayRate=.1, unsigned decayStep = 20);
        
            // I'm unconvinced that this should be public.
            void replaceVisibleLayer(std::vector<bool> inputs);
        
        /*  Begin Experimental Section */
            void softMaxDeterministicUpPass();
            void displayMachineState();
            void emplaceRandomVisibleLayer();
        /*  End Experimental Section */
        
        //  Machine Destructor
            ~Machine();
    private:
        void adjustWeights(bool increment, double learnRate);
        Layer* hiddenLayer;
        Layer* visibleLayer;
        Matrix weights;
        size_t hiddenSize, visSize;
        
        size_t machineType;             // 0 is stochastic (normal operation), 1 is softmax
    };
}

#endif /* defined(__RBM__Machine__) */
