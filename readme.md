

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
    