#include <iostream>

//import chapter18;
import uml_rel_ex;



int main() {

    try {
        //ch18::ex::test_13();

    }
    catch (std::exception& err) {
        std::cerr << err.what();
        return -2;
    } catch (...) {
        return -3;
    }

    return 0;
}