//
// Created by Dmytrenko Kyrylo on 19.12.2025.
//
module;

#include <vector>
#include "../../error.h"
#include <cmath>
#include <complex>
module chapter8;

namespace ch8::ex13 {
    [[nodiscard]]std::vector<long long int> get_all_multipliers(const long long int limit) {
        std::vector all_multipliers_of_limit{limit}; // divide by oneself

        for (int i = 2; i * i <= limit; ++i) {
            if (limit%i == 0)
                all_multipliers_of_limit.push_back(i);
        }

        return all_multipliers_of_limit;
    }

    [[nodiscard]]long long int get_max_divisor(const long long int limit,
        const std::vector<long long int>& all_multipliers) {
        long long int max_divisor = 1;
        for (auto el: all_multipliers) {
            if (limit%el == 0)
                max_divisor = el;
        }

        return max_divisor;
    }

    void Rational::reduce_rational_by(long long int value) {
        numerator/=value;
        denominator/=value;
    }




    Rational& Rational::simplify_rational() {
        auto n = std::abs(numerator);
        auto d = std::abs(denominator);
        const auto min_part_rational = std::min(n,d);
        const auto max_part_rational = std::max(n,d);
        const auto all_multipliers = get_all_multipliers(min_part_rational);
        auto max_divisor = get_max_divisor(max_part_rational,all_multipliers);

        reduce_rational_by(max_divisor);
        return *this;
    }

     Rational operator+(Rational r, Rational l) {
        if (r.get_denominator() == l.get_denominator())
            return Rational{r.get_numerator()+l.get_numerator(), r.get_denominator()};

        auto l_denominator = l.get_denominator();
        auto r_denominator = r.get_denominator();
        r.multiply_rational_by_long_long_int(l_denominator);
        l.multiply_rational_by_long_long_int(r_denominator);

        return (r+l).simplify_rational();
    }

     Rational operator-(Rational r, Rational l) {
        if (r.get_denominator() == l.get_denominator())
            return Rational{r.get_numerator()-l.get_numerator(), r.get_denominator()};

        auto l_denominator = l.get_denominator();
        auto r_denominator = r.get_denominator();
        r.multiply_rational_by_long_long_int(l_denominator);
        l.multiply_rational_by_long_long_int(r_denominator);

        return (r-l).simplify_rational();
    }

     Rational operator*(const Rational& r, const Rational& l) {
        return Rational{r.get_numerator()*l.get_numerator(),
                r.get_denominator()*l.get_denominator()}.simplify_rational();
    }

     Rational operator/(const Rational& r, const Rational& l) {
        return Rational{r.get_numerator()*l.get_denominator(),
            r.get_denominator() * l.get_numerator()}.simplify_rational();
    }

    bool Rational::operator==(const Rational & l) const {
        if (numerator == l.get_numerator() && denominator == l.get_denominator())
            return true;

        return false;
    }

    bool Rational::operator!=(const Rational & l) const {
        return !operator==(l);
    }

    Rational& Rational::operator=(int integer) {
        numerator=integer;
        denominator = 1;
        return *this;
    }
    std::pair<long long int,long long int> get_pair_num_denom(const double non_integer) { // example 1.32 -> 132 and 100
        std::pair result {0LL,0LL};
        auto num = non_integer;
        int denominator = 1;
        int count = 0;
        while (fmod(num,1) > 0.01 && count < 3) {
            num*=10;
            denominator*=10;
            ++count;
        }
        result.first = static_cast<long long int>(num);
        result.second = denominator;
        return result;
    }






    void Rational::validate_denominator(long long int denominator) {
        if (denominator == 0)
            error("denominator can't be zero");
    }
    Rational& Rational::operator=(double non_integer) {
        auto[num, denom] = get_pair_num_denom(non_integer);
        numerator = num;
        denominator = denom;
        validate_denominator(denominator);

        simplify_rational();

        return *this;
    }




    void test() {
        Rational r1 = 0.3;
        Rational r2 = 5;
        Rational r3 = 0.833333333;
        bool b1 = r2==r2;
        bool b2 = r2!=r2;
        auto sum_r = r1+r3;
        auto substract_r = r1-r3;
        auto multiply_r = r1*r3;
        auto division_r = r1/r3;
        Rational r4 = 13/7.;
        auto finish = r4*r2;
    }

}

