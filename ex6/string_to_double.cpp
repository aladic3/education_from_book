//
// Created by Dmytrenko Kyrylo on 26.11.2025.
//
#include "string_to_double.h"

constexpr int end_of_input_int = -1;
constexpr char end_of_input_char = '|';
constexpr int dot_kind = -2;

const  std::map<char, int> symbol_variants = {
    {'1',1},
    {'2',2},
    {'3',3},
    {'4',4},
    {'5',5},
    {'6',6},
    {'7',7},
    {'8',8},
    {'9',9},
    {'0',0},
    {end_of_input_char,end_of_input_int},
    {'.',dot_kind}, // is_have_dot
    {',',dot_kind}

};

constexpr double END_OF_INPUT = std::numeric_limits<double>::max();
constexpr size_t NOT_HAVE_COMMA = std::numeric_limits<size_t>::max();

size_t find_dot_position(const std::string& possible_double) {
    for (size_t i = 0; i < possible_double.size(); ++i) {
        const char symbol = possible_double[i];

        if (symbol == ',' || symbol == '.') return i;
    }

    return possible_double.size();
}

double find_double_from_string(std::string &possible_double) {
    const size_t position_of_dot = find_dot_position(possible_double);
    double result = 0;
    bool is_already_dot = false; // is find first dot or comma


    for (int i = 0; i < possible_double.size(); ++i ) {

        auto finded_symbol = symbol_variants.find(possible_double[i]);

        if (finded_symbol == symbol_variants.end())
            error("Bad input!\n");

        switch (finded_symbol->second) {
            case dot_kind:
                if (is_already_dot) error("Bad input!\n");
                is_already_dot = true;
                break;

            case end_of_input_int:
                if (i != 0) error("Bad input!\n");
                result = END_OF_INPUT;
                break;


            default:
                if (!is_already_dot)
                    result += finded_symbol->second * pow(10, position_of_dot - (i + 1));
                else
                    result += finded_symbol->second * pow(0.1, i - position_of_dot);
        }


    }

    return result;
}

std::pair<int,std::string> get_multiply_and_strDoubleWithoutMinus(const std::string& wet_possible_double) {
    const bool is_have_minus = wet_possible_double[0] == '-';
    int result_multiply = 1;
    std::string possible_double;
    if (is_have_minus) {
        result_multiply = -1;

        for (size_t i = 1; i < wet_possible_double.size(); ++i) {
            possible_double += wet_possible_double[i];
        }
    }
    else
        possible_double = wet_possible_double;

    return std::pair {result_multiply, possible_double};
}


double transparent_from_string_to_double(const std::string& wet_possible_double) {
    auto [result_multiply, possible_double] = get_multiply_and_strDoubleWithoutMinus(wet_possible_double);
    double result = find_double_from_string(possible_double);

    return result * result_multiply;

}