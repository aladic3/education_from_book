//
// Created by Dmytrenko Kyrylo on 09.12.2025.
//

module;

#include <ostream>
#include <ranges>
#include "../../error.h"
module chapter8;

namespace ch8::try_drill_ex {
    const std::vector months_with_30_days {Month::apr, Month::jun, Month::sep, Month::nov};
    bool is_30_day(Month m) {
        for ( auto el: months_with_30_days) {
            if (m == el)
                return true;
        }
        return false;
    }
    bool Date::is_day(const int dd) const {
        if (month == Month::feb ) {
            if (is_leapyear(year.y)) {
                return dd >= 1 && dd <= 29;
            }

            return dd >= 1 && dd <= 28;
        }

        if (is_30_day(month))
            return dd >= 1 && dd <= 30;

        return dd >= 1 && dd <= 31;
    }

    bool Date::is_month(const Month mm) {
        return month_to_int(mm) >= 1 && month_to_int(mm) <= 12;
    }

    bool Date::is_year(const int yy) {
        return yy > 0;
    }

    bool Date::is_date(Year yy, Month mm, Day dd) {
        if (is_month(mm) && is_year(yy.y) && is_day(dd.month_day))
            return true;

        return false;
    }

    void Date::increment_30_day_month_edge() {
        ++this->month; //increment month
        //set day to default with this condition
        day = Day{1, year.y,month}; //increment day
    }

    void Date::increment_31_day_month_edge() {
        //increment year
        if (this->month == Month::dec) // if 31/12
            ++this->year.y;
        ++this->month; //increment month

        //set day to default with this condition
        day = Day{1, year.y,month}; //increment day
    }

    void Date::increment_standard_day_of_month() {
        this->day = Day{day.month_day+1, year.y,month}; //increment day
    }
    Date& Date::add_one_day() {
        if (this->day.month_day == 30 && is_30_day(month)) {
            increment_30_day_month_edge();
        } else if (this->day.month_day == 31) {
            increment_31_day_month_edge();
        }
        else
            increment_standard_day_of_month();

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

    Date &Date::set_day(int day){
        if (is_day(day))
            this->day = Day{day,year.y,month};
        else
            error("u have a bad day");

        return *this;
    }

    Date& Date::set_month(Month month) {
        if (is_month(month)) {
            this->month = month;
            day = Day{day.month_day,year.y,month};
        }
        else
            error("u have a bad month");

        return *this;
    }
    Date& Date::set_year(Year year) {
        if (is_year(year.y)) {
            this->year = year;
            day = Day{day.month_day,year.y,month};
        }
        else
            error("u have a bad year");

        return *this;
    }

    Weekday Date::get_weekday() const {
        return day.weekday;
    }

    Date Date::next_workday() const {
        Date weekday_date{*this};
        //0 - sat, 1 - sun ...
        Weekday wd;
        do {
            weekday_date.add_one_day();
            wd = weekday_date.get_weekday();
        } while (wd == Weekday::sat || wd == Weekday::sun);



        return weekday_date;
    }

    int Date::calculate_day_of_year() {
        auto m_count = static_cast<int>(month);
        int sum = 0;
        for (int i = 1; i < m_count; ++i) { // month started from 1
            if (Month{i} == Month::feb ) { // feb, mb leapyear
                if (is_leapyear(year.y))
                    sum+=29;
                else
                    sum+=28;
                continue;
            }

            if (is_30_day(Month{i}))
                sum+=30;
            else
                sum+=31;

        }

        sum+=day.month_day;

        return sum;
    }

    int Date::week_of_year() {
        auto sum =  calculate_day_of_year();
        auto dayOfWeekOfJan1 = static_cast<int>(Date{year}.get_weekday()) - 1;
        sum += dayOfWeekOfJan1;
        return sum%7 == 0 ? sum / 7: sum/7 +1;
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


    const std::vector<std::string> week_vec{
        "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"
    };

    std::string week_to_str(Weekday w) {
        return week_vec[static_cast<int>(w)];
    }

    std::ostream& operator<<( std::ostream& os, const Month month) {
        return os << month_to_str(month);
    }

    std::ostream& operator<< (std::ostream& os, const Weekday w) {
        return os << week_to_str(w);
    }

    std::ostream& operator<<(std::ostream& os, const Date& d)  {
        return os << d.get_year().y << '/' << d.get_month() << '/' << d.get_day().month_day << " " << d.get_weekday();
    }


    Month& operator++(Month& month) {
        month == Month::dec ? month = Month::jan
                            : month = Month{static_cast<int>(month) + 1};
        return month;
    }



    Date operator/(Date date, int day) {
        return date.set_day(day);
    }

    Date operator/(Year year, Month month) {

        return {month,year};
    }
}