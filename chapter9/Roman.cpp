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
        ch = static_cast<char>(std::toupper(ch));

        for (auto& pair: basic_values)
            if (ch == pair.first)
                return pair.second;

        return 999999;
    }

    bool is_good_subtraction(char current_roman, char last_roman) {
        auto current_roman_int = roman_ch_to_int(current_roman);
        auto last_roman_int = roman_ch_to_int(last_roman);
        auto ratio = current_roman_int / last_roman_int;

        // subtraction rules
        if (last_roman_int < current_roman_int && ratio != 10 && ratio != 5)
                return false;
        if (last_roman_int < current_roman_int && non_repeatable_romans.contains(last_roman))
                return false;

        return true;
    }

    bool is_good_repeating(char last_roman, char current_roman, int& count_repeat) {
        if (last_roman == current_roman && !non_repeatable_romans.contains(current_roman))
            ++count_repeat;
        else if (last_roman == current_roman && non_repeatable_romans.contains(current_roman))
            return false;
        else
            count_repeat = 1;

        if (count_repeat > 3) // rule repeat max 3
            return false;

        return true;
    }

    bool is_roman(char current_roman) {
        if (!all_possible_romans.contains(current_roman)) // is roman
            return false;
        return true;
    }

    bool is_valid_roman_str(const std::string& roman_str) {
        int count_repeat = 0;
        char last_roman = '0';

        for (auto current_roman : roman_str) {
            current_roman = static_cast<char>(std::toupper(current_roman)); //normalized_current

            if (!is_roman(current_roman) || !is_good_repeating(last_roman,current_roman,count_repeat) ||
                !is_good_subtraction(current_roman,last_roman))
                    return false;

            last_roman = current_roman;
        }

        return true;
    }
    bool is_valid_roman_int(int roman_int) {

    }
    int roman_str_to_int(const std::string& roman_str) {
        auto overall_roman = 0;
        auto current_roman_int = roman_ch_to_int(roman_str[0]);
        auto next_roman_int = current_roman_int;

        for (auto el: roman_str.substr(1)) {
            next_roman_int = roman_ch_to_int(el);

            if (current_roman_int < next_roman_int)
                overall_roman -= current_roman_int;
            else
                overall_roman += current_roman_int;

            current_roman_int = next_roman_int;
        }

        overall_roman += current_roman_int;

        return overall_roman;
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

    void test() {


        for (auto& el : ch9::test::good_romans)
            try {
                Roman r{el.first};
                if (r.get_roman_int() != el.second)
                    error("must be good");
            } catch (std::exception& ex) {
                std::cerr << ex.what();
            }





            for (auto& el: ch9::test::bad_romans)
                try {
                    Roman r{el};
                    throw Bad_exception {std::format("must be bad, but not for el:{}\t{}",r.get_roman_str(),
                            r.get_roman_int())};
                } catch (std::exception& ex) {
                    std::cerr <<  "must be bad" << ex.what() ;
                } catch (Bad_exception& ex) {
                    std::cerr << ex.what();
                }


        return;

    }
}
