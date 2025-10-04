//
// Created by Dmytrenko Kyrylo on 25.08.2025.
//
#include <iostream>

void spelled_numbers() {
    std::cout << "Pls enter numbers in spelled format (0,1,2,3,4): ";
    std::string spelled_num;
    std::cin >> spelled_num;

    if (spelled_num == "zero")
        std::cout << "0";
    else if (spelled_num == "one")
        std::cout << "1";
    else if (spelled_num == "two")
        std::cout << "2";
    else if (spelled_num == "three")
        std::cout << "3";
    else if (spelled_num == "four")
        std::cout << "4";
    else
        std::cout << "not a number I know";
}