//
// Created by Dmytrenko Kyrylo on 03.12.2025.
//

#include "drill7.h"
import drill7;
using namespace Drill7;

void test_second_drill_ex() {
    X::var = 7;
    X::print(); // print X's var

    using namespace Y;
    var = 9;
    print(); //print Y's var

    {
        using Z::var;
        using Z::print;

        var = 11;
        print(); // print Z's var
    }

    print(); // Y

    X::print(); // X
}