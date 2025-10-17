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
    //prints_while_int();
    //print_each_char();

    //game_in_numbers();
    //converts_digits();
    // mini_calculator();
    //grain_and_chess();
    //rock_paper_scissors();
    //find_primes();
    //find_primes_sieve();
    // std::vector<std::string> vector {"fa", "fa", "cd", "cdr", "cdr", "fasd", "cdr", "l"};
    // std::cout << "mode = " << find_mode_str(vector) << "\n"
    //         << "min = " << find_min_str(vector) << "\n"
    //         << "max = " << find_max_str(vector) << "\n";

    //solve_quadratic_equations();

    //names_scores_pairs();

    // try 4

    // int s1 = area(7,2;
    // int s2 = area(7,2)
    // Int s3 = area(7,2);
    // int s4 = area('7, 2);
    //

    // int x0 = arena(7,2);
    // int x1 = area(7);
    // int x2 = area("seven", 2);
    // int x3 = area ('2',3);

    try {
        //test(3,5,-1);
        // double d = 0;
        //
        // std::cout << "\nhex = " << hexagon_area(2) << "\n";

        //estimate_driving_flying_time_all_cities();
        // std::cin >> d;
        // if (std::cin) {
        //     std::cout << "GG " << d;
        // }
        // else {
        //     error("Bad cin!\n");
        // }

       //debugging_fragments();
        //solve_quadratic_equations();
        sum_first_integers();
        //celsius_transfer();

        return 0;

    }
    // catch (Bad_area) {
    //     std::cerr << "\n" << "OOps! Bad arguments to area()\n";
    //     return -3;
    // }
    // catch (std::runtime_error& er) {
    //     std::cerr << "\nstd::runtime_error\n" << er.what();
    //     return -1;
    // }
    catch (std::exception& ex) {
        std::cerr << "\nerror: " << ex.what();
        return 1;
    }
    catch (...) {
        std::cerr << "\n ..." << "Something went wrong!\n";
        return 2;
    }
    //error("hmm");
    // TIP See CLion help at <a href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>. Also, you can try interactive lessons for CLion by selecting 'Help | Learn IDE Features' from the main menu.
}

int square(int x) {
    int result = 0;
    for (int i = 0; i < x; ++i) {
        result += x;
    }
    return result;
}