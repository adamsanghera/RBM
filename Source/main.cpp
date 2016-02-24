//
//  main.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Network.h"
#include "SimilarityTester.h"
#include "Matrix.h"
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
    mat armaMat = mat::fixed<10, 5>(fill::randu);
    cout << armaMat << endl;
    Matrix myMat(10, 5);
    myMat.randomizeWeights();
    cout << endl;
    myMat.printWeight();
    
    rowvec bottomLayerRV = {1,1,1,0,1,1,0};
    colvec topLayerCV = {0,1,0,1,1,1,1};
    double learnRate = 2.0;
    armaMat = (kron(bottomLayerRV, topLayerCV) * learnRate).t(); // NOTES: We end up needing to tranpose the armaMat to match the inner product, regardless of the ordering of the lower and upper states in the kron function.  This is a significant result.  This has been fixed in the code.
    
    std::vector<int> lowerLayerStates = {1,1,1,0,1,1,0};
    std::vector<int> upperLayerStates = {0,1,0,1,1,1,1};
    learnRate = 2.0;
    myMat = Matrix(lowerLayerStates, upperLayerStates, learnRate);
    
    cout << armaMat << endl;
    myMat.printWeight();
    
    cout << endl;
    
    Matrix mySecondMat = Matrix(myMat);
    mat armaSecondMat = mat(armaMat);
    
    mySecondMat.printWeight();
    cout << endl << armaSecondMat << endl;
    
    bool f = true;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if (armaMat(i,j) != myMat.getWeight(i, j))
                f = false;
        }
    }
    cout << "ArmaMat = myMat: " << f << endl;
    
    
    
//    //  Constructors
//    Matrix(size_t lowerLayerSize, size_t higherLayerSize);
//    Matrix(std::vector<int> lower, std::vector<int> higher, double learningRate);
//    Matrix(const Matrix& rhs);
//    
//    //  Misc. Methods
//    void randomizeWeights();
//    double getWeight(size_t lowerUnitIndex, size_t higherUnitIndex) const;
//    void adjustWeight(size_t lowerUnitIndex, size_t higherUnitIndex, double newWeight);
//    
//    //  Arithmetic Operators
//    Matrix& operator+=(const Matrix& rhs);
//    Matrix& operator-=(const Matrix& rhs);
//    Matrix& operator*=(const double rhs);
//    Matrix operator+(const Matrix& rhs);
//    Matrix operator-(const Matrix& rhs);
//    Matrix operator*(const double rhs);
//    
//    //  Assignment Operator
//    Matrix& operator=(const Matrix& rhs);
//    
//    Constructor Equivalents:
//    mat::fixed<lower, higher>;
//    kron(mat a, mat b) in conjunction with operator*(learningRate)
//    copy constructor
//    
//    Misc. Equivalencies:
//    randu<mat>(size, size)
//    mat.operator()(size_t, size_t)
//    same as aboce, just assign a value.
//    
//    Arithmetic Operators:
//    All handled.


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
//    
//    cout << "Testing Matrix multiplication" << endl;
//    
//    Network* n = new Network(8, 3);
//    n->swapWithRandomInput();
//    n->printNetwork();
//    n->iterateLearnCycle(.99, 5);
//    
//    n->printNetwork();
//    
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