
Restricted Boltzmann Machine


Redesign Proposal

Objective:  To broaden the computational complexity of the RBM, with the effect of allowing for different types of layers and passes.

Motivation: 
1.  We can't use softmax layers right now.
2.  The current project architecture is hostile towards multiple layer types.
3.  Having a more extensible architecture would allow for the addition of future layers.

Implementation Table of Contents:

I.  Classes to modify
A.  Machine

Implementation:

I.A.  Machine
+   A parameter, probably a _string_ or _index_, which will determine the type of machine
*   Here, the word 'type' is describing the relationship between the machine's layers
*   An example type would be "softmax" or "stochastic"
*   Essentially, this type will determine how forward passes, backward passes, and loss is calculated

->  All methods which would now be considered "type-specific" will be consolidated into singular methods whose functions vary with type, e.g. forwardPass(), backwardPass()
->  We should consolidate stochasticUpPass and stochasticDownPass into a single method, taking a variable of bool 'up'



Redesign Proposal -- Feb. 4 2016

Objective:  To improve the computational efficiency of all Matrix operations, with the effect of improving runtime and scalability.

Motivation:
1.  Using a standardized library more professional.
2.  Making use of a standard LA Library would delegate responsibility of matrices to a trusted third party
3.  Matrix calculations would be faster, reliable, and consistent.

Implementation:

+   I investigated Trilinos, and have their libraries installed.  However, their library is highly complex, and therefore beyond the scope of what's required.  Potentially, we can add support later.
+   I'll try implementing Armadillo.


These are the methods that need to be replaced:

//  Constructors
Matrix(size_t lowerLayerSize, size_t higherLayerSize);
Matrix(std::vector<int> lower, std::vector<int> higher, double learningRate);
Matrix(const Matrix& rhs);

//  Misc. Methods
void randomizeWeights();
double getWeight(size_t lowerUnitIndex, size_t higherUnitIndex) const;
void adjustWeight(size_t lowerUnitIndex, size_t higherUnitIndex, double newWeight);

//  Arithmetic Operators
Matrix& operator+=(const Matrix& rhs);
Matrix& operator-=(const Matrix& rhs);
Matrix& operator*=(const double rhs);
Matrix operator+(const Matrix& rhs);
Matrix operator-(const Matrix& rhs);
Matrix operator*(const double rhs);

//  Assignment Operator
Matrix& operator=(const Matrix& rhs);

Constructor Equivalents:
    mat::fixed<lower, higher>;
    kron(mat a, mat b) in conjunction with operator*(learningRate)
    copy constructor

Misc. Equivalencies:
    randu<mat>(size, size)
    mat.operator()(size_t, size_t)
    same as aboce, just assign a value.

Arithmetic Operators:
    All handled.

I really to standardize upper layer vs lower layer.  I'm using variations of upper/lower and hidden/visible.
    Which one should we go with?
Qualities of upper/lower 
    +   Less specific to RBM's.
    +   More visual/intuitive, less hand-wavey
Qualities of hidden/visible
    +   Follows the proper nomenclature of Hinton's papers.
    -   Less intuitive to users unfamiliar with Hinton's papers...
    -   Further, abstracted to network scale, using hidden layer is inaccurate.


Based on this list of pros and cons, I'm going to go with upper/lower.


I'm unsure about using bool's as the lowest-level state unit within the layer class.
    It is undoubtedly more memory-efficient than using an int, but the conversion overhead is a pain.
    Maybe I should look up how to statically-allocate bit-size???? I'm sure it's possible
--> In the meantime, switch to integers

So I managed to get the library to build, having made all the adequate changes, but I'm scared.  I want to step through and make sure that everything is reasonable before I delete the matrix class
Particular Concerns:
    --> In the Matrix class, I know how the inner product was calculated, and the size of the resulting matrix.
        ++ I want to make sure that kron creates the result I'm anticipating i.e. not the transpose matrix or smth weird like that

Things I want to implement:
Snapshots: 
    load network from a file.
    Save network to a file.
Templates:
    Save network structure to a file.
    Load network structures from a file.

How do we want the file to be structured?
    --> a series of layers.

Just made a makefile that works!!! Yay! -- Feb. 11

