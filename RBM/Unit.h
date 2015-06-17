//
//  Unit.h
//  RBM
//
//  Created by Adam Sanghera on 6/17/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__Unit__
#define __RBM__Unit__

#include <stdio.h>

namespace Boltzmann {
    class Unit {
    public:
        Unit();
        virtual bool ping() const = 0;
    private:
        
    };
}

#endif /* defined(__RBM__Unit__) */
