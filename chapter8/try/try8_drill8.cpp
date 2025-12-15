//
// Created by Dmytrenko Kyrylo on 09.12.2025.
//

module;
#include <iostream>
#include <ostream>
#include "../../error.h"
module chapter8;

namespace ch8::try_drill_ex {
    bool Date::is_day(const int dd) const {
        if (month == Month::feb ) {
            if (is_leapyear(year.y)) {
                return dd >= 1 && dd <= 29;
            }

            return dd >= 1 && dd <= 28;
        }
        return dd >= 1 && dd <= 31;
    }

    bool Date::is_month(const Month mm) {
        return month_to_int(mm) >= 1 && month_to_int(mm) <= 12;
    }

    bool Date::is_year(const int yy) {
        return yy > 0;
    }

    bool Date::is_date(Year yy, Month mm, Day dd) {
        if (is_month(mm) && is_year(yy.y) && is_day(dd.d))
            return true;

        return false;
    }

    Date& Date::add_one_day() {
        if (this->day.d == 31) {
            this->day.d = 1; //set day to default with this condition

            //increment year
            if (this->month == Month::dec) // if 31/12
                ++this->year.y;

            ++this->month; //increment month
        } else
            ++this->day.d; //increment day

        return *this;
    }

    Date& Date::add_days(int count) {
        if (count < 1)
            error("bad incrementing count");

        for (int i = 0; i < count; ++i) {
            add_one_day();
        }

        return *this;
    }

    Date &Date::set_day(Day day){
        if (is_day(day.d))
            this->day = day;
        else
            error("u have a bad day");

        return *this;
    }

    Date& Date::set_month(Month month) {
        if (is_month(month))
            this->month = month;
        else
            error("u have a bad month");

        return *this;
    }
    Date& Date::set_year(Year year) {
        if (is_year(year.y))
            this->year = year;
        else
            error("u have a bad year");

        return *this;
    }

    bool Date::is_leapyear(int year) {
        if (year%100 == 0) {
            if (year%400 == 0)
                return true;

            return false;
        }

        if (year%4 == 0 )
            return true;

        return false;
    }




    std::ostream& operator<<( std::ostream& os, const Month month) {
        return os << month_to_str(month);
    }

    std::ostream& operator<<(std::ostream& os, const Date& d)  {
        return os << d.get_year().y << '/' << d.get_month() << '/' << d.get_day().d;
    }

    Month& operator++(Month& month) {
        month == Month::dec ? month = Month::jan
                            : month = Month{static_cast<int>(month) + 1};
        return month;
    }



    Date operator/(Date date, Day day) {
        return date.set_day(day);
    }

    Date operator/(Year year, Month month) {

        return {month,year};
    }
}