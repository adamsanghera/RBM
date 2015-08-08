//
//  Matrix.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/18/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Matrix.h"

//  Boltzmann::Matrix Constructors
//  1.  Takes inputs lowerLayerSize and higherLayerSize.  Creates a matrix that is (lowerLayerSize, higherLayerSize).
//      -   Fills the vectors with random weights by calling the randomizeWeights() method.
//
//  2.  Takes two input vectors and makes a matrix of weights that is the outer product of <first, second>.
//      -   Takes a learningRate and performs a scalar multiplication of this learningRate and the result of the outerProduct.
//
//  3.  Takes another Matrix as an input
//      -   Steals the other Matrix's weights vector and sizes.
//

    //  1.
    Boltzmann::Matrix::Matrix(size_t lowerLayerSize, size_t higherLayerSize)
        :   sizeOfHigherLayer(higherLayerSize),
            sizeOfLowerLayer(lowerLayerSize),
            weights(std::vector<std::vector<double>>(lowerLayerSize, std::vector<double>(higherLayerSize)))
        {
            randomizeWeights();
    }

    //  2.
    Boltzmann::Matrix::Matrix(std::vector<int> lower, std::vector<int> higher, double learningRate)
        :   sizeOfHigherLayer(higher.size()),
            sizeOfLowerLayer(lower.size()),
            weights(std::vector<std::vector<double>>(sizeOfLowerLayer, std::vector<double>(sizeOfHigherLayer)))
        {
            for (int i = 0; i < sizeOfLowerLayer; ++i)
                for (int j = 0; j < sizeOfHigherLayer; ++j)
                    weights[i][j] = lower[i] * higher[j] * learningRate;
        }

    //  3.
    Boltzmann::Matrix::Matrix(const Boltzmann::Matrix& rhs){
        if (this != &rhs) {
            sizeOfLowerLayer = rhs.sizeOfLowerLayer;
            sizeOfHigherLayer = rhs.sizeOfHigherLayer;
            weights = rhs.weights;
        }
    }

//  Boltzmann::Matrix::randomizeWeights
//      Randomizes all the weights in the weights matrix to a value in the space [-1,1]
//      This method uses the same uniform distribution method as that found in Boltzmann::Unit::ping

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

//  Boltzmann::Matrix Arithmetic-Assignment Operators
//      1.  +=  Takes another Matrix and sums its weights into this Matrix's weight vectors.
//      2.  -=  Takes another Matrix and subtracts its weights from this Matrix's weight vectors.
//      3.  *=  Takes a double value and performs a scalar multiplication on this Matrix's weight vectors.

    //  1
    Boltzmann::Matrix& Boltzmann::Matrix::operator+=(const Matrix& rhs) {
        if (sizeOfLowerLayer == rhs.sizeOfLowerLayer && sizeOfHigherLayer == rhs.sizeOfHigherLayer)
            for (int i = 0; i < weights.size(); ++i)
                for (int j = 0; j < weights[i].size(); ++j)
                    weights[i][j] += rhs.weights[i][j];
        else std::cerr << "You cannot compare matrices of different dimensions.";
        return *this;
    }

    //  2
    Boltzmann::Matrix& Boltzmann::Matrix::operator-=(const Boltzmann::Matrix& rhs) {
        if (sizeOfLowerLayer == rhs.sizeOfLowerLayer && sizeOfHigherLayer == rhs.sizeOfHigherLayer)
            for (int i = 0; i < weights.size(); ++i)
                for (int j = 0; j < weights[i].size(); ++j)
                    weights[i][j] -= rhs.weights[i][j];
        else std::cerr << "You cannot compare matrices of different dimensions.";
        return *this;
    }

    //  3
    Boltzmann::Matrix& Boltzmann::Matrix::operator*=(const double rhs) {
        for (int i = 0; i < weights.size(); ++i)
            for (int j = 0 ; j < weights[i].size(); ++j)
                weights[i][j] *= rhs;
        return *this;
    }

//  Boltzmann::Matrix Assignment Operator
//      Checks for self-assignment.
//      Steals the other matrix's members.
//      Returns this.

    Boltzmann::Matrix& Boltzmann::Matrix::operator=(const Boltzmann::Matrix& rhs) {
        if (this == &rhs) return *this;
        sizeOfLowerLayer = rhs.sizeOfLowerLayer;
        sizeOfHigherLayer = rhs.sizeOfHigherLayer;
        weights = rhs.weights;
        return *this;
    }