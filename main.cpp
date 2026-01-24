#include <iostream>
#include "calculator.h"
import chapter10;




int main() {
    try {
        ch10::ex12_13::ex12();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -3;
    }

    return 0;
}