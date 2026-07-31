#include <iostream>

import chapter18;




int main() {

    try {
        ch18::ex::test_4();

    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -2;
    } catch (...) {
        return -3;
    }

    return 0;
}