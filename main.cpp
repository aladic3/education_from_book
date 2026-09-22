#include <iostream>


import uml_rel_ex;



int main() {

    try {
        //ch18::ex::test_13();
        uml_relationships::association::test();
    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -2;
    } catch (...) {
        return -3;
    }

    return 0;
}