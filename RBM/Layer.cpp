//
//  Layer.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Layer.h"

// Copy constructor for Layer.  Copies over the units of rhs to this.

Boltzmann::Layer::Layer(const Layer& rhs) {
    listOfUnits = std::vector<Unit*>(rhs.numUnits);
    numUnits = rhs.numUnits;
    for (int i = 0; i < rhs.listOfUnits.size(); ++i) {
        listOfUnits[i] = new Unit(rhs.listOfUnits[i]->pingState());
    }
}

//  Constructor for Layer objects.  Creates a Layer object with fields numberOfUnits and isVisible.

Boltzmann::Layer::Layer(size_t numberOfUnits)
    :   numUnits(numberOfUnits),
        listOfUnits(numberOfUnits)
    {
        for (int i = 0; i < numberOfUnits; ++i)
            listOfUnits[i] = new Unit(false);
}

//  Clamps the state of the unit at a given index.  If the index does not exist, throws an error.

void Boltzmann::Layer::clampStateOfUnit(size_t unitIndex, bool state) {
    if (unitIndex < listOfUnits.size()) {
        listOfUnits[unitIndex] = new Unit(state);
        return;
    }
    std::cerr << "The selected index " << unitIndex << " does not exist in this layer." << std::endl;
    return;
}


std::vector<int> Boltzmann::Layer::getStates() const {
    std::vector<int> p;
    for (int i = 0; i < listOfUnits.size(); ++i)
        p.push_back(listOfUnits[i]->pingState());
    return p;
}


void Boltzmann::Layer::clampStateOfUnits(std::vector<int> states) {
    for (int i = 0; i < states.size(); ++i)
        clampStateOfUnit(i, states[i]);
}

Boltzmann::Layer::~Layer() {
    for (int i = 0; i < listOfUnits.size(); ++i)
        delete listOfUnits[i];
}

bool Boltzmann::Layer::ping(size_t unitIndex, double eDiff, BoltzmannDistribution bd) const {
    return listOfUnits[unitIndex]->ping(eDiff, bd);
}
