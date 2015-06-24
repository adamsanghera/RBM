//
//  Matrix.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/18/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Matrix.h"

/*  *       *       *       *       *       *       *       *       *       *       *       *       *       *       *
    Constructors for the Boltzmann::Matrix class.
    1.  Takes inputs lowerLayerSize and higherLayerSize.  Creates a matrix that is (lowerLayerSize, higherLayerSize).  Fills the vectors with random weights by calling the randomizeWeights() method.
    2.  Takes two input vectors and makes a matrix of weights that is the outer product of <first, second>.  Takes a learningRate and takes a scalar multiplication of this learningRate and the result of the outerProduct.
 */

Boltzmann::Matrix::Matrix(size_t lowerLayerSize, size_t higherLayerSize)
    :   sizeOfHigherLayer(higherLayerSize),
        sizeOfLowerLayer(lowerLayerSize),
        weights(std::vector<std::vector<double>>(lowerLayerSize, std::vector<double>(higherLayerSize)))
    {
        randomizeWeights();
}

Boltzmann::Matrix::Matrix(std::vector<int> lower, std::vector<int> higher, double learningRate)
    :   sizeOfHigherLayer(higher.size()),
        sizeOfLowerLayer(lower.size()),
        weights(std::vector<std::vector<double>>(sizeOfLowerLayer, std::vector<double>(sizeOfHigherLayer)))
    {
        for (int i = 0; i < sizeOfLowerLayer; ++i)
            for (int j = 0; j < sizeOfHigherLayer; ++j)
                weights[i][j] = lower[i] * higher[j] * learningRate;
}

/*  *       *       *       *       *       *       *       *       *       *       *       *       *       *       *
    A method to randomize the weights contained within the Matrix to a value between -1 and 1
 */

void Boltzmann::Matrix::randomizeWeights() {
    srand(time(nullptr));
    for (int i = 0; i < weights.size(); ++i)
    for (int j = 0; j < weights[i].size(); ++j) {
        double out = rand() % (1000);
        double realOut = out / 1000;
        weights[i][j] = realOut;
        int test = out;
        if ( test % 2 == 0 )
            weights[i][j] *= -1;
    }
}

// Subtracts the weights of rhs from the weights of this.  Returns this

Boltzmann::Matrix& Boltzmann::Matrix::operator-=(const Boltzmann::Matrix& rhs) {
    if (sizeOfLowerLayer == rhs.sizeOfLowerLayer && sizeOfHigherLayer == rhs.sizeOfHigherLayer)
        for (int i = 0; i < weights.size(); ++i)
            for (int j = 0; j < weights[i].size(); ++j)
                weights[i][j] -= rhs.weights[i][j];
    else std::cerr << "You cannot compare matrices of different dimensions.";
    return *this;
}

// Copies all of the fields of the rhs to this.  Returns this.

Boltzmann::Matrix& Boltzmann::Matrix::operator=(const Boltzmann::Matrix& rhs) {
    if (this == &rhs) return *this;
    sizeOfHigherLayer = rhs.sizeOfHigherLayer;
    sizeOfLowerLayer = rhs.sizeOfLowerLayer;
    weights = rhs.weights;
    return *this;
}

Boltzmann::Matrix Boltzmann::Matrix::operator+(const Matrix& rhs) {
    return Matrix(*this) +=rhs;
}

Boltzmann::Matrix& Boltzmann::Matrix::operator+=(const Matrix& rhs) {
    if (sizeOfLowerLayer == rhs.sizeOfLowerLayer && sizeOfHigherLayer == rhs.sizeOfHigherLayer)
        for (int i = 0; i < weights.size(); ++i)
            for (int j = 0; j < weights[i].size(); ++j)
                weights[i][j] += rhs.weights[i][j];
    else std::cerr << "You cannot compare matrices of different dimensions.";
    return *this;
}

// Uses the operator -= to return a copy of a subtracted Matrix.

Boltzmann::Matrix Boltzmann::Matrix::operator-(const Boltzmann::Matrix& rhs) {
    return Matrix(*this) -=rhs;
}