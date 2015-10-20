//
//  SimilarityTester.h
//  RBM
//
//  Created by Adam Sanghera on 6/24/15.
//  Copyright (c) 2015 adamSanghera. All rights reserved.
//

#ifndef __RBM__SimilarityTester__
#define __RBM__SimilarityTester__

#include <stdio.h>
#include <string>

class SimilarityTester {
public:
    SimilarityTester(const std::string& one, const std::string& two): one(one), two(two) {}
    double test() {
        if (one.length() != two.length()) {
            return 0.0;
        }
        double tally = 0.0;
        for (int i = 0; i < one.length(); ++i) {
            if (one.at(i) == two.at(i)) {
                tally++;
            }
        }
        return tally / one.length();
    }
private:
    std::string one, two;
};

#endif /* defined(__RBM__SimilarityTester__) */