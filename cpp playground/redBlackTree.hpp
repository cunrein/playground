//
//  redBlackTree.hpp
//  cpp playground
//
//  Created by Unrein, Craig on 9/4/19.
//  Copyright © 2019 Unrein, Craig. All rights reserved.
//

#ifndef redBlackTree_hpp
#define redBlackTree_hpp

#include <memory>
#include <iostream>

using namespace std;

enum struct color { red, black };

template<typename T>
// requires EqualityComparable<T>
struct node {
    T val;
    color clr;
    shared_ptr<node> up;
    shared_ptr<node> left;
    shared_ptr<node> right;
    node(const T& v, shared_ptr<node> u) : val(v), clr(color::red), up(u), left(nullptr), right(nullptr) { };
};

template<typename T>
// requires EqualityComparable<T>
class redBlackTree {
private:
    
    shared_ptr<node<T>> root;

    // functions
    shared_ptr<node<T>> sibling(shared_ptr<node<T>> n) {
        shared_ptr<node<T>> s = NULL;
        if(n!=root)
            s = (n->up->left == n) ? n->up->right : n->up->left;
        return s;
    };
    
    shared_ptr<node<T>> findNode(const T& v) {
        auto f = root;
        while(f && f->val != v)
            f = (v < f->val) ? f->left : f->right;
        return f;
    };

    shared_ptr<node<T>> walkTree(shared_ptr<node<T>> walker, const T& v) {
        auto prev = walker;
        while(walker) {
            prev = walker;
            walker = (v < walker->val) ? walker->left : walker->right;
        }
        return prev;
    };

    void attachBase(shared_ptr<node<T>> g, shared_ptr<node<T>> cp) {
        cp->up = g->up;
        if (g->up)
            (g->up->left == g) ? g->up->left = cp : g->up->right = cp;
        else
            root = cp;
    };

    shared_ptr<node<T>> inorderSuccessor(shared_ptr<node<T>> ntr) {
        if(ntr->right) {
            ntr = ntr->right;
            while(ntr->left)
                ntr = ntr->left;
        }
        else if(ntr->left)
            ntr = ntr->left;
        return ntr;
    };

    void rotateLL(shared_ptr<node<T>> c, shared_ptr<node<T>> p, shared_ptr<node<T>> g) {
        auto t3 = p->right;
        p->clr = color::black;
        g->clr = color::red;
        attachBase(g,p);
        p->right = g;
        g->up = p;
        g->left = t3;
        if(t3)
            t3->up = g;
    };

    void rotateRR(shared_ptr<node<T>> c, shared_ptr<node<T>> p, shared_ptr<node<T>> g) {
        auto t3 = p->left;
        p->clr = color::black;
        g->clr = color::red;
        attachBase(g,p);
        p->left = g;
        g->up = p;
        g->right = t3;
        if(t3)
            t3->up = g;
    };

    void rotateLR(shared_ptr<node<T>> c, shared_ptr<node<T>> p, shared_ptr<node<T>> g) {
        auto t2 = c->left;
        auto t3 = c->right;
        c->clr = color::black;
        g->clr = color::red;
        attachBase(g,c);
        c->left = p;
        p->up = c;
        c->right = g;
        g->up = c;
        p->right = t2;
        if(t2)
            t2->up = p;
        g->left = t3;
        if(t3)
            t3->up = g;
    };

    void rotateRL(shared_ptr<node<T>> c, shared_ptr<node<T>> p, shared_ptr<node<T>> g) {
        auto t2 = c->left;
        auto t3 = c->right;
        c->clr = color::black;
        g->clr = color::red;
        attachBase(g,c);
        c->left = g;
        g->up = c;
        c->right = p;
        p->up = c;
        g->right = t2;
        if(t2)
            t2->up = g;
        p->left = t3;
        if(t3)
            t3->up = p;
    };

    void delete_case1(shared_ptr<node<T>> n, shared_ptr<node<T>> s, shared_ptr<node<T>> p) {
        if(n!=root)
            delete_case2(n,s,p);
    };

    void delete_case2(shared_ptr<node<T>> n, shared_ptr<node<T>> s, shared_ptr<node<T>> p) {
        if( (s->clr == color::red) &&
        (p->clr == color::black) &&
        !(s->right && s->right->clr == color::red) &&
        !(s->left && s->left->clr == color::red) ) {
            attachBase(p,s);
            p->clr = color::red;
            s->clr = color::black;
            if(p->right == s) {
                p->right = s->left;
                if(s->left)
                    s->left->up = p;
                s->left = p;
            } else if(p->left == s) {
                p->left = s->right;
                if(s->right)
                    s->right->up = p;
                s->right = p;
            }
            p->up = s;
        }
        delete_case3(n,sibling(n),p); //because of rotation, n's sibling can rotate to become the left or right child of sibling.
    };

    void delete_case3(shared_ptr<node<T>> n, shared_ptr<node<T>> s, shared_ptr<node<T>> p) {
        if( (p->clr == color::black) &&
        (s->clr == color::black) &&
        !(s->right && s->right->clr == color::red) &&
        !(s->left && s->left->clr == color::red) ) {
            s->clr = color::red;
            delete_case1(p,sibling(p),p->up);
        } else
            delete_case4(n,s,p);
    };

    void delete_case4(shared_ptr<node<T>> n, shared_ptr<node<T>> s, shared_ptr<node<T>> p) {
        if( (p->clr == color::red) &&
        (s->clr == color::black) &&
        !(s->left && s->left->clr == color::red)  &&
        !(s->right && s->right->clr == color::red) ) {
            s->clr = color::red;
            p->clr = color::black;
        } else {
            delete_case5(n,s,p);
        }
    };

    void delete_case5(shared_ptr<node<T>> n, shared_ptr<node<T>> s, shared_ptr<node<T>> p) {
        if(s->clr == color::black) {
            if( (s->left && s->left->clr == color::red) &&
            !(s->right && s->right->clr == color::red) &&
            (p->right == s) ) {
                auto sl = s->left;
                auto slr = sl->right; //reattach sibling's left right node to sibling left
                p->right = sl;
                sl->up = p;
                sl->right = s;
                s->up = sl;
                s->left = slr;
                if(slr)
                    slr->up = s;
                sl->clr = color::black;
                s->clr = color::red;
            } else {
                if( (s->right && s->right->clr == color::red) &&
                !(s->left && s->left->clr == color::red) &&
                (p->left == s) ) {
                    auto sr = s->right;
                    auto srl = sr->left;  //reattach sibling's right left node to sibling right
                    p->left = sr;
                    sr->up = p;
                    sr->left = s;
                    s->up = sr;
                    s->right = srl;
                    if(srl)
                        srl->up = s;
                    sr->clr = color::black;
                    s->clr = color::red;
                }
            }
        }
        delete_case6(n,sibling(n),p);//because of rotation pass in sibling(n)**
    };

    void delete_case6(shared_ptr<node<T>> n, shared_ptr<node<T>> s, shared_ptr<node<T>> p) {
        auto sl = s->left;
        auto sr = s->right;
        if( (p->right == s) &&
            (s->clr == color::black) &&
            (s->right && s->right->clr == color::red) ) {
            s->clr = p->clr;
            p->clr = color::black;
            attachBase(p,s);
            s->left = p;
            p->up = s;
            p->right = sl;
            if(sl)
                sl->up = p;
            if(sr)
                sr->clr = color::black;
        } else {
            if( (p->left == s) &&
                (s->clr == color::black) &&
                (s->left && s->left->clr == color::red) ) {
                s->clr = p->clr;
                p->clr = color::black;
                attachBase(p,s);
                s->right = p;
                p->up = s;
                p->left = sr;
                if(sr)
                    sr->up = p;
                if(sl)
                    sl->clr = color::black;
            }
        }
    };

    char printColor(shared_ptr<node<T>> n) {
        char c;
        (n->clr == color::black) ? c = 'B' : c = 'R';
        return c;
    };

    void print(shared_ptr<node<T>> n) {
        if(n->left)
            print(n->left);
        cout<<"\'"<< n->val<<" "<<printColor(n)<<"\' ";
        if(n->right)
            print(n->right);
    };
public:
    redBlackTree() : root(nullptr) {};
    void addNode(const T& n) {
        if(!root) {
            root = make_shared<node<T>>(n, nullptr);
            root->clr = color::black;
        }
        else {
            auto walker = walkTree(root, n);
            auto c = (n < walker->val) ? walker->left = make_shared<node<T>>(n, walker) :
            walker->right = make_shared<node<T>>(n, walker);
            auto p = walker;
            auto g = walker->up;
            while(sibling(p) && sibling(p)->clr == color::red && p->clr==color::red) { //recolor//
                p->clr = color::black;
                sibling(p)->clr = color::black;
                if(g!=root) {
                    g->clr = color::red;
                    c = g, p = c->up, g = p->up;
                }
            }
            if(g && p->clr == color::red && (!sibling(p) || sibling(p)->clr == color::black)) { //restructure//
                if(g->left == p && p->left == c)
                    rotateLL(c,p,g);
                else if(g->right == p && p->right == c)
                    rotateRR(c,p,g);
                else if(g->left == p && p->right == c)
                    rotateLR(c,p,g);
                else if(g->right == p && p->left == c)
                    rotateRL(c,p,g);
            }
        }
    };
    
    void removeNode(const T& n) {
        auto ntr = findNode(n);
        if(!ntr)
            return;
        auto ios = inorderSuccessor(ntr);
        ntr->val = ios->val;
        if(ios->clr == color::black) {
            if(ios->right && ios->right->clr == color::red) { //ios has the at most one child.//
                ios->val = ios->right->val;
                ios = ios->right;
            }
            else
                delete_case1(ios,sibling(ios),ios->up);
                }
        if(ios == root)
            root = nullptr;
        else
            (ios->up->left == ios) ? ios->up->left = nullptr : ios->up->right = nullptr;
    };
    
    int findNodeCount(const T& v) {
        auto w = root;
        int nodeCount = 0;
        while(w) {
            if(v ==  w->val)
                return nodeCount;
            else {
                w = (v < w->val) ? w->left : w->right;
                nodeCount++;
            }
        }
        return -1;
    };
    
    void print(){
        cout<<"Printing tree: "<<endl<<"[ ";
        print(root);
        cout<<"]"<<endl;
    };
};

#endif /* redBlackTree_hpp */
