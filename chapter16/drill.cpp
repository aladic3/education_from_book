//
// Created by Dmytrenko Kyrylo on 07.05.2026.
//


module;

#include <vector>
#include <iostream>

module chapter16;


constexpr bool init_g(int* p, int size) {
    *p = 1;
    for (int* s = p+1; s != p+size; ++s) {
        int* prev = s - 1;
        *s = *prev * 2;
    }

    return true;
}
constexpr int size_g = 10;
int g[size_g](10);
bool init = init_g(g,size_g);

namespace ch16::drill {
    void drill1() {
        int i = 0;
        for (int* p = g; p != g+size_g; p++) {
            std::cout <<  i << '\t' << *p << std::endl;
            ++i;
        }
    }

}