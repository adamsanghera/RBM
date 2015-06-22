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
#include "VisibleUnit.h"
#include "HiddenUnit.h"
#include <vector>

namespace Boltzmann {
    class Layer {
        friend class Network;
    public:
        Layer(size_t numberOfUnits, bool isVisible = false);
        Layer(const Layer& rhs);
        ~Layer() { for (int i = 0; i < listOfUnits.size(); ++i) delete listOfUnits[i]; }
        
        void clampState(size_t unitIndex, bool state);
    private:
        std::vector<Unit*> listOfUnits;
        size_t numUnits;
        bool isVisible;
    };
}

#endif /* defined(__RBM__Layer__) */
