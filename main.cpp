#include <iostream>

import chapter17;




int main() {


    try {
        ch17::try_::test();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -1;
    } catch (...) {
        return -666;
    }

    return 0;
}