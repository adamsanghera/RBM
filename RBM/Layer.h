//
//  Layer.h
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__Layer__
#define __RBM__Layer__

#include <stdio.h>
#include "Unit.h"
#include <vector>

namespace Boltzmann {
    class Layer {
        friend class Machine;
        friend class Network;
    public:
        //  Constructors
            Layer(size_t numberOfUnits);
            Layer(const Layer& rhs);
        
        //  Misc. Methods
            std::vector<int> getStates() const;
            void clampStateOfUnit (size_t unitIndex, bool state);
            void clampStateOfUnits (std::vector<int> states);
            bool ping (size_t unitIndex, double eDiff, BoltzmannDistribution& bd) const;
        
        //  Layer Destructor
            ~Layer();
    private:
        std::vector<Boltzmann::Unit*> listOfUnits;
        size_t numUnits;
    };
}

#endif /* defined(__RBM__Layer__) */
