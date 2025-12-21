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


    double Money::set_and_get_dollars_amount() {
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
        auto mm1 = money.set_and_get_dollars_amount();
        auto mm2 = m2.set_and_get_dollars_amount();
        auto mm3 = m3.set_and_get_dollars_amount();
        auto mm4 = m4.set_and_get_dollars_amount();
        Money uam1 {40,Currency::UAH};
        auto uausdm1 = uam1.get_dollars_amount();
         auto uamm1 = uam1.get_currency_amount();
        std::cout << uam1 << std::endl;

        std::cout << m2 << std::endl;
        std::cout << m3+uam1 << std::endl;
        std::cout << m4-m3;

        Currency cr;
        double amount;
        std::cin >> amount;
    }

}