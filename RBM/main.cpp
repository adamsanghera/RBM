//
//  main.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Network.h"
#include "SimilarityTester.h"

class timer;

using namespace std;
using namespace Boltzmann;

int main() {
    BoltzmannDistribution bd0(1);
    
    //  These tests should print out a bunch of 1's
    
    //  Unit Test Space
        cout << "Unit test: ";
        Unit* a = new Unit(true);
        Unit* b = new Unit(false);
        cout << (a->pingState() == true);
        cout << (b->pingState() == false);
        a->ping(100000, bd0);
        cout << (a->pingState() == true);
        delete a;
        delete b;

    //  Layer Test Space
        cout << endl << "Layer test: ";
        Layer* c = new Layer(10);
        Layer* d = new Layer(*c);
        cout << !(c == d);
        cout << (c->getStates().size() == 10);
        cout << (d->getStates().size() == 10);
        c->clampStateOfUnit(0, !c->getStates()[0]);
        cout << !(c->getStates()[0] == d->getStates()[0]);
        c->clampStateOfUnits(d->getStates());
        cout << (c->getStates()[0] == d->getStates()[0]);
        cout << (c->ping(0, 1000, bd0) == true);
        delete c;
        delete d;
    
    //  Matrix Test Space
        cout << endl << "Matrix test: ";
        Matrix* e = new Matrix(2,3);
        vector <int> i = {1,0,0};
        vector <int> j = {0,1};
        Matrix* f = new Matrix(j, i, .5);
        Matrix* g = new Matrix(2,3);
        cout << (f->getWeight(1,0) == .5);
        f->adjustWeight(1, 0, 0.0);
        cout << (f->getWeight(1,0) == 0.0);
        double aaaa = g->getWeight(0, 0);
        *g -= *e;
        *g += *e;
        cout << (aaaa == g->getWeight(0, 0));
        *g = *g - *e;
        *g = *g + *e;
        cout << (aaaa == g->getWeight(0, 0));
        *g *= 5;
        cout << (aaaa*5 == g->getWeight(0, 0));
        delete e;
        delete f;
        delete g;
        for (int i = 0; i < 1000000; ++i) {
            Matrix* testMat = new Matrix(1,0);
            delete testMat;
        }
    
    //  Machine Test Space
        Machine* h = new Machine(4,20);
        delete h;

    //  Network Test Space
        Network* n = new Network(10);
        delete n;
//    std::vector<double> tests;
//    std::vector<double> testTimes;
//    timer t;
//    for (int i = 0; i < 10; ++i) {
//        t.start();
//        Boltzmann::Network n(324, 500);
//        n.pushLayer(500);
//        n.pushLayer(2000);
//        n.swapWithRandomInput();
//        std::string start = n.extractVisibleLayerAsString();
//        
//        n.iterateLearnCycle(.3, 3);
//        n.generateInput();
//        std::string finish = n.extractVisibleLayerAsString();
//        
//        SimilarityTester st(start, finish);
//        std::cout << st.test() << "\n";
//        tests.push_back(st.test());
//        testTimes.push_back(t.elapsedTime());
//    }
//    for (int i = 0; i < tests.size(); ++i) {
//        std::cout << tests[i] << "\n";
//    }
//    for (int i = 0; i < testTimes.size(); ++i) {
//        std::cout << testTimes[i] << "\n";
//    }
    std::cout << endl << "Ha!\n";
    //  Structure:
    //      Unit:       These units include Hidden and Visible units
    //      Layer:      Layers contain units
    //      Network:    Contains layers
    //  How do we handle edges?  Stochastic stuff?
    //  When we're back-propagating, what level should that be at?  Presumably layer.
    //  Should layers have links to other layers?  -- Probably not
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