//
//  Matrix.h
//  RBM
//
//  Created by Adam Sanghera on 6/18/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__Matrix__
#define __RBM__Matrix__

#include <stdio.h>
#include <vector>
#include <random>
#include <math.h>
#include <time.h>
#include <iostream>

namespace Boltzmann {
    class Matrix {
    public:
        Matrix(size_t lowerLayerSize, size_t higherLayerSize);
        Matrix(std::vector<int> lower, std::vector<int> higher, double learningRate);
        void randomizeWeights();
        
        double getWeight(size_t lowerUnitIndex, size_t higherUnitIndex) const { return weights[lowerUnitIndex][higherUnitIndex]; }
        void adjustWeight(size_t lowerUnitIndex, size_t higherUnitIndex, double newWeight) { weights[lowerUnitIndex][higherUnitIndex]=newWeight;}
        
        Matrix& operator-=(const Matrix& rhs);
        Matrix operator-(const Matrix& rhs);
        Matrix& operator=(const Matrix& rhs);
    private:
        size_t sizeOfHigherLayer, sizeOfLowerLayer;
        std::vector<std::vector<double>> weights;
    };
}

#endif /* defined(__RBM__Matrix__) */
