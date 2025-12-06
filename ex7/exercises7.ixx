//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include <iostream>
export module exercises7;

namespace exercises::ex2 {
    export void print(const std::string&, const std::vector<int>&);
    export void print(const std::string&, const std::vector<std::string>&);

    export void test();
}

namespace exercises::ex3 {

    export std::vector<int> create_fibonacci_vector(const int& start_a, const int& start_b,
        const int& n, const std::vector<int>& vec); //vec is must empty on input

    export void test();
}

namespace exercises::ex5_6 {
    export std::vector<int> reverse_const(const std::vector<int>&); // produce a new vector with the reversed sequence
    export void reverse_ref(std::vector<int> &); // reverse input vec without using any vector

    export std::vector<std::string> reverse_const(const std::vector<std::string>&); // produce a new vector with the reversed sequence
    export void reverse_ref(std::vector<std::string> &);

    export void test();
}