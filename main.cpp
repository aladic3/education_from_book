#include <iostream>

import chapter18;




int main() {

    try {
        ch18::try_::test1();

    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -1;
    } catch (...) {
        return -666;
    }

    return 0;
}