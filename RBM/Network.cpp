//
//  Network.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Network.h"

// Constructs a Network object, composed of a single layer of visible units and a Boltzmann Distribution.

Boltzmann::Network::Network(size_t soBL,  Boltzmann::BoltzmannDistribution bd)
    :   listOfLayers(std::vector<Layer*>(1)),
        dist(bd),
        sizeOfBaseLayer(soBL),
        listOfWeightMatrices(std::vector<Matrix>())
    {
        listOfLayers[0] = new Layer(soBL, true);
        numLayers = 1;
}

// Adds a new layer to the top of the network.

void Boltzmann::Network::pushLayer(Boltzmann::Layer l) {
    listOfLayers.push_back(new Layer(l));
    listOfWeightMatrices.push_back(Matrix(listOfLayers[numLayers-1]->numUnits, l.numUnits));
    numLayers++;
}