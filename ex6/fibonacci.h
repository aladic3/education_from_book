//
// Created by Dmytrenko Kyrylo on 02.12.2025.
//

#ifndef HELLO_WORLD_FIBONACCI_H
#define HELLO_WORLD_FIBONACCI_H
//#include <vector>
#include <iostream>
#include "../error.h"


void print_fibonacci(const std::vector<unsigned long long>& fibonacci);

void test_on_overflow_ull_value(std::vector<unsigned long long>& fibonacci_vec,
    const unsigned long long & next_element_of_fibonacci);

std::vector<unsigned long long> &calculate_fibonacci_vector(std::vector<unsigned long long>& fibonacci_vec,
    const unsigned long long& N);

std::vector<int> &calculate_fibonacci_vector(std::vector<int>& fibonacci_vec,
    const int& N);

unsigned long long find_largest_fibonacci();


#endif //HELLO_WORLD_FIBONACCI_H