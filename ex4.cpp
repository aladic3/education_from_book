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





