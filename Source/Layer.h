//
//  Layer.h
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//
//  Class Layer:
//      - The "Layer" is the second-lowest level element of the Boltzmann Machine.
//      - Layers are composed of several inter-_in_dependent units.
//      - Layers are woven together via the connections between their respective units.
//          + These connections are described and stored in the Matrix member variable of a Layer-pair's Machine parent.


#ifndef __RBM__Layer__
#define __RBM__Layer__

#include <stdio.h>
#include "Unit.h"
#include <vector>
#include <armadillo>

namespace Boltzmann {
    class Layer {
        friend class Machine;
        friend class Network;
    public:
        //  Constructors
            Layer(size_t numberOfUnits);
            Layer(const Layer& rhs);
        
        //  Misc. Methods
            arma::mat getStates() const;
            void clampStateOfUnit (size_t unitIndex, bool state);
            void clampStateOfUnits (arma::mat states);
            bool ping (size_t unitIndex, double eDiff, BoltzmannDistribution& bd) const;
            bool pingState(size_t unitIndex) const { return listOfUnits[unitIndex]->pingState(); }
        
        //  Layer Destructor
            ~Layer();
    private:
        std::vector<Boltzmann::Unit*> listOfUnits;
        size_t numUnits;
    };
}

#endif /* defined(__RBM__Layer__) */
