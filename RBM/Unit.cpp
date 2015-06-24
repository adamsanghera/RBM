//
//  Unit.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Unit.h"

bool Boltzmann::Unit::ping(double energyDifferential, BoltzmannDistribution b) {
    //  energydiff = summation (weights times states) aka b
    //  totalInput (a) = bias (optional) + summation of weights*states (b)
    
    double prob = b.getProb(energyDifferential);  // 1 = certain, 0 = never
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