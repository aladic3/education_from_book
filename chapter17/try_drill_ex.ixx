//
// Created by Dmytrenko Kyrylo on 13.06.2026.
//
module;
#include "../error.h"

#include <iostream>
#include <vector>

export module chapter17;

export namespace ch17::ex {
using namespace std;

struct Matrix {
    Matrix(int rr, int cc);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m);

    int row_size() const{return rows_count;}
    int column_size() const {return column_count;}

    double& operator[](int row,int coll);
    double operator[](int row,int coll) const;

    Matrix operator+(const Matrix& m) const;
    bool operator==(const Matrix &) const;

    Matrix& operator=(const Matrix& m);
    Matrix&& operator=(Matrix&& m);

    __wrap_iter<vector<vector<double>>::__alloc_traits::pointer> begin();
    __wrap_iter<vector<vector<double>>::__alloc_traits::pointer> end();

    ~Matrix();
private:
    int rows_count;
    int column_count;
    vector<vector<double>> rows;


};

void print_matrix( Matrix& m);

void test();
}


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
        X& operator=(X&& obj)  noexcept { out("X move assigment",obj.val); val = obj.val; obj.val=0; return *this;} // move

        ~X() {out("~X()",0);}

    };

    X glob {2};

    X copy(X a) {cout << "copy()\n"; return a;}
    X copy2(X a) {cout << "copy2()\n"; X aa = a; return aa;}
    X& ref_to(X &a) {cout << "ref_to()\n"; return a;}
    X* make(int i ) {cout << "make()\n"; X a(i); return new X(a);}

    struct XX {X a; X b; };

    struct Vector {
        Vector();
        explicit Vector(int sz);
        Vector(initializer_list<double> lst);

        Vector(const Vector& v);
        Vector(Vector&& v) noexcept;

        Vector& operator=(const Vector& v);
        Vector& operator=(Vector&& v) noexcept;

        void reserve(int new_alloc);
        void resize(int new_size);
        void push_back(double new_el);

        [[nodiscard]] int size() const {return sz;}


        double& operator[](int i);
        const double& operator[](int i) const;

        [[nodiscard]] double* begin() const {return elem;} // iteration support
        [[nodiscard]] double* end() const {return elem+sz;}

        ~Vector();
    private:
        int sz = 0;
        int cap = 0;
        double* elem = nullptr;
    };

    void test();
    void test2();
    void test3();
    } // namespace ch17::try_

export namespace ch17::drill {
    struct  Ptr{
        Ptr();
        Ptr(double val);
        ~Ptr();

        Ptr(Ptr& ptr);
        Ptr(Ptr&& ptr);

        Ptr& operator=(const Ptr& ptr);
        Ptr& operator=(Ptr&& ptr);

        double* element();

    private:
        double* elem = nullptr;
    };

    void test();

}













