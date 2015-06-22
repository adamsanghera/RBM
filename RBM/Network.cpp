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

//  Replaces the current input vector (visible base layer) with a new input vector

void Boltzmann::Network::swapOutInput(std::vector<bool> inputs) {
    for (int i = 0; i < listOfLayers[0]->numUnits; ++i) {
        listOfLayers[0]->clampState(i, inputs[i]);
    }
}

void Boltzmann::Network::iterateLearnCycle(double learningRate) {
    // What do we have to do here?
    //  1.  Iterate up the network, pinging from left to right.  We should save the 'pinged' states in some temporary vector.
    //  2.  Save this state of the network somewhere. 1st state
    //  3.  Iterate *down* the network, pinging from left to right.  Treat the topmost units as clamped, generate next layer down, clamp. so on.
    //  4.  Save this state of the network somewhere. 2nd state
    //  5.  Create a matrix for each incremental layer pair for both network state 1 and 2, tracking the off-on states.
    //  6.  Iterate through the weight matrices, and subtract from them these off-on matrices times a learning factor.
}