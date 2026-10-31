#include <iostream>


import chapter19;



int main() {

    try {
        ch19::ex::ex5();
        //uml_relationships::association::test();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -2;
    } catch (...) {
        return -3;
    }

    return 0;
}