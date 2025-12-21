//
// Created by Dmytrenko Kyrylo on 20.12.2025.
//
module;
#include <cmath>
#include <iostream>

#include "../../error.h"
module chapter8;

namespace ch8::ex14_15 {
    long int round(double d) {
        auto round_d =d*10000;
        if (std::abs(fmod(round_d,10000)) >= 4999) {
            return static_cast<long int>(d+1);
        }

        return static_cast<long int>(d);
    }

    int find_iterator_currency_prompt_by_str(std::string& str) {
        for (int i = 0; i < _currency_prompt.size(); ++i) {
            if (_currency_prompt[i] == str)
                return i;
        }

        error("Bad currency");
        return -1;
    }

    void validate_currency_str(std::string& str) {
        if (str.length() > 3)
            return error("Bad currency");
    }

    [[nodiscard]]Currency get_currency_from_string(std::string& str) {
            validate_currency_str(str);
            auto iterator_currency_prompts = find_iterator_currency_prompt_by_str(str);
            return Currency{iterator_currency_prompts};

    }

    void Money::set_currency(Currency crr) {
        if (crr >= Currency::end || crr <= Currency::begin)
            error("Bad currency");

        _currency = crr;
    }

    void Money::set_monetary_amount(double amount_currency) {
        _monetary_amount = 100 * static_cast<int>(amount_currency); // v = 2.23; static_cast<int> (v) = 2;
        auto cents = std::fmod(amount_currency,1) * 100; // fmod(v,1) = .23


        if (std::abs(cents) >= 0.5)
            _monetary_amount += round(cents);

    }

    Money::Money(const double& amount_currency) {
        set_monetary_amount(amount_currency);
    }


    Money::Money(const double& amount_currency, Currency crr) {
        set_monetary_amount(amount_currency);
        set_currency(crr);

    }

    long int Money::get_monetary_amount_in_dollars() const {
        auto multiplier = _conversion_factors[static_cast<int>(_currency)];
        auto monetary_amount_in_dollars = round(static_cast<double>(_monetary_amount) / multiplier);
        return monetary_amount_in_dollars;
    }


    void Money::conversion_this_to_dollars() {
        auto monetary_amount_in_dollars = get_monetary_amount_in_dollars();
        _currency = Currency::USD;
        _monetary_amount = monetary_amount_in_dollars;

    }


    double Money::get_and_set_dollars_amount() {
        conversion_this_to_dollars();
        return get_currency_amount();
    }

   double Money::monetary_to_currency(long int monetary_amount) {
        return static_cast<double>(monetary_amount) / 100.;
    }

   double Money::get_dollars_amount() const {
        auto monetary_amount_in_dollars = get_monetary_amount_in_dollars();
        return monetary_to_currency(monetary_amount_in_dollars);

    }

    double Money::get_currency_amount() const {
        return monetary_to_currency(_monetary_amount);
    }

    std::ostream& operator<<(std::ostream& os, const Money& money) {
        auto prompt = money.get_currency_prompt();
        return os << prompt << money.get_currency_amount() ; // if negative

    }

    std::string read_3_chars(std::istream& in) {
        char input;
        std::string str_currency;
        for (int i = 0; i<3; ++i) {
            in.get(input);
            str_currency.push_back(input);
        }
        return str_currency;
    }




    Currency get_currency_from_stream(std::istream& in) {
        std::string str_currency = read_3_chars(in);
        return get_currency_from_string(str_currency);
    }

    double get_double_from_stream(std::istream& in) {
        char input = 0;
        in.get(input);

        if (std::isdigit(input) || input == '.') {
            double value = 0;
            in.putback(input);
            in >> value;
            return value;
        }
        error("bad double");

        return -1;  //is.setstate(std::ios::failbit)

    }


    std::istream& operator>>(std::istream& is, Money& money) {
        try {
            auto currency = get_currency_from_stream(is);
            auto amount = get_double_from_stream(is);

            money.set_currency(currency);
            money.set_monetary_amount(amount);
        } catch (std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            is.setstate(std::ios::failbit);;
        }

        return is;
    }

    Money operator+(const Money& m1, const Money& m2) {
        Money result {m1.get_dollars_amount()+m2.get_dollars_amount()};
        return result;
    }

    Money operator-(const Money& m1, const Money& m2) {
        Money result {m1.get_dollars_amount()-m2.get_dollars_amount()};
        return result;
    }

    void test() {
        Money money = 1.326;
        Money m2 = 23.325;
        Money m3 = 323.235;
        Money m4 = 32.4949;
        auto mm1 = money.get_and_set_dollars_amount();
        auto mm2 = m2.get_and_set_dollars_amount();
        auto mm3 = m3.get_and_set_dollars_amount();
        auto mm4 = m4.get_and_set_dollars_amount();
        Money uam1 {40,Currency::UAH};
        auto uausdm1 = uam1.get_dollars_amount();
         auto uamm1 = uam1.get_currency_amount();
        std::cout << uam1 << std::endl;

        std::cout << m2 << std::endl;
        std::cout << m3+uam1 << std::endl;
        std::cout << m4-m3;

        Money test_is{1};
        std::cout << "\nEnter Money(USD12-etc.):";
        std::cin >> test_is;

        if (!std::cin)
            error("Bad input");

        std::cout << test_is;

    }

}