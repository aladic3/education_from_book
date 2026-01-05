import try_drill;




int main() {
    try {
        ch9::ex14_15::test();
    }
    catch (...) {
        return -3;
    }

    return 0;
}