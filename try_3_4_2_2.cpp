//
// Created by Dmytrenko Kyrylo on 03.09.2025.
//
#include <iostream>

void alphabet() {

    char l_letter = 'a';
    char u_letter = 'A';
    char digits = '0';

    for (int i = 0; i < 26; ++i) {

        std::cout << l_letter << "\t" << int(l_letter) << "\t"
            << u_letter << "\t" << int(u_letter) << "\t"
            << digits << "\t" << int(digits) << "\n";

        ++l_letter;
        ++u_letter;
        if (digits < char('9'))
            ++digits;
        else
            digits = '@';
    }

    /*while (i < 26) {
        letter = char('a' + i);
        std::cout << letter << "\t" << int(letter) << "\n";
        ++i;
    }*/
}