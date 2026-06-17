//
// Created by Dmytrenko Kyrylo on 13.06.2026.
//
module;
#include <iostream>
#include <vector>

module chapter17;

namespace ch17::try_ {
    using namespace std;
    void test() {
        X loc{4}; // local variable
        X loc2{loc}; // copy construction
        loc = X{5}; //copy assigment
        loc2 = copy(loc); // call by value and return
        loc2 = copy2(loc);
        X loc3{6};
        X& r = ref_to(loc); // call by reference and return
        delete make(7);
        delete make(8);
        vector<X> v(4); // default values
        XX loc4;
        X* p = new X{9}; // an X on the free store
        delete p;
        X* pp = new X[5]; // an array in the free store
        delete [] pp;

        std::cout << "Test done.";
    }
}