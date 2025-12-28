//import drill7;
//import exercises7;
//import chapter8;
import try_drill;
//#include <iostream>

//#include <iostream>

// Forward declarations (optional): add prototypes here if you want to call functions
// implemented in the other source files from main.cpp.
//#include "drill7/foo.h"
//#include "PPP.h"


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
        //sum_first_integers();
        //celsius_transfer();
        //sum_first_doubles();
        //find_largest_fibonacci();

        //game_bulls_cows();
        //day_of_weeks();
        //find_largest_fibonacci();
        //sum_first_doubles();
        //calculator >>>>>>>>>>>>>>

        //calculation(std::cin);

        // <<< calculator

        //names_scores_pairs_v2();

        //game_bulls_cows_v2();

        //bitwise calculator >>>>>>>>>>>>>>
        /*
        Bitwise_token token{};

        int result = 0;
        std::cout << "Welcome to out simple calculator.\nPlease enter expressions using floating-point numbers."
                << std::endl << "Available operators: =, x, &, |, ^, ~, !, (, ), {, }, !."
                << std::endl << "Your expression: ";

        while (std::cin) {
            token = bitwise_ts.get();

            if (token.kind_of_token == 'x') break;
            if (token.kind_of_token == '=')
                    std::cout << "=" << result
                            << std::endl << "Enter expression: ";
            else  bitwise_ts.putback(token);

            result = bitwise_expression();


        }
        */
        // <<< bitwise calculator


        //combination_and_permutation();

        //sum_first_integers();
        //test_drill();
        //Drill7::test_drill();

        //test_second_drill_ex();

        //test_third_drill_ex();
        //Try7::dangerously_ugly_code::X f;
        //f.main();
        //print_foo();
        //print(12);
        //foo = 4;
        //print_foo();

        //Try7::converting::test();
        //calculation(std::cin);
        //exercises::ex2::test();
        //exercises::ex5_6::test();
        //exercises7::ex7_8::test();
        //exercises7::ex14::test();
        /*{
            using namespace ch8::try_drill_ex;
            auto date = (Year(2025)/Month{11}/30).add_days(365);
            Date today;
            Date tomorrow = today.add_days(4);
            tomorrow.add_days(1);


            std::cout << today << std::endl
                << tomorrow << std::endl
                << date << std::endl;

            Month month {Month::dec};
            std::cout /*<< Date::is_leapyear(2000)
                << Date::is_leapyear(1900)
                << Date::is_leapyear(2024)
                << Date::is_leapyear(2001) << std::endl
                << "test of next_workday func:\n"
                << today.next_workday() << std::endl
                << tomorrow.next_workday() << std::endl
                << date.next_workday() << std::endl
                << "test weeks of year: " << std::endl
                << today.week_of_year()
                << " " << tomorrow.week_of_year()
                << " " << date.week_of_year();
        }
*/
        {
            //ch8::ex5_9::Library::test();
            /*using namespace ch8::ex2_4;
            Name_pairs name_pairs;
            name_pairs.read_names();
            name_pairs.read_ages();
            std::cout << name_pairs;*/
        }

        // ch8::ex14_15::test();

        //ch9::drill::print_birthyear();
        //ch9::drill::try_reading_different_bases();

        ch9::drill11::test();


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
    //catch (std::exception& ex) {
    //    std::cerr << "\nerror: " << ex.what();
    //    return 1;
    //}
    catch (...) {
        //std::cerr << "\n ..." << "Something went wrong!\n";
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