//
// Created by Dmytrenko Kyrylo on 05.09.2025.
//
// example.cpp
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm> // для std::sort
#include <ranges>    // для std::ranges::sort (C++20)
#include <iomanip>   // для setprecision
#include <cmath>



double dif (double,double);
double normalize (double, std::string);

void prints_while_int() {
    double  number  = 0;
    double normalized  = 0;

    double sum = 0;
    int count = 0;
    double avg = 0;

    double smallest = std::numeric_limits<double>::max();
    double biggest = std::numeric_limits<double>::min();

    std::cout << "Please enter 1 double number and units (cm, m, ft, in): ";
    std::string units;

    std::vector<double> entered_values (0);

    while (std::cin >> number >> units) {

        normalized = normalize(number,units);

        if (normalized == -1) {
            std::cout << "Rejected!\n" ;
            std::cout << "Please enter 1 double number and units: ";
            continue;
        }

        std::cout << "Input normalized " << normalized << "m. " << "Standart "
            << number << units << "\n";

        if (normalized < smallest) {
            smallest = normalized;
            std::cout << "The smallest so far. \n";
        }


        if (normalized > biggest) {
            biggest = normalized;
            std::cout << "The largest so far. \n";
        }


        //std::cout << "dif " << dif(smallest,biggest) << "\n";





        // else if (smallest > biggest)
        //     std::cout << "smaller num: " << biggest << "\n"
        //         << "grater num: " << smallest << "\n";
        //
        // else if (smallest < biggest)
        //     std::cout << "smaller num: " << smallest << "\n"
        //         << "grater num: " << biggest << "\n";


        if ( smallest == biggest )
            std::cout << "the numbers are equals\n";
        else if (dif(smallest,biggest) <= 0.011)
            std::cout << "the numbers are almost equals\n";
        // else
        //     std::cout << "smaller num: " << smallest << "\n"
        //         << "grater num: " << biggest << "\n";
        //std::cout << first << " " << second << "\n";

        std::cout << "Please enter 1 double number and units: ";

        entered_values.push_back(normalized);
        sum += normalized;
        count += 1;
    }

    avg = sum / count;

    std::cout << "Biggest " << biggest << " Smallest " << smallest
            << " Sum " << sum << " Count " << count << "\n"
            << "Avg " << avg << "\n"
            << "All values:\n";
    for (double entered_value: entered_values) {
        std::cout << entered_value << " ";
    }

    std::cout << "\nsorted: \n";
    std::sort(entered_values.begin(), entered_values.end());

    int size = entered_values.size();
    double median = 0;

    if (size % 2 == 1) {
        median = entered_values[size/2];
    } else {
        median = (entered_values[size/2 - 1] + entered_values[size/2]) / 2.;
    }

    for (double entered_value: entered_values) {
        std::cout << entered_value << " ";
    }
    std:: cout << "\nMedian = " << median;


}

double normalize(double num, std::string units) {
    double result = 0;
    if (units == "in") {
        result = (num * 2.54) / 100;
    }
    else if  (units == "m") {
        result = num;
    }
    else if (units == "cm") {
        result = num / 100;
    } else if (units == "ft") {
        result = (12 * num * 2.54) / 100;
    } else
        result = -1;

    return result;
}

double dif(double a, double b) {
    double result = 0;

    if (a < b)
        result = b - a;
    else
        result = a - b;


    return result;
}