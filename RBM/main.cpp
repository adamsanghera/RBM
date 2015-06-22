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
    Boltzmann::Layer l(5);
    n.pushLayer(l);
    n.pushLayer(Boltzmann::Layer(2));
    
    Boltzmann::Matrix y(3,6);
    Boltzmann::Matrix z(3,6);
    Boltzmann::Matrix w(3,6);
    
    std::cout << "Ha!\n";
    //  Structure:
    //      Unit:       These units include Hidden and Visible units
    //      Layer:      Layers contain units
    //      Network:    Contains layers
    //  How do we handle edges?  Stochastic stuff?
    //  When we're back-propagating, what level should that be at?  Presumably layer.
    //  Should layers have links to other layers?  -- Probably not
}
