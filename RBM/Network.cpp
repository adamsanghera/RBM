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
    :   listOfMachines(std::vector<Machine*>(1)),
        dist(bd),
        sizeOfBaseLayer(soBL)
    {
        listOfMachines[0] = new Machine(soBL, soBL / 2 + 1);
        numMachines = 1;
}

// Adds a new layer to the top of the network.

void Boltzmann::Network::pushLayer(size_t sizeOfNewLayer) {
    Layer* dummy = listOfMachines[listOfMachines.size()-1]->hiddenLayer;
    listOfMachines.push_back(new Machine(dummy, new Layer(sizeOfNewLayer)));
    numMachines++;
}

//  Replaces the current input vector (visible base layer) with a new input vector

void Boltzmann::Network::swapOutInput(std::vector<bool> inputs) {
    listOfMachines[0]->replaceVisibleLayer(inputs);
}

void Boltzmann::Network::iterateLearnCycle(double learningRate) {

}

Boltzmann::Network::~Network() {
    for (int i = 0; i < listOfMachines.size(); ++i)
        delete listOfMachines[i];
}