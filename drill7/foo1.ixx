//
// Created by Dmytrenko Kyrylo on 03.12.2025.
//
module;
#include <iostream>
export module foo1;

int foo = 0;

export void print_foo() {
    std::cout << foo << '\n';
}

export void set_foo(int x) {
    foo = x;
}

export int get_foo() {
    return foo;
}