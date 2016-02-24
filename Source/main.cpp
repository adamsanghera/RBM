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

//    cout << "Testing for memory Leaks" << endl;
//    
//    cout << "Testing Machine class" << endl;
//    for (int i = 0; i < 100; ++i) {
//        Machine* m = new Machine(1000,1000);
//        delete m;
//    }
//    cout << "Testing Unit class" << endl;
//    for (int i = 0; i < 100; ++i) {
//        Unit* u = new Unit(true);
//        delete u;
//    }
//    cout << "Testing Network class" << endl;
//    for (int i = 0; i < 100; ++i) {
//        Network* n = new Network(1000,2000);
//        delete n;
//    }
//    cout << "Testing Layer class" << endl;
//    for (int i = 0; i < 10000; ++i) {
//        Layer* l = new Layer(1000);
//        delete l;
//    }
    
    cout << "Testing Matrix multiplication" << endl;
    
    Network* n = new Network(8, 3);
    n->swapWithRandomInput();
    n->printNetwork();
    n->iterateLearnCycle(.99, 5);
    
    n->printNetwork();
    
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