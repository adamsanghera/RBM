//
//  HiddenUnit.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "HiddenUnit.h"
#include <iostream>
#include <sys/types.h>


bool Boltzmann::HiddenUnit::ping(double energyDifferential, BoltzmannDistribution b) const {
    //  energydiff = summation (weights times states) aka b
    //  totalInput (a) = bias (optional) + summation of weights*states (b)
    
    double prob = b.getProb(energyDifferential);  // 1 = certain, 0 = never
    srand(time(nullptr));
    double out = rand() % (1000);
    double realOut = out / 1000;
    if (realOut < prob) {
        return true;
    }
    return false;
}