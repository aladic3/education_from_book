//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include <iostream>
#include <vector>
#include "../ex6/fibonacci.h"
#include "../error.h"
module exercises7;

namespace exercises::ex3 {
    bool is_empty(const std::vector<int>& vec) {
        return vec.empty();
    }

    std::vector<int> create_fibonacci_vector(const int& start_a, const int& start_b,
         const int& n, const std::vector<int>& vec) {

        if (!is_empty(vec))
            error("Vector must be empty");

        auto new_vec = vec;
        new_vec.push_back(start_a); new_vec.push_back(start_b);

        calculate_fibonacci_vector(new_vec,n); // using func from fibonacci.h

        return new_vec;
    }



    void test() {
        std::vector<int> vec{};
        vec = ex3::create_fibonacci_vector(-1,-2,20,vec);

        ex2::print("fibonacci: ", vec);
    }
}