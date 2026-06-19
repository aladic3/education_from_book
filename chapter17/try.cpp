//
// Created by Dmytrenko Kyrylo on 13.06.2026.
//
module;
#include "../error.h"

#include <iostream>
#include <vector>

module chapter17;

namespace ch17::try_ {
    using namespace std;

    Vector::~Vector() {
        delete[] elem;
    }

    Vector::Vector() : sz(4), cap(sz*2) {
        elem = new double[cap];
        for (int i = 0; i < sz; ++i) {
            elem[i] = 0;
        }
    };

    Vector::Vector(initializer_list<double> lst) : sz(static_cast<int>(lst.size())),
        cap(sz), elem(new double[cap]){
            int iterator = 0;

            for (double val : lst) {
                elem[iterator] = val;
                ++iterator;
            }
    }
    Vector::Vector(const Vector &v): sz(v.size()), cap(v.cap), elem(new double[cap]) {
        for (int i = 0; i < sz; ++i)
            elem[i] = v.elem[i];
    }

    Vector::Vector(Vector &&v) noexcept : sz(v.size()), cap(v.cap), elem(v.elem) {
        v.elem = nullptr;
        v.sz = 0;
        v.cap = 0;
    }

    Vector &Vector::operator=(const Vector &v) {
        auto* new_array = new double[v.cap];

        for (int i = 0; i < v.sz; ++i)
             new_array[i] = v.elem[i];

        cap = v.cap;
        sz = v.sz;
        delete[] elem;
        elem = new_array;

        return *this;
    }
    Vector &Vector::operator=(Vector &&v) noexcept{
        sz = v.sz;
        cap = v.cap;
        delete[] elem;
        elem = v.elem;

        v.elem = nullptr;
        v.sz = 0;
        v.cap = 0;

        return *this;
    }

    void Vector::reserve(int new_alloc) {
        if (new_alloc <= cap) return;

        auto* new_array = new double[new_alloc];

        for (int i = 0; i < size(); ++i) {
            new_array[i] = elem[i];
        }
        delete[] elem;

        elem = new_array;
        cap = new_alloc;

    }
    void Vector::resize(int new_size) {
        reserve(new_size);

        for (int i = sz; i < new_size; ++i)
            elem[i] = 0;

        sz = new_size;
    }
    void Vector::push_back(double new_el) {
        if (sz == cap)
            reserve(sz*2);

        elem[sz] = new_el;
        ++sz;
    }

    const double &Vector::operator[](int i) const {
        if (i >= sz || i < 0 )
            error("bad iterator");

        return elem[i];
    }
    Vector::Vector(int s) {
        if (s < 0)
            error("bad size");
        sz = s;
        elem = new double[sz];
        cap = s;
    }

    double& Vector::operator[](int i) {
        if (i >= sz || i < 0 )
            error("bad iterator");

        return elem[i];
    }

    Vector create_v(initializer_list<double> elements) {
        return Vector(elements);
    }

    void print_v(const Vector& v, const string& intro = "") {
        cout << intro;
        for (auto el : v) {
            cout << el << '\t';
        }
        cout << '\n';
    }

    void test3() {
        Vector default_resize_test;
        Vector push_test = {1, 2 ,3 ,4};
        Vector reserve_test (3);

        print_v(default_resize_test, string("default_resize_test: "));
        print_v(push_test, string("push_test: "));
        print_v(reserve_test, string("reserve_test: "));

        push_test.push_back(5);
        reserve_test.reserve(10);
        default_resize_test.push_back(1);

        print_v(default_resize_test, string("default_resize_test after push: "));
        print_v(push_test, string("push_test after push: "));
        print_v(reserve_test, string("reserve_test after reserve"));

        default_resize_test.resize(40);

        print_v(default_resize_test, string("default_resize_test after resize: "));

        Vector copy_test = push_test;
        Vector move_test = create_v({5,4,3,2,1});

        print_v(copy_test, string("copy_test: "));
        print_v(move_test, string("move_test: "));


    }

    void test2() {
        Vector b(10);
        double x = b[3];
        b[2] = x;
    }

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