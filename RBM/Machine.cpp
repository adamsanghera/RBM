//
//  Machine.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Machine.h"

Boltzmann::Machine::Machine(size_t sizeOfBase, size_t sizeOfTop)
:   visibleLayer(new Layer(sizeOfBase)),
    hiddenLayer(new Layer(sizeOfTop)),
    weights(sizeOfBase, sizeOfTop),
    visSize(sizeOfBase),
    hiddenSize(sizeOfTop) {}

Boltzmann::Machine::Machine(Boltzmann::Layer* vis, Boltzmann::Layer* hid)
:   visibleLayer(vis),
    hiddenLayer(hid),
    weights(vis->numUnits, hid->numUnits),
    visSize(vis->numUnits),
    hiddenSize(hid->numUnits) {}


void Boltzmann::Machine::stochasticUpPass(double learnRate, Boltzmann::BoltzmannDistribution bd) {
    double diff = 0.0;
    std::vector<int> origInputs = visibleLayer->getStates();
    for (int i = 0; i < hiddenSize; ++i) {
        for (int j = 0; j < weights.sizeOfLowerLayer; ++j)
            diff += weights.getWeight(j, i) * origInputs[j];
        hiddenLayer->ping(i, diff, bd);
        diff = 0.0;
    }
    Matrix firstGates(visibleLayer->getStates(), hiddenLayer->getStates(), learnRate);
    weights += firstGates;
}

void Boltzmann::Machine::stochasticDownPass(double learnRate, Boltzmann::BoltzmannDistribution bd) {
    double diff = 0.0;
    for (int i = 0; i < hiddenSize; ++i) {
        for (int j = 0; j < weights.sizeOfLowerLayer; ++j)
            diff += weights.getWeight(j, i) * visibleLayer->listOfUnits[j]->pingState();
        hiddenLayer->ping(i, diff, bd);
        diff = 0.0;
    }
    Matrix secondGates(visibleLayer->getStates(), hiddenLayer->getStates(), learnRate);
    weights -= secondGates;
}

void Boltzmann::Machine::generateData(Boltzmann::BoltzmannDistribution bd) {
    double diff = 0.0;
    for (int i = 0; i < visSize; ++i) {
        for (int j = 0; j < weights.sizeOfHigherLayer; ++j)
            diff += weights.getWeight(i, j) * hiddenLayer->listOfUnits[j]->pingState();
        visibleLayer->ping(i, diff, bd);
        diff = 0.0;
    }
}

void Boltzmann::Machine::iterateLearning(double learnRate, Boltzmann::BoltzmannDistribution bd, size_t numberOfExchanges) {
    for (int i = 0; i < numberOfExchanges; ++i) {
        std::vector<int> origInputs = visibleLayer->getStates();
        stochasticUpPass(learnRate, bd);
        generateData(bd);
        stochasticDownPass(learnRate, bd);
        visibleLayer->clampStateOfUnits(origInputs);
    }
}

void Boltzmann::Machine::replaceVisibleLayer(std::vector<bool> inputs) {
    for (int i = 0; i < inputs.size(); ++i)
        visibleLayer->clampStateOfUnit(i, inputs[i]);
}
