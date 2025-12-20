//
// Created by Dmytrenko Kyrylo on 20.12.2025.
//
module;
#include <cmath>
module chapter8;

namespace ch8::ex14_15 {
    long int round(double d) {
        auto round_d =d*10000;
        if (fmod(round_d,10000) >= 4999) {
            return static_cast<long int>(d+1);
        }

        return static_cast<long int>(d);
    }
    Money::Money(const double& dollars) {
        _monetary_amount = 100 * static_cast<int>(dollars);
        auto cents = std::fmod(dollars,1) * 100;


        if (cents >= 0.5)
            _monetary_amount += round(cents);
    }

    double Money::get_dollars_amount() const {
        return static_cast<double>(_monetary_amount)/100.;
    }


    void test() {
        Money money = 1.326;
        Money m2 = 23.325;
        Money m3 = 323.233;
        Money m4 = 32.4949;
        auto mm1 = money.get_dollars_amount();
        auto mm2 = m2.get_dollars_amount();
        auto mm3 = m3.get_dollars_amount();
        auto mm4 = m4.get_dollars_amount();
    }

}