//
// Created by Dmytrenko Kyrylo on 08.12.2025.
//
module;
#include <iostream>
#include <ostream>
#include "../../error.h"
export module try8;

export namespace ch8::try1 {
    class Date {
    public:
        Date(int yy,int mm,int dd):year(yy),month(mm), day(dd) {
            if ( is_bad_month() || is_bad_day()|| is_bad_year())
                error("bad input");
        }

        [[nodiscard]]  int get_year() const{ return year;}
        [[nodiscard]]  int get_month() const{ return month;}
        [[nodiscard]]  int get_day() const{ return day;}




    private:
        [[nodiscard]] bool is_bad_month() const{return month > 12 || month < 1;}
        [[nodiscard]] bool is_bad_year() const{return year < 0;}
        [[nodiscard]] bool is_bad_day() const{return day > 31 || day < 1; }

        int year;
        int month;
        int day;
    };


    std::ostream& operator<<(std::ostream& os, const Date& d)  {
        return os << d.get_year() << '/' << d.get_month() << '/' << d.get_day();
    }
}