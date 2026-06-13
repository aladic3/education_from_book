//
// Created by Dmytrenko Kyrylo on 13.06.2026.
//
module;
#include <iostream>

export module chapter17;

export namespace ch17::try_ {
    using namespace std;
    struct X {
        int val;

        void out(const string& s, int nv) { cout << this << "->" << s << ":" << val << "(" << nv << ")\n"; }

        X() { out("X()",0); val = 0;} // default constructor

        X(int x) { out("X(int)",x); val = x;}

        X(const X& obj) { out("X(X&)",obj.val); val = obj.val;} // copy constructor
        X(X&& obj) { out("X(X&&)",obj.val); val = obj.val; obj.val=0;} // move constructor

        X& operator=(const X& obj) { out("X copy assigment", obj.val); val = obj.val; return *this;} // copy
        X& operator=(X&& obj) { out("X move assigment",obj.val); val = obj.val; obj.val=0; return *this;} // move

        ~X() {out("~X()",0);}




    };

    void test();
}
