//
// Created by Dmytrenko Kyrylo on 24.08.2025.
//
#include <iostream>
#include <string>
void three() {
    std::cout << "Pls input three string val: "; //std::cout << "Pls input three numbers: ";
    std::string a,b,c;// int a,b,c;
    std::cin >> a >> b >> c;

    std::string temp;

    if (a >= b) {
        temp = a;
        a = b;
        b = temp;
    }

    if (b >= c) {
        temp = b;
        b = c;
        c = temp;
    }

    if (a >= b) {
        temp = a;
        a = b;
        b = temp;
    }

    if (b >= c) {
        temp = b;
        b = c;
        c = temp;
    }

    std::cout << a << ", " << b << ", " << c;


}