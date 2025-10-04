#include <iostream>

// Forward declarations (optional): add prototypes here if you want to call functions
// implemented in the other source files from main.cpp.

#include "PPP.h"
int square(int);

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the <b>lang</b> variable name to see how CLion can help you rename it.

    /*std::cout << "Please input your first name and age\n";
    std::string firstName="???";
    double age = -1;
    std::cin >> firstName >> age;
    std::cout << "Hello, "<<  firstName << " (age " << age*12 <<" month)\n";
*/
/*
    std::string current;
    std::string previous;
    std::cout << "input words:\n";
    while (std::cin >> current) {
        if (current == previous)
            std::cout << "repeated word: " << current << "\n";

        previous = current;
    }
*/
    //conversions();

    //letter();
    //std::cout << convert_to_kilometers(7);
    //two_int_values();
    //go_to_bathroom();
    //go_to_my_worck();

    //three();
    //even_or_odd();
    //spelled_numbers();
    // calculation();
    //sum_penni();
    //convert();
    //alphabet();
    //std::cout << "square " << square(4);
    prints_while_int();
    //print_each_char();

    //game_in_numbers();
    //converts_digits();
    // mini_calculator();
    //grain_and_chess();
    //rock_paper_scissors();
    //find_primes();
    //find_primes_sieve();

    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}

int square(int x) {
    int result = 0;
    for (int i = 0; i < x; ++i) {
        result += x;
    }
    return result;
}