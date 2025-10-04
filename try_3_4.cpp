#include <iostream>
//
// Created by Dmytrenko Kyrylo on 29.08.2025.
//

void convert() {
    std::cout << "how many and which (y,k,p) you want to convert to dollar:";

    char v = ' ';
    int amount = 0;
    std::cin >> amount >> v;

    double result = 0;

    switch (v) {
        case 'y':
            result = amount*2;
            break;

        case 'k':
            result = amount+2;
            break;

        case 'p':
            result = amount/2;
            break;

        default:
            result = -1;
            break;
    }

    if (result == -1) {
        std::cout << "I dont convert from this value!\n";
    }
    else {
        std::cout << "result = " << result << " dollar\n";
    }

    /*
    if (v == 'y') {
        std::cout << amount*2 << " dollar\n";
    }
    else if (v == 'k') {
        std::cout << amount+2 << " dollar\n";
    }
    else if (v == 'p') {
        std::cout << amount/2 << " dollar\n";
    }
    else {
        std::cout << "I dont convert from this value!\n";
    }*/
}