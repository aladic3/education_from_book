//
// Created by Dmytrenko Kyrylo on 10.04.2026.
//
module;
#include <iostream>
module chapter15;


namespace ch15::drill {
    void part1() {
        const int size_array = 1000;
        int* array = new int[size_array]{0,1,2,3,4,5,6,7,8,9};
        set_values_to_elements_array(100,array,size_array);
        print_array(std::cout, array, size_array);

        delete[] array;
    }

    void print_array(std::ostream &os, const int *array, int size_array) {
        os << "print array...\n";
        for (const int *iterator = array; iterator != array + size_array; ++iterator)
            os << iterator << " is " << *iterator << std::endl;
    }

    void set_values_to_elements_array(int start, int *array, int size_array) {
        for (int* el = array; el != array + size_array; ++el) {
            *el = start;
            ++start;
        }
    }

    void part1_2() {
        constexpr int size_v = 20;
        std::vector<int> vector(size_v);
        set_values_to_elements_vector(100,vector);
        print_vector(std::cout, vector);
    }

    void print_vector(std::ostream &os, const std::vector<int> &vector) {
        os << "print vector...\n";
        for (auto& el : vector )
            os << &el << " is " << el << std::endl;
    }

    void set_values_to_elements_vector(int start, std::vector<int>& vector) {
        for (auto& el : vector) {
            el = start;
            ++start;
        }
    }

}