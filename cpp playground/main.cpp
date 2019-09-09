//
//  main.cpp
//  cpp playground
//
//  Created by Unrein, Craig on 3/19/19.
//  Copyright © 2019 Unrein, Craig. All rights reserved.
//

#include <iostream>
#include "redBlackTree.hpp"
#include "Beer.hpp"

using std::string;
using std::cout;

string beerTypeToString(BeerType beerType)
{
    switch (beerType)
    {
        case BeerType::IPA : return string("IPA");
        case BeerType::LAGER: return string("Lager");
        case BeerType::BLONDE: return string("Blonde");
            // omit default case to trigger compiler warning for missing cases
    };
    return std::to_string(static_cast<int>(beerType));
}

int main(int argc, const char * argv[]) {
    Beer b("Hazy", BeerType::IPA);
    cout << b.getName() << " " << beerTypeToString(b.getType()) << std::endl;
    
    redBlackTree<int> rbt;
    rbt.addNode(15);
    rbt.addNode(1);
    rbt.addNode(11);
    rbt.addNode(18);
    rbt.addNode(3);
    rbt.addNode(5);
    rbt.addNode(12);
    rbt.addNode(34);
    rbt.addNode(4);
    rbt.addNode(6);
    rbt.print();
    rbt.removeNode(34);
    rbt.print();
    
    auto rbtString = make_unique<redBlackTree<string>>();
    rbtString->addNode(string("test"));
    rbtString->addNode(string("testing"));
    rbtString->addNode(string("google"));
    rbtString->addNode(string("amazon"));
    rbtString->addNode(string("microsoft"));
    rbtString->addNode(string("sun"));
    rbtString->addNode(string("oracle"));
    rbtString->addNode(string("spring"));
    rbtString->addNode(string("corral"));
    rbtString->addNode(string("brazil"));
    rbtString->print();
    rbtString->removeNode(string("test"));
    rbtString->removeNode(string("testing"));
    rbtString->print();

    return 0;
}
