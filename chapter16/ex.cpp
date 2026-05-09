//
// Created by Dmytrenko Kyrylo on 07.05.2026.

module;
#include <iostream>

module chapter16;

namespace ch16::exercises {
    void to_lower(char* input_str) {
        for (char* p = input_str; *p != 0; ++p) {
            if (*p > 'A' && *p < 'Z')
                *p += 32;
        }
    }

    void print_str(char* str) {
        for (char* p = str; *p != 0; ++p)
            std::cout << *p;
    }

    void ex1() {
        char str [] = "Hello, World! NICE TO SEE YOU!!!\n";
        print_str(str);
        to_lower(str);
        print_str(str);

        /*char ch_A = 'A';
        char ch_a = 'a';
        char ch_punct = ',';
        std::cout << ch_A << '\t' << static_cast<int> (ch_A) << std::endl;
        std::cout << ch_a << '\t' << static_cast<int> (ch_a) << std::endl;
        std::cout << ch_punct << '\t' << static_cast<int> (ch_punct) << std::endl;*/
    }

}