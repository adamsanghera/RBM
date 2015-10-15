//
//  Network.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Network.h"

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
        Layer* dummy = listOfMachines[listOfMachines.size()-1]->hiddenLayer;
        listOfMachines.push_back(new Machine(dummy, new Layer(sizeOfNewLayer)));
        numMachines++;
    }

//  Boltzmann::Network::swapOutInput
//  -   Replaces the current input vector (lowermost layer) with a new input vector.

    void Boltzmann::Network::swapOutInput(std::vector<bool> inputs) {
        listOfMachines[0]->replaceVisibleLayer(inputs);
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

//  Boltzmann::Network Destructor
//  -   Iterates through the Machines, deleting visible and hidden layers in a weave that avoids malloc bugs.

    Boltzmann::Network::~Network() {
        for (int i = 0; i < listOfMachines.size(); ++i) {
            delete listOfMachines[i]->visibleLayer;
            listOfMachines[i]->visibleLayer = nullptr;
            if (i == listOfMachines.size()-1)   delete listOfMachines[i]->hiddenLayer;
            listOfMachines[i]->hiddenLayer = nullptr;
        }
        for (int j = 0; j < listOfMachines.size(); ++j)
            delete listOfMachines[j];
    }

//  Boltzmann::Network::swapWithRandomInput
//  -   Randomizes the inputVector (the lowest layer in the network)
//  *   Uses a similar uniform distribution model as that model which is implemented in Boltzmann::Unit::ping

    void Boltzmann::Network::swapWithRandomInput() {
        std::vector<bool> inputs;
        srand(time(nullptr));
        for (int i = 0; i < sizeOfBaseLayer; ++i) {
            double out = rand() % 1000;
            double real = out / 1000;
            if (real < .50)
                inputs.push_back(true);
            else
                inputs.push_back(false);
        }
        swapOutInput(inputs);
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
            o.push_back(listOfMachines[0]->visibleLayer->listOfUnits[i]->pingState());
        return o;
    }

//  Boltzmann::Network::printNetwork
//  -   Prints out a visual representation of the network's current state vectors.

    void Boltzmann::Network::printNetwork() {
        for (int i = 0; i < numMachines; ++i) {
            for (int j = 0; j < listOfMachines[i]->visibleLayer->numUnits; j++) {
                if (j % 50 == 0)    std::cout << "\n";
                std::cout << listOfMachines[i]->visibleLayer->listOfUnits[j]->pingState();
            }
            std::cout << "\n";
        }
        for (int k = 0; k < listOfMachines[numMachines-1]->hiddenLayer->numUnits; ++k) {
            if (k % 50 == 0)    std::cout << "\n";
            std::cout << listOfMachines[numMachines-1]->hiddenLayer->listOfUnits[k]->pingState();
        }
        std::cout << "\n";
    }