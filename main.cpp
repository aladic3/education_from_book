import try_drill;




int main() {
    try {
        ch9::ex17_19::test();
    }
    catch (...) {
        return -3;
    }

    return 0;
}