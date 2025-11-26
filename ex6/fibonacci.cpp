//
// Created by Dmytrenko Kyrylo on 26.11.2025.
//
#include <vector>
#include <iostream>
#include "../error.h"

constexpr unsigned long long init_value= 1;
const std::string prompt = "Enter count (N) values of the Fibonacci series, which you want find: ";


void print_fibonacci(const std::vector<unsigned long long>& fibonacci) {
    std::cout << "Fibonacci:\n";

    for (auto el: fibonacci) {
        std::cout << el << " ";
    }

    std::cout << "Largest: " << fibonacci[fibonacci.size() -1] << std::endl;
    std::cout << std::endl;
}

void test_on_overflow_ull_value(std::vector<unsigned long long>& fibonacci_vec,
    const unsigned long long & next_element_of_fibonacci) {
    if (next_element_of_fibonacci < 0) {
        print_fibonacci(fibonacci_vec);
        error("N so big. Integer overflow!\n");
    }
}

std::vector<unsigned long long> &calculate_fibonacci_vector(std::vector<unsigned long long>& fibonacci_vec,
    const unsigned long long& N) {
    unsigned long long next_element_of_fibonacci;
    for (auto i = 1; i < N - 1; ++i) { // count of elements vector is N-1
        next_element_of_fibonacci = fibonacci_vec[i] + fibonacci_vec[i - 1];
        test_on_overflow_ull_value(fibonacci_vec, next_element_of_fibonacci);
        fibonacci_vec.push_back(next_element_of_fibonacci);
    }

    return fibonacci_vec;
}

unsigned long long find_largest_fibonacci()
/*
 *write a program that writes out the first N values of the Fibonacci series, that is, the series
 *that starts with 1 1 2 3 5 8 13 21 34. The next number of the series is the sum of the two previous ones.
 *Find the largest Fibonacci number that fits in an int.
 */
{
    unsigned long long largest_fibonacci = 0;
    unsigned long long input;
    std::vector fibonacci_vec {init_value, init_value};

    std::cout << prompt;
    std::cin >> input;

    if (!std::cin) error("Bad input!");
    const unsigned long long N = input;
    if (N < 3) return init_value;

    calculate_fibonacci_vector(fibonacci_vec, N);

    largest_fibonacci = fibonacci_vec[N-1];

    print_fibonacci(fibonacci_vec);

    return largest_fibonacci;
}
