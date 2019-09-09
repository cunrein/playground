//
//  Beer.cpp
//  cpp playground
//
//  Created by Unrein, Craig on 3/19/19.
//  Copyright © 2019 Unrein, Craig. All rights reserved.
//

#include "Beer.hpp"

using std::string;

Beer::Beer(BeerType type):type(type) {};
Beer::Beer(string name, BeerType type):beerName(name), type(type) {};

BeerType Beer::getType() const {
    return this->type;
};

void Beer::setType(BeerType type){
    this->type = type;
};

string Beer::getName() const {
    return this->beerName;
}
