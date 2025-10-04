//
// Created by Dmytrenko Kyrylo on 25.08.2025.
//
#include <iostream>

void calculation() {
    std::cout << "Pls enter operation, num, num (* 2.3 4): ";

    std::string operation;
    double num1, num2;

    std::cin >> operation >> num1 >> num2;

    if (operation == "*" || operation == "mul")
        std::cout << "result = " << num1 * num2;
    else if (operation == "/" || operation == "div")
        std::cout << "result = " << num1 / num2;
    else if (operation == "+" || operation == "plus")
        std::cout << "result = " << num1 + num2;
    else if (operation == "-" || operation == "minus")
        std::cout << "result = " << num1 - num2;
    else
        std::cout << "I don't know such operation";
}