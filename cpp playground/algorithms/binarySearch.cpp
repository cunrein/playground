//
//  binarySearch.cpp
//  cpp playground
//
//  Created by Unrein, Craig on 3/21/19.
//  Copyright © 2019 Unrein, Craig. All rights reserved.
//

#include <vector>
#include "binarySearch.hpp"

using std::vector;

// recursive
// 1 2 .. n/2-1 n/2 n/2+1 .. n -1 n
// look in n/2 position
// if a[n/2]<a[n/2-1] then only look at the left half 1 .. n/2 - 1 to look for a peak
// else if a[n/2] < a[n/2 +1] then look at the right half n/2 + 1 .. n
// else a[n/2] is a peek

int findPeek(vector<int>& list) {
    size_t middle = list.size()/2;
    if(list[middle] < list[middle - 1]) {
        // search the left side.
        vector<int> v = vector<int>(begin(list), begin(list) + (middle - 1));
        return findPeek(v);
    } else if (list[middle] < list[middle + 1]) {
        // search the right side
        vector<int> v = vector<int>(begin(list), begin(list) + (middle - 1));
        return findPeek(v);
    } else
        return list[middle];
    
}
