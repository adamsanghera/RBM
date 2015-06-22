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
    if (rhs.isVisible)
        for (int i = 0; i < rhs.listOfUnits.size(); ++i) {
            listOfUnits[i] = new VisibleUnit(rhs.listOfUnits[i]->ping(-1, BoltzmannDistribution(1)));
        }
    else
        for (int i = 0; i < rhs.listOfUnits.size(); ++i) {
            listOfUnits[i] = new HiddenUnit;
        }
    isVisible = rhs.isVisible;
}

//  Constructor for Layer objects.  Creates a Layer object with fields numberOfUnits and isVisible.

Boltzmann::Layer::Layer(size_t numberOfUnits, bool isVisible)
    :   isVisible(isVisible),
        numUnits(numberOfUnits),
        listOfUnits(numberOfUnits)
    {
        if (!isVisible)
            for (int i = 0; i < numberOfUnits; ++i)
                listOfUnits[i] = new HiddenUnit();
        else
            for (int i = 0; i < numberOfUnits; ++i)
                listOfUnits[i] = new VisibleUnit();
}

//  Clamps the state of the visible unit at a given index.  If the units are hidden, or if the index does not exist, throws an error.

void Boltzmann::Layer::clampState(size_t unitIndex, bool state) {
    if (isVisible) {
        if (unitIndex < listOfUnits.size()) {
            delete listOfUnits[unitIndex];
            listOfUnits[unitIndex] = new VisibleUnit(state);
            return;
        }
        std::cerr << "The selected index " << unitIndex << " does not exist in this layer." << std::endl;
        return;
    }
    std::cerr << "You cannot clamp a hidden unit." << std::endl;
}