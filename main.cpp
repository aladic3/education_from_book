#include <iostream>
#include "error.h"

import try_drill;




int main() {
    try {
        ch9::ex21_22::test();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -3;
    }

    return 0;
}