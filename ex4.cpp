//
// Created by Dmytrenko Kyrylo on 16.10.2025.
//
#include <iostream>


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
    auto size_str = possible_integer.size();
    int result = 0;


    for (auto i = 0; i < size_str; ++i) {
        char symbol = possible_integer[i];
        int number = 0;

        switch (symbol) {
            case '0':
                number = 0;
                break;

            case '1':
                number = 1;
                break;

            case '2':
                number = 2;
                break;

            case '3':
                number = 3;
                break;

            case '4':
                number = 4;
                break;

            case '5':
                number = 5;
                break;

            case '6':
                number = 6;
                break;

            case '7':
                number = 7;
                break;
            case '8':
                number = 8;
                break;

            case '9':
                number = 9;
                break;

            case '|':
                return -1;

            default:
                error("Bad integer input!");

        }

        result += number * std::pow(10, size_str - (i + 1) );
    }


    return result;
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





