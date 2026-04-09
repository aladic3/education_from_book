//
// Created by Dmytrenko Kyrylo on 08.04.2026.
//
module;
#include <iostream>

module chapter15;


namespace ch15::try_ {
    void sizeof_test() {
        long int li = 0;
        long long int lli = 0;
        long long unsigned int llui = 0;
        double d = 0;
        bool* b = new bool(true);
        double* d1;
        char* ch = new char(0);
        char& ch1 = *ch;
        std::cout << "sizeof(int) = " << sizeof(int) << std::endl;
        std::cout << "sizeof(li) = " << sizeof(li) << std::endl;
        std::cout << "sizeof(lli) = " << sizeof(lli) << std::endl;
        std::cout << "sizeof(llui) = " << sizeof(llui) << std::endl;
        std::cout << "sizeof(d) = " << sizeof(d) << std::endl;
        std::cout << "sizeof(float) = " << sizeof(float) << std::endl;
        std::cout << "sizeof(bool) = " << sizeof(bool) << std::endl;
        std::cout << "sizeof(&b) = " << sizeof(b) << std::endl;
        std::cout << "sizeof(*b) = " << sizeof(*b) << std::endl;
        std::cout << "sizeof(&b) = " << sizeof(&b) << std::endl;
        std::cout << "sizeof(&double) = " << sizeof(d1) << std::endl;
        std::cout << "sizeof(char) = " << sizeof(char) << std::endl;
        std::cout << "sizeof(char*) = " << sizeof(ch) << std::endl;
        std::cout << "sizeof(char&) = " << sizeof(&ch1) << std::endl;

        delete b;
        delete ch;


    }
}
