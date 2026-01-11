#include <iostream>
#include "error.h"
#include "calculator.h"
import try_drill;




int main() {
    try {
        calculation(std::cin);
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -3;
    }

    return 0;
}