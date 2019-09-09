//
//  Beer.hpp
//  cpp playground
//
//  Created by Unrein, Craig on 3/19/19.
//  Copyright © 2019 Unrein, Craig. All rights reserved.
//

#pragma once
#ifndef Beer_hpp
#define Beer_hpp

#include <stdio.h>
#include <string>

enum class BeerType {
    BLONDE = 0b001,
    IPA = 0b010,
    LAGER = 0b100,
};

class Beer {
private:
    BeerType type;
    std::string beerName;
public:
    Beer() = default;
    Beer(BeerType type);
    Beer(std::string name, BeerType type);
    BeerType getType() const;
    void setType(BeerType type);
    std::string getName() const;
};

#endif /* Beer_hpp */
