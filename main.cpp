#include <iostream>

import chapter15;




int main() {


    try {
        ch15::try_::sizeof_test();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -1;
    }

    return 0;
}