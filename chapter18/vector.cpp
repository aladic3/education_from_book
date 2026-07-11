//
// Created by Dmytrenko Kyrylo on 11.07.2026.
//
module;
#include "../error.h"

#include <iostream>
#include <vector>

module chapter18;


namespace ch18::vector{

    Vector::~Vector() {
        delete[] elem;
    }

    Vector::Vector() : sz(4), cap(sz*2) {
        elem = new double[cap];
        for (int i = 0; i < sz; ++i) {
            elem[i] = 0;
        }
    };

    Vector::Vector(std::initializer_list<double> lst) : sz(static_cast<int>(lst.size())),
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
}