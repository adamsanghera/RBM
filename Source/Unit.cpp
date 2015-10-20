//
//  Unit.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Unit.h"

//  Boltzmann::Unit::ping
//  -   Stochastically pings a new state, depending on the passed-in energeyDifferential value and the passed-in Boltzmann Distribution model
//  *   Calls a method in the Boltzmann::BoltzmannDistribution class, 'getProb' to sample from the Boltzmann Distribution.
//  ~   This is the most fundamental method in the Boltzmann::Network Hierarchy.  It is essential for learning.

    bool Boltzmann::Unit::ping(double energyDifferential, BoltzmannDistribution& b) {
        double prob = b.getProb(energyDifferential);
        srand(time(nullptr));
        double out = rand() % (1000);
        double realOut = out / 1000;
        if (realOut < prob) {
            state = true;
            return true;
        }
        state = false;
        return false;
    }