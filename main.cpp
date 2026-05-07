#include <iostream>

import chapter16;




int main() {


    try {
        ch16::drill::drill1();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -1;
    } catch (...) {
        return -666;
    }

    return 0;
}