//
//  Network.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Network.h"

using namespace arma;

//  Boltzmann::Network Constructor
//  -   Constructs a Netowrk composed of a single Boltzmann::Machine of dimensions (soBL, soHL).
//  In the future, perhaps we should have a Network constructor that starts without any machines?

    Boltzmann::Network::Network(size_t soBL, size_t soHL,  Boltzmann::BoltzmannDistribution bd)
        :   listOfMachines(std::vector<Machine*>(1)),
            dist(bd),
            sizeOfBaseLayer(soBL)
        {
            listOfMachines[0] = new Machine(soBL, soHL);
            numMachines = 1;
    }

//  Boltzmann::Network::pushLayer
//  -   Pushes a new layer of size sizeOfNewLayer into the network.
//  -   This method accomplishes it's task by adding a new Machine, whose visible layer is the previous uppermost layer,
//          and whose hidden layer is the new layer which is now being pushed into the network.

    void Boltzmann::Network::pushLayer(size_t sizeOfNewLayer) {
        Layer* dummy = listOfMachines[listOfMachines.size()-1]->topLayer;
        listOfMachines.push_back(new Machine(dummy, new Layer(sizeOfNewLayer)));
        numMachines++;
    }

//  Boltzmann::Network::iterateLearnCycle
//  -   Goes through the entire list of Machines, calling the method Boltzmann::iterateLearnCycle on each.
//  *   This method follows the idea of training each Machine in a cascade, iteratively.
//      -   e.g. Machine 1 is trained, and its output hidden layer is used as Machine 2's visible layer; from which 2 is trained.

    void Boltzmann::Network::iterateLearnCycle(double learningRate, size_t numberOfIts, bool softMaxTop) {
        if (softMaxTop) {
            for (int i = 0; i < listOfMachines.size()-1; ++i)
                listOfMachines[i]->backPropagationTuning(learningRate, dist, numberOfIts);
            listOfMachines[listOfMachines.size()-1]->backPropagationTuning(learningRate, dist, numberOfIts, softMaxTop);
        }
        else
            for (int i = 0; i < listOfMachines.size(); ++i)
                listOfMachines[i]->backPropagationTuning(learningRate, dist, numberOfIts);
    }

//  Boltzmann::Network::swapOutInput
//  -   Replaces the current input vector (lowermost layer) with a new input vector.

    void Boltzmann::Network::swapOutInput(vec inputs) {       // We need to pass in a vec, not a vector
        listOfMachines[0]->replaceVisibleLayer(inputs);
    }

//  Boltzmann::Network::swapWithRandomInput
//  -   Randomizes the inputVector (the lowest layer in the network)
//  *   Uses a similar uniform distribution model as that model which is implemented in Boltzmann::Unit::ping

    void Boltzmann::Network::swapWithRandomInput() {
        // Create the input vector
        arma_rng::set_seed_random();
        vec newInputLayer(sizeOfBaseLayer, fill::randu);
        std::cout << newInputLayer << std::endl;
        for (int i = 0; i < newInputLayer.size(); ++i) {
            float j = newInputLayer[i];
            if (j < .5)
                newInputLayer[i] = 0;
            else
                newInputLayer[i] = 1;
        }
        listOfMachines[0]->replaceVisibleLayer(newInputLayer);
    }

//  Boltzmann::Network::generateInput
//  -   Generates an input which is fantasized by the network.
//  *   Accomplishes this task by calling a stochasticDownPass from the highest machine all the way down to the lowest machine.

    void Boltzmann::Network::generateInput() {
        for (size_t i = numMachines-1; i > -1; --i) {
            listOfMachines[i]->stochasticDownPass(dist);
        }
    }

//  Boltzmann::Network::extractVisibleLayerAsString
//  -   Spits out a string equivalent of the input layer.
//  ~   Useful in analyzing a network's fantasy input.

    std::string Boltzmann::Network::extractVisibleLayerAsString() {
        std::string o("");
        for (int i = 0; i < sizeOfBaseLayer; ++i)
            o.push_back(listOfMachines[0]->botLayer->listOfUnits[i]->pingState());
        return o;
    }

//  Boltzmann::Network::printNetwork
//  -   Prints out a visual representation of the network's current state vectors.

    void Boltzmann::Network::printNetwork() {
        for (int i = 0; i < numMachines; ++i) {
            for (int j = 0; j < listOfMachines[i]->botLayer->numUnits; j++) {
                if (j % 50 == 0)    std::cout << "\n";
                std::cout << listOfMachines[i]->botLayer->listOfUnits[j]->pingState();
            }
            std::cout << "\n";
        }
        for (int k = 0; k < listOfMachines[numMachines-1]->topLayer->numUnits; ++k) {
            if (k % 50 == 0)    std::cout << "\n";
            std::cout << listOfMachines[numMachines-1]->topLayer->listOfUnits[k]->pingState();
        }
        std::cout << "\n";
    }

//  Boltzmann::Network Destructor
//  -   Iterates through the Machines, deleting visible and hidden layers in a weave that avoids malloc bugs.

    Boltzmann::Network::~Network() {
        for (int i = 0; i < listOfMachines.size(); ++i) {
            delete listOfMachines[i]->botLayer;
            listOfMachines[i]->botLayer = nullptr;
            if (i == listOfMachines.size()-1)   delete listOfMachines[i]->topLayer;
            listOfMachines[i]->topLayer = nullptr;
        }
        for (int j = 0; j < listOfMachines.size(); ++j)
            delete listOfMachines[j];
    }