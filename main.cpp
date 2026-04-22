#include <iostream>

import chapter15;




int main() {


    try {
        ch15::exercises::ex14();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -1;
    }

    return 0;
}