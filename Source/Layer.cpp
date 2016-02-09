//
//  Layer.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Layer.h"

using namespace arma;

//  Boltzmann::Layer Constructors
//  1.  General Constructor
//      -   Takes a size_t numberOfUnits and constructs a layer of deactivated units and numberOfUnits size.
//  2.  Copy Constructor
//      -   Takes another layer rhs, and creates a new Layer with new Units whose states mirror the states of corresponding units in rhs.

    //  1
    Boltzmann::Layer::Layer(size_t numberOfUnits)
        :   numUnits(numberOfUnits),
            listOfUnits(numberOfUnits)
        {
            for (int i = 0; i < numberOfUnits; ++i)
                listOfUnits[i] = new Unit(false);
    }

    //  2
    Boltzmann::Layer::Layer(const Layer& rhs) {
        listOfUnits = std::vector<Boltzmann::Unit*>(rhs.numUnits);
        numUnits = rhs.numUnits;
        for (int i = 0; i < rhs.listOfUnits.size(); ++i) {
            listOfUnits[i] = new Unit(rhs.listOfUnits[i]->pingState());
        }
    }

//  Boltzmann::Layer::clampStateOfUnit
//  -   Clamps the state of unit contained in unitIndex to 'state'.

    void Boltzmann::Layer::clampStateOfUnit(size_t unitIndex, bool state) {
        if (unitIndex < listOfUnits.size())
            return listOfUnits[unitIndex]->clampState(state);
        std::cerr << "The selected index " << unitIndex << " does not exist in this layer." << std::endl;
    }

//  Boltzmann::Layer::getStates
//  -   Returns a vector of integers to represent the states of units contained within this layer.

    mat Boltzmann::Layer::getStates() const {
        mat p = mat(1, listOfUnits.size());
        for (int i = 0; i < listOfUnits.size(); ++i)
            p(i) = (listOfUnits[i]->pingState());
        return p;
    }

//  Boltzmann::Layer::clampStateOfUnits
//  -   Clamps the state of all units in this layer to match the states contained within the input vector of integers, 'states'.
//  ~   If the integers within states are not 0 or 1, they will be forced into an appropriate binary value.  i.e. 193 -> 1.

    void Boltzmann::Layer::clampStateOfUnits(mat states) {
        for (int i = 0; i < states.size(); ++i)
            clampStateOfUnit(i, states[i]);
    }

//  Boltzmann::Layer ping
//  -   Calls the method Boltzmann::Unit::ping on the unit contained within listOfUnits[unitIndex]
//  ~   This is essentially a helper method, allowing for a shorthand calling of Boltzmann::Unit::ping from higher-level methods.
//  ~   This method MODIFIES THE STATE OF THE UNIT AT 'unitIndex'.
//          Therefore, do *not* call this method when attempting to retrieve a specific unit's state without changing it.

    bool Boltzmann::Layer::ping(size_t unitIndex, double eDiff, BoltzmannDistribution& bd) const {
        return listOfUnits[unitIndex]->ping(eDiff, bd);
    }

//  Boltzmann::Layer Destructor
//  -   Deletes all the units contained within this layer.

    Boltzmann::Layer::~Layer() {
        for (int i = 0; i < listOfUnits.size(); ++i)
            if (listOfUnits[i] != nullptr) {
                delete listOfUnits[i];
                listOfUnits[i] = nullptr;
            }
        numUnits = 0;
    }
