//
//  Unit.h
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//
//  Class Unit:
//      - The "Unit" is the most basic element of the Boltzmann Machine.
//      - Units are modeled after neurons.
//      - Units are binary switches; that is, they are always in an 'on' or 'off' state.
//      - Units trigger other units to flip on or off, depending on the strength of the connections between them.
//      - When units are exposed to large, positive energy, they tend to switch on or remain on.
//      - When units are exposed to large, negative energy, they tend to switch off or remain off.
//      - Units pass on their energy via connections to other Units.

#ifndef __RBM__Unit__
#define __RBM__Unit__

#include <stdio.h>
#include "BoltzmannDistribution.h"
#include "time.h"
#include "random"
#include "iostream"


namespace Boltzmann {
    class Unit {
    public:
        //  Constructor
            Unit(bool state): state(state) {}
        
        //  Misc. Essential Methods
            bool pingState()  { return state; }
            bool ping(double energyDifferential, BoltzmannDistribution& b);
            void clampState(bool newState) { state = newState; }

        //  Unit Destructor
            ~Unit() { }
    private:
        bool state;
    };
}

#endif /* defined(__RBM__Unit__) */
