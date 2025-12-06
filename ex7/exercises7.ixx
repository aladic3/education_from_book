//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include <iostream>
export module exercises7;

namespace exercises::ex2 {
    export void print(const std::string&, const std::vector<int>&);

    export void test();
}

namespace exercises::ex3 {

    export std::vector<int> create_fibonacci_vector(const int& start_a, const int& start_b,
        const int& n, const std::vector<int>& vec); //vec is must empty on input

    export void test();
}