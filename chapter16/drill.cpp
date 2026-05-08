//
// Created by Dmytrenko Kyrylo on 07.05.2026.
//


module;

#include <vector>
#include <iostream>
#include "../error.h"

module chapter16;


constexpr bool init_g(int* p, int size) {
    *p = 1;
    for (int* s = p+1; s < p+size; ++s) {
        int* prev = s - 1;
        *s = *prev * 2;
    }

    return true;
}

bool init_gv(std::vector<int>& gv) {
    gv[0] = 1;
    for (int i = 1; i < gv.size(); ++i) {
        gv[i] = 2 * gv[i-1];
    }

    return true;
}

constexpr int size_g = 10;
int ga[size_g](10);
std::vector<int> gv (size_g);
bool init_v = init_gv(gv);
bool init = init_g(ga,size_g);



namespace ch16::drill {
    void copy_array(const int* from_array, int* to_array, int size) {
        for (int i = 0; i < size; ++i) {
            to_array[i] = from_array[i];
        }
    }

    void print_array(const int* array, int size) {
        for (int i = 0; i < size; ++i) {
            std::cout << "array[" << i << "] = " << array[i] << std::endl;
        }
    }

    void f(const int* array, int size) {
        int la[size_g];

        copy_array(ga, la, size_g);
        print_array(la,size_g);

        int* p = new int[size];
        copy_array(array,p,size);
        print_array(p,size);

        delete p;
    }

    unsigned long long factorial_l(const int value) {
        unsigned long long result = 1;

        if (value < 0) error("Minus factorial not exist!");
        if (value <= 1) return result;

        for (int i = 2; i <= value; ++i ) {
            result *= i;
        }

        return result;
    }

    int* create_array_factorial(int size) {
        int* result = new int[size];

        for (int i = 0; i < size; ++i) {
            result[i] = static_cast<int>(factorial_l(i));
        }

        return result;
    }

    std::vector<int> create_vector_factorial(int size) {
        std::vector<int> result (size);

        for (int i = 0; i < size; ++i) {
            result[i] = static_cast<int>(factorial_l(i));
        }

        return result;
    }

    void copy_vector(const std::vector<int>& from, std::vector<int>& to) {
        for (int i = 0; i < from.size(); ++i) {
            to[i] = from[i];
        }
    }


    void print_vector(const std::vector<int>& vector) {
        for (int i = 0; i < vector.size(); ++i) {
            std::cout << "vector[" << i << "]\t" << vector[i] << std::endl;
        }
    }

    void fv(std::vector<int>& v ) {
        std::vector<int> lv (v.size());
        copy_vector(gv,lv);
        print_vector(lv);

        std::vector<int> lv2 {v};
        print_vector(lv2);
    }

    void drill1() {
        ch16::drill::f(ga,size_g);
        const int size_aa = 10;
        int* aa = ch16::drill::create_array_factorial(size_aa);
        ch16::drill::f(aa,size_aa);
        delete aa;
    }


    void drill2() {
        fv(gv);
        auto v = create_vector_factorial(10);
        fv(v);
    }

}