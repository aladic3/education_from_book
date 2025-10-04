//
// Created by Dmytrenko Kyrylo on 25.08.2025.
//
#include <iostream>

void even_or_odd() {
    std::cout << "Enter integer value: ";
    int number;
    std::cin >> number;

    if (number%2) {
        std::cout << "Number " << number << " is odd.\n";
    }
    else
        std::cout << "Number " << number << " is even.\n";
}