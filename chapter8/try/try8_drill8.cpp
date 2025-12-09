//
// Created by Dmytrenko Kyrylo on 09.12.2025.
//

module;
#include <iostream>
#include <ostream>
#include "../../error.h"
module try8;

namespace ch8:: try_drill {
    bool is_day(const int dd) {
        return dd > 0 && dd < 32;
    }

    bool is_month(const Month mm) {
        return month_to_int(mm) >= 1 && month_to_int(mm) <= 12;
    }

    bool is_year(const int yy) {
        return yy > 0;
    }

    bool is_date(Year yy, Month mm, Day dd) {
        if (is_month(mm) && is_year(yy.y) && is_day(dd.d))
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
}