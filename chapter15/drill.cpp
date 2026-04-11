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

    void set_values_to_elements_array_double(int start, int *array, int size_array) {
        for (int* el = array; el != array + size_array; ++el) {
            *el = start;
            start*=2;
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

    void set_values_to_elements_vector_double(int start, std::vector<int>& vector) {
        for (auto& el : vector) {
            el = start;
            start*=2;
        }
    }

    void part2() {
        constexpr int size_array = 7;
        int* p1 = new int(size_array);
        int* p2 = new int[size_array];


        set_values_to_elements_array_double(1,p2,size_array);
        std::cout << "Print p2:\n";
        print_array(std::cout,p2,size_array);

        std::cout << "Print p1:\n";
        std::cout << *p1 << std::endl;

        int* p3 = p2;
        p2 = p1;
        p2 = p3;

        std::cout << "Print p2:\n";
        print_array(std::cout,p2,size_array);

        std::cout << "Print p1:\n";
        std::cout << *p1 << std::endl;

        delete p1;
        delete[] p2;

        constexpr int size_array2 = 10;
        p1 = new int[size_array2];
        p2 = new int[size_array2];

        set_values_to_elements_array_double(1,p1,size_array2);

        for (int i = 0; i < size_array2; ++i)
            p2[i] = p1[i];

        std::cout << "P1: \n";
        print_array(std::cout,p1,size_array2);

        std::cout << "P2: \n";
        print_array(std::cout,p2,size_array2);

        delete[] p1;
        delete[] p2;

        using  namespace std;
        std::vector<int> v2 (size_array2);
        set_values_to_elements_vector_double(1,v2);
        cout << "Vector:\n";
        print_vector(std::cout, v2);
    }

}