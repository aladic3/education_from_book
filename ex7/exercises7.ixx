//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include <iostream>
#include <vector>
export module exercises7;

namespace exercises7::ex2 {
    export void print(const std::string&, const std::vector<int>&);
    export void print(const std::string&, const std::vector<std::string>&);
    export void print(const std::string&, const std::vector<double>&);

    export void test();
}

namespace exercises7::ex3 {

    export std::vector<int> create_fibonacci_vector(const int& start_a, const int& start_b,
        const int& n, const std::vector<int>& vec); //vec is must empty on input

    export void test();
}

namespace exercises7::ex5_6 {
    export std::vector<int> reverse_const(const std::vector<int>&); // produce a new vector with the reversed sequence
    export void reverse_ref(std::vector<int> &); // reverse input vec without using any vector

    export std::vector<std::string> reverse_const(const std::vector<std::string>&); // produce a new vector with the reversed sequence
    export void reverse_ref(std::vector<std::string> &);

    export void test();
}

namespace exercises7::ex7_8 {
    export void sort_ref(std::vector<std::string>& names, std::vector<double>& ages);
    export void print (const std::vector<std::string>& names, const std::vector<double>& ages);
    export void test();
}

namespace exercises7::ex9 {
    export std::vector<double> sum(const std::vector<double> & price, const std::vector<double> & weight);
    export void test();
}

namespace exercises7::ex10_11 {
    export struct Properties_of_vector {
        double median;
        int max_value;
        int min_value;
        double mean;
    };

    export int maxv(const std::vector<int>&);

    export Properties_of_vector calculate_properties_of_vector(const std::vector<int>&);

    export void test();
}