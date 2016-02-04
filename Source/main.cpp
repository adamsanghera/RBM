//
//  main.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Network.h"
#include "SimilarityTester.h"
#include <armadillo>

class timer;

using namespace std;
using namespace Boltzmann;
using namespace arma;

int main() {
//  Structure:
//      Unit:       These units include Hidden and Visible units
//      Layer:      Layers contain units
//      Network:    Contains layers
    arma_rng::set_seed_random();
    mat A = randu<mat>(1,5);
    mat B = randu<mat>(1,5);

    cout << A*10 << endl;
    
//    Machine* mp = new Machine (10,5);
//    mp->emplaceRandomVisibleLayer();
//    mp->displayMachineState();
//    auto b = BoltzmannDistribution(1);
//    mp->backPropagationTuning(.2, b, 100, true, .1, 25);
}

class timer {
private:
    unsigned long begTime;
public:
    void start() {
        begTime = clock();
    }
    
    unsigned long elapsedTime() {
        return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
    }
    
    bool isTimeout(unsigned long seconds) {
        return seconds >= elapsedTime();
    }
};