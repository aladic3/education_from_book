//
// Created by Dmytrenko Kyrylo on 19.08.2025.
//
#include <iostream>
using namespace std;
void conversions() {
    double input_double = 0;
    cout << "Pls enter double value: ";

    while (cin >> input_double) {
        int i = input_double;
        char ch = i;
        cout << "double == " << input_double
            << " int == " << i
            << " ch == " << ch
            << " char(" << int(ch) << ")\n";

        cout << "Pls enter double value: ";
    }
}
