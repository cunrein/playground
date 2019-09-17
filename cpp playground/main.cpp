//
//  main.cpp
//  cpp playground
//
//  Created by Unrein, Craig on 3/19/19.
//  Copyright © 2019 Unrein, Craig. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "redBlackTree.hpp"
#include "Beer.hpp"
#include <math.h>

using std::string;
using std::cout;
using std::vector;

char getNewColor(char, char);
bool allSameColor(vector<char>);

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

vector<char> lineOfQuxes(vector<char> quxes) {
    if (quxes.size() < 1) {
        return quxes;
    }
    vector<char> line = vector<char>(quxes);
    vector<char> out = {};
    while(!allSameColor(out) && line.size() > 1) {
        char a = line[line.size() - 1];
        line.pop_back();
        char b = line[line.size() - 1];
        line.pop_back();
        if (a == b) {
            line.push_back(a);
            line.push_back(b);
        } else {
            char c = getNewColor(a, b);
            out.push_back(c);
        }
    }
    return out;
};

bool allSameColor(vector<char> quxes) {
    if (quxes.size() < 2) {
        return true;
    }
    char color = quxes[0];
    for (char c : quxes) {
        if (c != color)
            return false;
    }
    return true;
};

char getNewColor(char a, char b) {
    if(a == b) {
        return a;
    } else if (a == 'B' && b == 'G') {
        return 'R';
    } else if (a == 'G' && b == 'B') {
        return 'R';
    } else if (a == 'R' && b == 'B') {
        return 'G';
    } else if (a == 'B' && b == 'R') {
        return 'G';
    } else if (a == 'G' && b == 'R') {
        return 'B';
    } else if (a == 'R' && b == 'G') {
        return 'B';
    }
    
    return ' ';
};

size_t findTarget(vector<int>& list, int target, bool left) {
    size_t lo = 0;
    size_t hi = list.size();
    
    while(lo < hi) {
        size_t middle = (lo + hi)/2;
        if(list[middle] > target || (left && list[middle] == target)) {
            hi = middle;
        } else {
            lo = middle + 1;
        }
    }
    return lo;
};

vector<int> searchRange(vector<int>& nums, int target) {
    if (nums.size() == 0)
        return {-1, -1};
    int left = findTarget(nums, target, true);
    if (left > nums.size() || nums[left] != target)
        return {-1,-1};
    int right = findTarget(nums, target, false) - 1;
    
    return {left, right};
}

//   Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void printListNode(ListNode* list) {
    if(list) {
        printListNode(list->next);
        cout << list->val;
    }
}

long long buildValueHelper(ListNode* list, int step) {
    if (list) {
        auto mask = pow(10, step);
        auto val = list->val * mask;
        return val + buildValueHelper(list->next, step + 1);
    }
    return 0;
}

long long buildValue(ListNode* list) {
    return buildValueHelper(list, 0);
}

ListNode* cascadeOne(ListNode* l) {
    if (l) {
        auto out = l->val + 1;
        l->val = out % 10;
        if (out > 9) {
            l->next = cascadeOne(l->next);
        }
        return l;
    }
    return new ListNode(1);
};

ListNode* addTwoNumbersHelper(ListNode* l1, ListNode* l2, bool addOne) {
    if(l1 && l2) {
        auto out = l1->val + l2->val;
        out = addOne ? out + 1 : out;
        ListNode* retv = new ListNode(out % 10);
        if (out > 9)
            retv->next = addTwoNumbersHelper(l1->next, l2->next, true);
        else
            retv->next = addTwoNumbersHelper(l1->next, l2->next, false);
        return retv;
    } else if (l1 && !l2) {
        if (addOne) {
            return cascadeOne(l1);
        }
        return l1;
    } else if (!l1 && l2) {
        if (addOne) {
            return cascadeOne(l2);
        }
        return l2;
    } else if (!l1 && !l2 && addOne) {
        return new ListNode(1);
    }
    return NULL;
};

ListNode* addTwoNumbers2(ListNode* l1, ListNode* l2) {
    return addTwoNumbersHelper(l1, l2, false);
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    auto v1 = buildValue(l1);
    auto v2 = buildValue(l2);
    cout << v1 << " " << v2;
    auto sum = to_string(v1 + v2);

    ListNode* retv = NULL;
    for(char c : sum) {
        int nodeValue = c - '0';
        ListNode* current = new ListNode(nodeValue);
        current->next = retv;
        retv = current;
    };
    
    return retv;
};

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


//    ListNode* n1 = new ListNode(2);
//    ListNode* n2 = new ListNode(4);
//    ListNode* n3 = new ListNode(3);
//    n2->next = n3;
//    n1->next = n2;
//
//    ListNode* m1 = new ListNode(5);
//    ListNode* m2 = new ListNode(6);
//    ListNode* m3 = new ListNode(4);
//    m2->next = m3;
//    m1->next = m2;
//    printListNode(n1);
//    cout << "\n";
//    printListNode(m1);
//    cout << "\n";
//    ListNode* out = addTwoNumbers2(n1, m1);
//    printListNode(out);
//    cout << "\n";
    
    ListNode* x1 = new ListNode(9);
    x1->next = new ListNode(8);
    ListNode* y = new ListNode(1);
    ListNode* out = addTwoNumbers2(x1, y);
    printListNode(out);
    cout << endl;
    
    //vector<int> searchList = {1, 2, 3, 4, 5, 6, 6, 6, 6, 7, 8, 9, 10, 11, 12};
    //vector<int> searchList = {5, 7, 7, 8, 8, 10};
    vector<int> searchList = {2, 2};
    auto r = searchRange(searchList, 6);
    
    cout << "[" << r[0] << ", " << r[1] << "]" << endl;
    
    return 0;
}
