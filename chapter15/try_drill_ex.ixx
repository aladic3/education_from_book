//
// Created by Dmytrenko Kyrylo on 08.04.2026.
//
module;
#include "../error.h"
#include <vector>

export module chapter15;

export namespace ch15::try_ {
    struct Own_Exception : std::exception {
        Own_Exception(){}
        Own_Exception(const std::string& msg);
        ~Own_Exception() noexcept override;

        const char * what() const noexcept override;

    private:
        std::string* msg = nullptr;
    };

    void test_constructor_and_destructor();
    void sizeof_test();
}

export namespace ch15::drill {
    void part1();
    void part1_2();

    void part2();



    void print_array(std::ostream& os, const int* array, int size_array);
    void set_values_to_elements_array(int start, int* array, int size_array); // start with start ... start+size_array is end
    void set_values_to_elements_array_double(int start, int* array, int size_array); // 1 2 4 8 etc


    void print_vector(std::ostream& os, const std::vector<int>& vector);
    void set_values_to_elements_vector(int start, std::vector<int>& vector); // start with start ... start+size_array is end
    void set_values_to_elements_vector_double(int start, std::vector<int>& vector);
}

