//
// Created by Dmytrenko Kyrylo on 08.12.2025.
//
module;

#include <iostream>
#include <ostream>
#include <vector>
#include "../../error.h"
export module chapter8;

namespace ch8::try_drill_ex {
    export class Date;
    export struct Year;
    export struct Day;
    export enum class Month;

    const std::vector<std::string> vector_month_tdl = {
        "no exist", // zeroth id is redundant
        "January", "February",
        "March", "April", "May",
        "June", "Jul", "August",
        "September", "October", "November",
        "December"
        };

    bool is_day(int);
    bool is_month(Month);
    bool is_year(int);
    bool is_date(Year yy, Month mm, Day dd);


    export  std::ostream& operator<<( std::ostream& os, Month month);
    export std::ostream& operator<<(std::ostream& os, const Date& d);
    export Month& operator++(Month& month);


    export Date operator/(Date date, Day day);
    export Date operator/(Year year, Month month);

    inline int month_to_int(Month mm) {
        return static_cast<int>(mm);
    }

    inline const std::string& month_to_str(Month mm) {
        return vector_month_tdl[month_to_int(mm)];
    }



    enum class Month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec // start with 1
    };

    struct Day {
        int d;
        explicit Day(int dd):d(dd) {}
    };

    struct Year {
        int y;
        explicit Year(int yy): y(yy){}
    };



    class Date {
    public:
        Date(Year yy, Month mm, Day dd):year(yy),month(mm), day(dd) {
            if (!is_date(yy, mm,dd))
                error("bad date");
        }

        explicit Date(Year yy):year(yy), month(Month::jan), day(1) {
            if (!is_date(yy, month, day))
                error("bad date");

        }

        Date(Month mm, Day dd): year(2001), month(mm), day(dd) {
            if (!is_date(year, mm,dd))
                error("bad date");
        }
        Date(Month mm, Year yy): year(yy), month(mm), day(1) {
            if (!is_date(yy, mm,day))
                error("bad date");
        }

        Date():year(2001), month(Month::jan), day(1){}

        Date& add_days(int);
        Date& add_one_day();

        Date& set_day(Day day);
        Date& set_month(Month month);
        Date& set_year(Year year);

        [[nodiscard]]  Year get_year() const{ return year;}
        [[nodiscard]]  Month get_month() const{ return month;}
        [[nodiscard]]  Day get_day() const{ return day;}
    private:
        Year year;
        Month month;
        Day day;
    };


}