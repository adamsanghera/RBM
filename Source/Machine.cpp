//
//  Machine.cpp
//  RBM
//
//  Created by Adam Sanghera on 6/22/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#include "Machine.h"

//  Machine Constructor A
//      Inputs: sizeOfBase, sizeOfTop
//  Constructs a Machine with a visible layer of size sizeOfBase and a hidden layer of size sizeOfTop
//      Constructs a Matrix to manage the weights between these two layers, again using the sizeOf arguments.

    Boltzmann::Machine::Machine(size_t sizeOfBase, size_t sizeOfTop)
    :   visibleLayer(new Layer(sizeOfBase)),
        hiddenLayer(new Layer(sizeOfTop)),
        weights(sizeOfBase, sizeOfTop),
        visSize(sizeOfBase),
        hiddenSize(sizeOfTop) {}

//  Machine Constructor B
//  Uses pointers to two Layers to construct a Machine
//  This approach is useful when we want to use specific layers that ALREADY EXIST to compose the machine.
//      e.g. you want the hidden layer of another machine to be the visible layer of *this* machine.
//  Generates a new weihts matrix in the same way as Constructor A

    Boltzmann::Machine::Machine(Boltzmann::Layer* const vis, Boltzmann::Layer* const hid)
    :   visibleLayer(vis),
        hiddenLayer(hid),
        weights(vis->numUnits, hid->numUnits),
        visSize(vis->numUnits),
        hiddenSize(hid->numUnits)
        {}

//  Boltzmann::Machine::stochasticUpPass
//      Uses a BoltzmannDistribution (essentially a t-value) to perform a stochastic-up-pass through the machine.
//  Follows the following pseudo-code process:
//      1.  Tallies up the total energy-differential of a given hidden unit's power state by iterating through the unit's weight vector.
//      2.  Pings the given hidden unit with its respective, total energy differential.
//  This method uses the data given in the visible layer and the weights contained in the weights matrix as the inputs to a non-linear function
//      with the purpose of generating output data into the hidden layer which reflects certain characteristics of the visible layer.

    void Boltzmann::Machine::stochasticUpPass(Boltzmann::BoltzmannDistribution& bd) {
        double diff = 0.0;
        std::vector<int> origInputs = visibleLayer->getStates();
        for (int i = 0; i < hiddenSize; ++i) {
            for (int j = 0; j < weights.sizeOfLowerLayer; ++j)
                diff += weights.getWeight(j, i) * origInputs[j];
            hiddenLayer->ping(i, diff, bd);
            diff = 0.0;
        }
    }

//  Boltzmann::Machine::stochasticDownPass
//      Uses a Boltzmann Distribution (effectively a t-value) to perform a stochastic-down-pass through the machine.
//  Follows the following pseudo-code process:
//      1.  Tallies up the total energy-differential of a given visible unit's power state by iterating through the unit's weight vector.
//      2.  Pings the given visible unit with its respective, total energy differential.
//  This method uses the states of the hidden units and the weights contained within the weights matrix as inputs to a non-linear transformation
//      with the purpose of generating an imaginary input which has been fantasized by the machine.

    void Boltzmann::Machine::stochasticDownPass(Boltzmann::BoltzmannDistribution& bd) {
        double diff = 0.0;
        for (int i = 0; i < visSize; ++i) {
            for (int j = 0; j < weights.sizeOfHigherLayer; ++j)
                diff += weights.getWeight(i, j) * hiddenLayer->listOfUnits[j]->pingState();
            visibleLayer->ping(i, diff, bd);
            diff = 0.0;
        }
    }

//  Boltzmann::Machine::deterministicUpPass
//      This method is the stripped-down cousin of stochasticUpPass
//  Follows the following pseudo-code:
//      1.  Tallies the sum total energy-differential of each hidden unit's power state by iterating through the units' respective weight vectors
//      2.  Clamps the states of the hidden layer units based on the differential.
//          2.a.    If the differential is higher than zero, clamp to true.
//          2.b.    If the differential is lower than or equal to zero, clamp to false.
//
//  This method is used to very quickly/cheaply generate a hidden layer relying only on the states of the visibles and their respective weights.
//      This is a purely linear transformation, and involves neither Boltzmann Distributions nor Stochastic Generations.

    void Boltzmann::Machine::determinsticUpPass() {
        double diff = 0.0;
        for (int i = 0; i < hiddenSize; ++i) {
            for (int j = 0; j < weights.sizeOfLowerLayer; ++j)
                diff += weights.getWeight(j, i) * visibleLayer->listOfUnits[j]->pingState();
            if (diff > 0)
                hiddenLayer->clampStateOfUnit(i, true);
            else
                hiddenLayer->clampStateOfUnit(i, false);
            diff = 0.0;
        }
    }

//  Boltzmann::Machine::adjustWeights
//      Adjusts the weights of the network to reflect the current state of the Machine
//  This method works by:
//      1.  Collecting the states of the visible and hidden layers.
//      2.  Creating a special type of weights Matrix which transforms the data on construction.
//      3.  This matrix takes the outer product of the unit states and multiplies the result by a learning constant, learnRate.
//      4.  The weights of the machine are then either incremented or decremented, depending on the state of the 'increment' switch.
//
//  ***Essential component of the learning process.***
//      Iff V1 and H2 are both on when this method is called, the weight V1-H2 will be incremented by learnRate if increment is true
//      Iff V1 and H2 are both on when this method is called, the weight V1-H2 will be decremented by learnRate if increment is false
//
//  This method is called extensively in the Boltzmann::Machine::iterateLearning method.

    void Boltzmann::Machine::adjustWeights(bool increment, double learnRate) {
        Matrix gates(visibleLayer->getStates(), hiddenLayer->getStates(), learnRate);   // Calculates inner product v^t*h
        if (increment)
            weights += gates;
        else
            weights -= gates;
    }

//  Boltzmann::Machine::iterateLearning
//      This method makes the machine learn the input vector.
//  While this method *does* modify the pre-learning input vector, the machine preserves this vector and restores it at the culmination of
//      each learning cycle.
//  This method calls the following methods a number of times equal to numberOfExchanges:
//      1.  stochasticUpPass / softMaxDeterministicUpPass
//      2.  adjustWeights (increment)
//      3.  stochasticDownPass
//      4.  deterministicUpPass
//      5.  adjustWeights (decrement)
//
//  Pseudo:
//      1.  Generates a hidden layer configuration and reinforces this configuration's weights
//      2.  Generates a fantasy visible layer configuration.
//      3.  Generates a final hidden layer configuration (deterministically) from this visible layer fantasy and punishes the weights
//              corresponding to this config.

    void Boltzmann::Machine::backPropagationTuning(double learnRate, Boltzmann::BoltzmannDistribution& bd, size_t numberOfExchanges, bool softMax, double decayRate, unsigned decayStep) {
        double decay = 1.0; unsigned counter = 0;
        std::vector<int> origInputs = visibleLayer->getStates();
        for (int i = 0; i < numberOfExchanges; ++i, ++counter) {
            if (counter >= decayStep)
                decay *= decay;
//            std::cout << "Learning: " << i << std::endl;        // Debug
            origInputs = visibleLayer->getStates();
            std::cout << "Init:\n";
        displayMachineState();
            
            if (softMax)
                softMaxDeterministicUpPass();                   //  1.
            else
                stochasticUpPass(bd);                           //  1.
            adjustWeights(true, learnRate*decay);               //  2.

            std::cout << "Hiddens mapped, connections incremented:\n";
        displayMachineState();
            
            stochasticDownPass(bd);                             //  3.
            std::cout << "Visibles generated, connections unchanged\n";
            
            if (softMax)
                softMaxDeterministicUpPass();
            else
                determinsticUpPass();                           //  4.
            adjustWeights(false, learnRate*decay);              //  5.
            
            std::cout << "Hiddens mapped from fantasy visibles, connections decremented:\n";
        displayMachineState();
            
            visibleLayer->clampStateOfUnits(origInputs);
        }
    }

//  Boltzmann::Machine::replaceVisibleLayer
//      This method replaces the current visible player with a vector of bool inputs.
//  Used to adjust the input vector

    void Boltzmann::Machine::replaceVisibleLayer(std::vector<bool> inputs) {
        for (int i = 0; i < inputs.size(); ++i)
            visibleLayer->clampStateOfUnit(i, inputs[i]);
    }

//  Boltzmann::Machine Destructor
//      deletes the visible and hidden layers and sets them to nullptr (if they aren't already nullptr's)

    Boltzmann::Machine::~Machine() {
        if (visibleLayer != nullptr) {
            delete visibleLayer;
            visibleLayer = nullptr;
        }
        if (hiddenLayer != nullptr) {
            delete hiddenLayer;
            hiddenLayer = nullptr;
        }
    }

/* Begin Experimental Section */


//  softMax
//  1.  Do a deterministic up pass, such that the following conditions are satisfied:
//      a.  One and *only* one top-layer node has been activated.
//      b.  This single, activated top-layer-node is the node which has been "most" activated by the input*weights vector.
//  2.  Increment the weights between the lower-level activated nodes and this softmaxed node.
//  3.  Generate a visible layer given the softmaxed-activated node.
//  4.  Do another deterministic up pass, (repeat step 1).
//  5.  Decrement the weights between the lower-level activated nodes and the newly-activated softmaxed node.

    void Boltzmann::Machine::softMaxDeterministicUpPass() {
        double diff = 0.0;
        std::pair<double, unsigned> biggest = std::make_pair(-15.0, 0);
        std::vector<int> origInputs = visibleLayer->getStates();
        for (int i = 0; i < hiddenSize; ++i) {
            for (int j = 0; j < weights.sizeOfLowerLayer; ++j)
                diff += weights.getWeight(j, i) * origInputs[j];
            if (diff > biggest.first) {
                biggest.first = diff;
                biggest.second = i;
            }
            hiddenLayer->clampStateOfUnit(i, false);
            diff = 0.0;
        }
        hiddenLayer->clampStateOfUnit(biggest.second, true);
    }

    void Boltzmann::Machine::displayMachineState() {
        std::cout << "\t";
        for (int i = 0; i < hiddenSize; ++i) {
            std::cout << "h" << i%10;
            if (hiddenLayer->listOfUnits[i]->pingState())
                std::cout << "T\t";
            else
                std::cout << "F\t";
        }
        std::cout << std::endl;
        for (int j = 0; j < visSize; ++j) {
            std::cout << "v" << j%10;
            if (visibleLayer->listOfUnits[j]->pingState())
                std::cout << "T\t";
            else
                std::cout << "F\t";
            for (int k = 0; k < hiddenSize; ++k) {
                double z = weights.getWeight(j, k);
                if (z >= .35)
                    std::cout << "+\t";
                else if (z >= -.35)
                    std::cout << "*\t";
                else
                    std::cout << "-\t";
            }
            std::cout << std::endl;
        }
        //Lower1 Higher1  Higher2  Higher3
        //Lower2 Higher1  Higher2  Higher3
        //Lower3 Higher1  Higher2  Higher3
        //Lower4 Higher1  Higher2  Higher3
    }

    void Boltzmann::Machine::emplaceRandomVisibleLayer() {
        std::vector<bool> inputs;
        srand(time(nullptr));
        for (int i = 0; i < visSize; ++i) {
            double out = rand() % 1000;
            double real = out / 1000;
            if (real < .50)
                inputs.push_back(true);
                else
                    inputs.push_back(false);
                    }
        replaceVisibleLayer(inputs);
    }
/* End Experimental Section */