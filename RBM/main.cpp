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
    Matrix a(2,3);
    
    
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
    std::cout << "Ha!\n";
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