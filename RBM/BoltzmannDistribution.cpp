//
//  BoltzmannDistribution.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "BoltzmannDistribution.h"

double Boltzmann::BoltzmannDistribution::getProb(double energyDifferential) const {
    double denom = (1 + exp(-energyDifferential/tValue));
    return 1/denom;
}