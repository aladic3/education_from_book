//
// Created by Dmytrenko Kyrylo on 19.12.2025.
//
module;
#include <iostream>
#include <vector>
module chapter8;

namespace ch8::ex13 {
    [[nodiscard]]std::vector<int> get_all_multipliers(const int limit) {
        std::vector all_multipliers_of_limit{limit}; // divide by oneself

        for (int i = 2; i * i <= limit; ++i) {
            if (limit%i == 0)
                all_multipliers_of_limit.push_back(i);
        }

        return all_multipliers_of_limit;
    }

    [[nodiscard]]int get_max_divisor(const int limit, const std::vector<int>& all_multipliers) {
        int max_divisor = 1;
        for (int el: all_multipliers) {
            if (limit%el == 0)
                max_divisor = el;
        }

        return max_divisor;
    }

    void Rational::reduce_rational_by(int value) {
        numerator/=value;
        denominator/=value;
    }




    Rational& Rational::simplify_rational() {
        const auto min_part_rational = std::min(numerator,denominator);
        const auto all_multipliers = get_all_multipliers(min_part_rational);
        auto max_divisor = get_max_divisor(min_part_rational,all_multipliers);

        reduce_rational_by(max_divisor);
        return *this;
    }

     Rational operator+(Rational r, Rational l) {
        if (r.get_denominator() == l.get_denominator())
            return Rational{r.get_numerator()+l.get_numerator(), r.get_denominator()};

        r.multiply_rational_by_int(l.get_denominator());
        l.multiply_rational_by_int(r.get_denominator());

        return (r+l).simplify_rational();
    }

     Rational operator-(Rational r, Rational l) {
        if (r.get_denominator() == l.get_denominator())
            return Rational{r.get_numerator()-l.get_numerator(), r.get_denominator()};

        r.multiply_rational_by_int(l.get_denominator());
        l.multiply_rational_by_int(r.get_denominator());

        return (r-l).simplify_rational();
    }

     Rational operator*(const Rational& r, const Rational& l) {
        return Rational{r.get_numerator()*l.get_numerator(),
                r.get_denominator()*l.get_denominator()}.simplify_rational();
    }

     Rational Rational::operator/(const Rational& r, const Rational& l) {
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
    Rational& Rational::operator=(double non_integer) {
        // TODO
        return *this;
    }




    void Rational::test() {


    }

}