//
// Created by Dmytrenko Kyrylo on 16.10.2025.
//
#include <iostream>
#include <map>
#include <random>
#include "error.h"
#include "ex6/string_to_double.cpp"

constexpr double END_OF_INPUT = std::numeric_limits<double>::max();
constexpr size_t NOT_HAVE_COMMA = std::numeric_limits<size_t>::max();

double celsius_to_kelvin(double celsius)
// converts celsius to kelvin
{
    // below -273.15 is error
    if (celsius < -273.15)
        error("Input temperature must be above -273.15C! Because it is absolute zero!");

    return celsius + 273.25;
}

double kelvin_to_celsius(double kelvin)
// converts kelvin to celsius
{
    // below -273.15 is error
    if (kelvin < 0)
        error("Input temperature must be above 0 Kelvin! Because it is absolute zero!");

    return kelvin - 273.25;
}

double celsius_to_fahrenheit(double celsius) {
    if (celsius < -273.15)
        error("Input temperature must be above -273.15C! Because it is absolute zero!");

    return (celsius * 9/5.) + 32;
}

double fahrenheit_to_celsius(double fahrenheit) {
    if (fahrenheit < -459.67)
        error("Input temperature must be above 0 K! Because it is absolute zero!");

    return (fahrenheit - 32) * 5/9.;
}

int celsius_transfer() {
    double input_celsius, input_kelvin, input_fahrenheit = 0;


    std::cout << "Input celsius: ";
    std::cin >> input_celsius;

    std::cout << "Input kelvin: ";
    std::cin >> input_kelvin;

    std::cout << "Input fahrenheit: ";
    std::cin >> input_fahrenheit;



    if (std::cin) {
        std::cout << celsius_to_kelvin(input_celsius) << " Kelvin\n";
        std::cout << kelvin_to_celsius(input_kelvin) << " Celsius\n";
        std::cout << celsius_to_fahrenheit(input_celsius) << " Fahrenheit\n";

        std::cout << fahrenheit_to_celsius(input_fahrenheit) << " Celsius (from fahrenheit)\n";

    }
    else {
        throw std::runtime_error("Bad input! Must be double");
    }


    return 0;
}

int transparent_from_string_to_int(const std::string& possible_integer)
{
    const auto size_str = possible_integer.size();
    int result = 0;


    for (auto i = 0; i < size_str; ++i) {
        const char symbol = possible_integer[i];

        if (symbol == '|') return -1;

        const int number = symbol - '0';
        if (number > 9 || number < 0) error("Bad integer input!");

        result += number * std::pow(10, static_cast<int>(size_str) - (i + 1) );
    }


    return result;
}





void print_double_vector (const std::vector<double>& vector) {
    for (auto element: vector) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void sum_first_doubles()
/*
 * write a program that reads and stores a series of integers and then computes the sum of the first N integers
 * First ask for N, then read the values into a vector, then calculate the sum of the first N values
 */
{

    int iterator = 0, input_integer = 0;
    double sum = 0;

    std::string input_string;
    std::vector<double> vector_of_doubles, vector_of_differences;

    std::cout << "Please enter the number of values you want to sum: ";
    std::cin >> input_integer;

    const int N = input_integer;


    if (!std::cin) {
        error("Bad input");
    }

    std::cout << "Please enter some doubles (press '|' to stop): ";

    while (std::cin >> input_string) {
        const double input_double = transparent_from_string_to_double(input_string);

        if (input_double == END_OF_INPUT) break;

        vector_of_doubles.push_back(input_double);
        ++iterator;

        /*std::cout << "inputted num = " << input_integer <<std::endl;
        std::cout << "Please enter some integers (press '|' to stop): ";*/
    }

    if (vector_of_doubles.size() < N)
        error("you ask a sum of more numbers than thet are in the vector");

    input_string = "";

    std::cout  << "Your inputted vector: ";
    print_double_vector(vector_of_doubles);

    for (int i = 0; i < N; ++i) {
        sum += vector_of_doubles[i];
        input_string += std::to_string(vector_of_doubles[i]) + " ";

    }

    std::string line_of_differences;
    //calculate differences
    for (int i = 1; i < vector_of_doubles.size(); ++i) {
        vector_of_differences.push_back(vector_of_doubles[i] - vector_of_doubles[i-1]);
        line_of_differences += std::to_string(vector_of_differences[i-1]) + " ";
    }


    std::cout << "The sum of the first " << N << " numbers ( " << input_string << ") is " << sum << std::endl;
    std::cout << "Differences: " << line_of_differences << std::endl;





}

void sum_first_integers()
/*
 * write a program that reads and stores a series of integers and then computes the sum of the first N integers
 * First ask for N, then read the values into a vector, then calculate the sum of the first N values
 */
{

    int input_integer, iterator = 0, sum = 0;

    std::string input_string;
    std::vector<int> vector_of_integers;

    std::cout << "Please enter the number of values you want to sum: ";
    std::cin >> input_integer;

    const int N = input_integer;


    if (!std::cin) {
        error("Bad input");
    }

    std::cout << "Please enter some integers (press '|' to stop): ";

    while (std::cin >> input_string && iterator < N) {
        input_integer = transparent_from_string_to_int(input_string);

        if (input_integer == -1) break;

        vector_of_integers.push_back(input_integer);
        ++iterator;

        /*std::cout << "inputted num = " << input_integer <<std::endl;
        std::cout << "Please enter some integers (press '|' to stop): ";*/
    }

    if (vector_of_integers.size() < N)
        error("you ask a sum of more numbers than thet are in the vector");

    input_string = "";

    for (int i = 0; i < N; ++i) {
        sum += vector_of_integers[i];
        input_string += std::to_string(vector_of_integers[i]) + " ";
    }


    std::cout << "The sum of the first " << N << " numbers ( " << input_string << ") is " << sum;





}



void seed(std::__1::default_random_engine& engine) {
    int time = static_cast<int>(std::time(nullptr));
    engine.seed(time);

}

std::vector<int> generate_different_integers() {
    std::__1::default_random_engine random_engine;
    seed(random_engine);

    std::vector<int> result (4,-1);

    for (int i = 0; i < result.size(); ++i) {
        std::uniform_int_distribution<int> dist(0,9);

        while (result[i] == -1) {
            int random_num = dist(random_engine);


            // flag for check unicum
            bool is_unicum = true;
            for (int j = 0; j < i; ++j) {
                if (result[j] == random_num) {
                    is_unicum = false;
                    break;
                }
            }
            /*for (int element: result) {
                if (element == random_num) {
                    is_unicum = false;
                    break;
                }
            }*/


            result[i] = is_unicum ? random_num : -1;
        }
    }

    return  result;
}

std::vector<int> get_inputted_vec_in_int(const std::string &number, const int size_num) {
    //check
    transparent_from_string_to_int(number);

    std::vector<int> inputted_vec(size_num);

    for (int i = 0; i < size_num; ++i) {
        inputted_vec[i] = number[i] - '0';
    }

    return  inputted_vec;
}


std::pair<int,int> calculate_bulls_cows(const std::vector<int>& inputted_vec,
    const std::vector<int>& generated_vec, const int size_vec) {
    std::pair<int,int> bulls_and_cows = {0,0};
    for (int i = 0; i < size_vec; ++i) {

        for (int j = 0; j < size_vec; ++j) {
            if (inputted_vec[i] == generated_vec[j] && i == j) {++bulls_and_cows.first; break;}

            if (inputted_vec[i] == generated_vec[j] && i != j) {++bulls_and_cows.second; break;}
        }
    }

    return bulls_and_cows;
}

void game_bulls_cows() {
    std::string answer = "y";

    while (answer == "y") {
        std::vector<int> generated_vec = generate_different_integers();
        const int size_num = static_cast<int>(generated_vec.size());
        std::pair<int,int> bulls_cows = {0,0};



        std::cout << "Enter number (size " << size_num << "): ";

        for (std::string number; bulls_cows.first < size_num && std::cin >> number; ) {

            if (!std::cin || number.size() > size_num)
                error("bad input!");

            std::vector<int> inputted_vec = get_inputted_vec_in_int(number, size_num);

            bulls_cows = calculate_bulls_cows(inputted_vec,generated_vec,size_num);

            std::cout << "Bulls = " << bulls_cows.first << " Cows = " << bulls_cows.second << std::endl;


        }


        std::cout << "Congratulations! You win!" << std::endl << "If you would proceed new game, input 'y': ";
        std::cin >> answer;


    }




}



int normalize_word(const std::string& input) { //return day iterator
    const std::map<std::string, int> short_week_day = {
        {"sun", 0},
        {"mon", 1},
        {"tue", 2},
        {"wed", 3},
        {"thu", 4},
        {"fri", 5},
        {"sat", 6},
         {"|", -1}
    };
    const std::map<std::string, int> week_day = {
        {"sunday", 0},
        {"monday", 1},
        {"tuesday", 2},
        {"wednesday", 3},
        {"thursday", 4},
        {"friday", 5},
        {"saturday", 6}
    };

    std::string result = input;

    for (char & i : result) {
        if (i >= 'A' && i <= 'Z') i += 32;
    }

    auto search_long_word = week_day.find(result);
    auto search_short_word = short_week_day.find(result);


    if (search_long_word !=week_day.end())
        return search_long_word->second;

    if (search_short_word != short_week_day.end())
        return search_short_word->second;

    return 7; // return iterator of not corrects inputted words
}

void print_day_results(const std::vector<int> & sums_of_days) {
    const std::map<int, std::string> week_day = {
        {0, "sunday"},
        {1, "monday"},
        {2, "tuesday"},
        {3, "wednesday"},
        {4, "thursday"},
        {5, "friday"},
        {6, "saturday"},
        {7,"not correct days"}
    };

    std::cout << "Result of summarize: \n";

    for (int i = 0; i < sums_of_days.size(); ++i) {
        auto it = week_day.find(i);

        if (it != week_day.end())
            std::cout << it->second << " = "<< sums_of_days[i] << std::endl;
        else
            error("bad day print");
    }

}

void day_of_weeks()
/*
Read (day-of-the-week, value) pairs from standard input. For example:
Tuesday 23 Friday 56 Tuesday -3 Thursday 99
Collect all the values for each day of the week in a vector‹int». Write out the values of the seven day-of-the-week vectors.
Print out the sum of the values in each vector. Ignore illegal days of the week, such as Funday,
but accept common synonyms such as Mon and monday.
Write out the number of rejected values.

 */

{
    std::string input_day;
    int input_num, num_of_day = 100;
    std::vector<int> sums_of_days(8,0);

    std::cout << "Write (day-of-the-week, value) pairs. For example: Tuesday 23 Friday 56 Tuesday -3 Thursday 99."
            << "\nIf you want to stop, enter '|'"
            << "\nEnter pairs: ";

    while (std::cin >> input_day >> input_num) {
        if (!std::cin) error("bad input");

        num_of_day = normalize_word(input_day);

        if (num_of_day == -1) break;
        if (num_of_day == 7) {
            ++sums_of_days[num_of_day];
            continue;
        }

        sums_of_days[num_of_day] += input_num;
    }

    print_day_results(sums_of_days);

}