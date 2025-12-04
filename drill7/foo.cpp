//
// Created by Dmytrenko Kyrylo on 04.12.2025.
//
#include <iostream>
#include "foo.h"

int foo = 0;

void print_foo() {
    print(foo);
}

void print(int input) {
    std::cout << input << '\n';
}