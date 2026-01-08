//
// Created by Dmytrenko Kyrylo on 07.01.2026.
//
module;

#include <string>
#include <utility>
#include <vector>
#import <iostream>

#include "../error.h"


module try_drill;

namespace ch9::ex21_22 {
    class Roman;
    const std::vector<std::pair<char,int>> basic_values{
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D',500},
        {'M',1000}
    };
    constexpr  std::string non_repeatable_romans {"VLD"};
    constexpr std::string all_possible_romans {"VLDIXCM"};
    const std::vector<std::pair<char,std::string>> subtractions_rules{
        {'I',"XV"},
        {'X',"LC"},
        {'C',"DM"}
    };

    int roman_ch_to_int(char ch) {
        for (auto& pair: basic_values)
            if (ch == pair.first)
                return pair.second;

        return -1;
    }

    bool is_valid_roman_str(const std::string& roman_str) {
        int count_repeat = 0;
        char last_roman = static_cast<char>(std::toupper(roman_str.front()));

        for (auto current_roman : roman_str) {
            auto normalized_current = static_cast<char>(std::toupper(current_roman));

            if (!all_possible_romans.contains(normalized_current)) // is roman
                return false;


            if (last_roman == normalized_current && !non_repeatable_romans.contains(normalized_current))
                ++count_repeat;
            else
                count_repeat = 0;

            if (count_repeat > 2) // rule repeat max 3
                return false;

            auto current_roman_int = roman_ch_to_int(current_roman);
            auto last_roman_int = roman_ch_to_int(last_roman);
            auto ratio = current_roman_int / last_roman_int;

            // subtraction rules
            if (last_roman_int < current_roman_int && ratio != 10 && ratio != 5)
                return false;



            last_roman = normalized_current;
        }

        return true;
    }
    bool is_valid_roman_int(int roman_int) {

    }
    int roman_str_to_int(const std::string& roman_str) {

    }
    std::string roman_int_to_str(int roman_int) {

    }
    void normalize_roman_str(std::string& roman_str){

    }
    std::istream& operator>>(std::istream&, Roman& roman) {

    }
    std::ostream& operator<<(std::ostream&, const Roman& roman) {

    }

    void Roman::set_roman_int(int roman_int) {

    }

    void Roman::set_roman_str(const std::string &roman_str) {

    }
}
