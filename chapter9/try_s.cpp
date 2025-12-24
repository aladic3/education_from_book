//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;
#include <iomanip>
#include <iostream>
import chapter8;

module try_drill;

using namespace ch8::try_drill_ex;

namespace ch9::try_s {
    void print_birthyear() {
        Date birthday {2002,Month::jul, 31};
        std::cout << std::setw(10) << std::setfill('0') << birthday << std::hex << "\t" << birthday
            << std::oct <<"\t" << birthday ;


    }

}