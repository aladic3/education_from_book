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
    Matrix();
    Matrix(initializer_list<initializer_list<double>> init_list);
    Matrix(int rows, int cols, double val);
    Matrix(int rr, int cc);
    Matrix(const Matrix& m);
    Matrix(Matrix&& m);

    std::vector<double> row(int i) const ;
    std::vector<double> column(int i) const ;

    int rows_count() const{return r_count;}
    int column_count() const {return c_count;}

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);

    Matrix& operator+=(double el);
    Matrix& operator-=(double el);

    bool operator!=(const Matrix &) const;

    double& operator[](int row,int coll);
    double operator[](int row,int coll) const;

    Matrix operator+(const Matrix& m) const;
    bool operator==(const Matrix &) const;

    Matrix& operator=(const Matrix& m);
    Matrix& operator=(Matrix&& m);

    void resize(int new_rows, int new_columns);
    void transpose();
    void fill(double el);

    __wrap_iter<vector<double*>::__alloc_traits::pointer> begin();
    __wrap_iter<vector<double*>::__alloc_traits::pointer> end();

    [[nodiscard]] __wrap_iter<vector<double *>::__alloc_traits::const_pointer> begin() const;
    [[nodiscard]] __wrap_iter<vector<double *>::__alloc_traits::const_pointer> end() const;

    ~Matrix();
private:
    int r_count;
    int c_count;
    vector<double*> _rows;

    void clear_matrix();


};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
std::istream& operator>>(std::istream& is, Matrix& matrix);

void print_matrix(std::ostream& os, const Matrix& m);

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

    //X glob {2};

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













