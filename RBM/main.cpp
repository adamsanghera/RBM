//
//  main.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Network.h"


int main() {
    Boltzmann::Network n(10);
    Boltzmann::Machine m(3, 2);
    Boltzmann::BoltzmannDistribution bd(.5);
    Boltzmann::BoltzmannDistribution bd2(2);
    Boltzmann::BoltzmannDistribution bd3(4);
    std::vector<bool> inputs;
    inputs.push_back(true);
    inputs.push_back(false);
    inputs.push_back(false);
    m.replaceVisibleLayer(inputs);
    
    
    std::cout << "Ha!\n";
    //  Structure:
    //      Unit:       These units include Hidden and Visible units
    //      Layer:      Layers contain units
    //      Network:    Contains layers
    //  How do we handle edges?  Stochastic stuff?
    //  When we're back-propagating, what level should that be at?  Presumably layer.
    //  Should layers have links to other layers?  -- Probably not
}
