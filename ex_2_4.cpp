//
// Created by Dmytrenko Kyrylo on 24.08.2025.
//
#include  <iostream>
#include "../../../../Library/Developer/CommandLineTools/SDKs/MacOSX15.5.sdk/usr/include/c++/v1/algorithm"

void two_int_values(void) {

    std::cout << "Pls enter two double value: ";
    double val1,val2;
    std::cin >> val1 >> val2;


    double biggest = val1;
    double smallest = val2;


    if (val1 < val2) {
        smallest = val1;
        biggest = val2;
    }

    double dif = biggest - smallest;

    double sum = val1 + val2;
    double product = val1*val2;
    double ratio = 0;

    if (val2 != 0 )
      ratio = val1/val2;


    std::cout << "smaller = " << smallest << "\n"
        << "bigger = " << biggest << "\n"
        << "sum = " << sum << "\n"
        << "product = " << product << "\n"
        << "dif = " << dif << "\n"
        << "ratio = " << ratio;

}
