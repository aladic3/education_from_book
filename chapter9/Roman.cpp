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
        {'M',1000},
        {'D',500},
        {'C', 100},
        {'L', 50},
        {'X', 10},
        {'V', 5},
        {'I', 1}
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

        error("bad char when translate one char to roman int");
        return 999999;
    }

    char roman_int_to_ch(int r) {
        for (auto& pair: basic_values)
            if (r == pair.second)
                return pair.first;

        error("bad int when translate one int to roman char");
        return 0;
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
        int count_repeat = 1;
        char last_roman = roman_str.front();

        for (auto current_roman : roman_str.substr(1)) {
            current_roman = static_cast<char>(std::toupper(current_roman)); //normalized_current

            if (!is_roman(current_roman) || !is_good_repeating(last_roman,current_roman,count_repeat) ||
                !is_good_subtraction(current_roman,last_roman))
                    return false;

            last_roman = current_roman;
        }

        return true;
    }
    bool is_valid_roman_int(int roman_int) {
        return roman_int < 4000 && roman_int > 0;
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

        if (roman_int_to_str(overall_roman) != roman_str)
            error("bad input str roman!");

        return overall_roman;
    }
    std::string roman_int_to_str(int input_roman_int) {
        std::string result;
        int ra = input_roman_int;

        if (!is_valid_roman_int(ra))
            error("bad input int in roman translate");

        while (ra > 0)
            for (auto& roman_pair: basic_values) {
                int diff_lower = non_repeatable_romans.contains(roman_pair.first)
                                 ? roman_pair.second / 5: roman_pair.second / 10;
                int ratio = ra / roman_pair.second;
                int remainder = roman_pair.second % ra ;

                if (ratio > 0) {
                    ra-=roman_pair.second;
                    result+=roman_pair.first;
                    break;
                }

                if (remainder <= diff_lower && roman_pair.second / ra == 1) {
                    ra -= roman_pair.second - diff_lower;
                    result += roman_int_to_ch(diff_lower);
                    result += roman_pair.first;
                    break;
                }

            }

        return result;
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

        std::cout << "Testing good values:\n";
        for (auto& el : ch9::test::good_romans_2)
            try {
                Roman r{el.first};
                Roman ri{el.second};
                if (ri.get_roman_str() != el.first)
                    error("must be " + el.first + " but:" + ri.get_roman_str());

                if (r.get_roman_int() != el.second)
                    error("must be good");

                std::cout << "PASS\n";
            } catch (std::exception& ex) {
                std::cerr << ex.what();
            }


            std::cout << "Testing bad values:\n";
            for (auto& el: ch9::test::bad_romans_2)
                try {
                    Roman r{el};
                    throw Bad_exception {std::format("must be bad, but not for el:{}\t{}",r.get_roman_str(),
                            r.get_roman_int())};
                } catch (std::exception& ex) {
                    std::cout << "PASS\n";
                } catch (Bad_exception& ex) {
                    std::cerr << ex.what();
                }


        return;

    }
}
