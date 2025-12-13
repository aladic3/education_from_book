//
// Created by Dmytrenko Kyrylo on 08.12.2025.
//
module;

#include <iostream>
#include <ostream>
#include <utility>
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

namespace ch8::ex2_4 {
    struct Name_pair;

    export class Name_pairs {
    public:
        Name_pairs(): input_stream(std::cin) {}
        explicit Name_pairs(std::istream& is): input_stream(is){}

        void read_ages();
        void read_names();
        void print() const;
        void sort();
        [[nodiscard]] const std::vector<std::string>& get_names() const{ return this->names;}
        [[nodiscard]] const std::vector<double>& get_ages() const {return this->ages;}

        static void test();
    private:
        void reorganize_ages(const std::vector<std::string> & copy_names,
                const std::vector<double>& copy_ages);

        int find_index(const std::string& element, const std::vector<std::string>& vector);
        bool is_valid_age(double age);
        char skip_spaces() const;
        void clear_ages_names();

        std::istream& input_stream;
        std::vector<std::string> names;
        std::vector<double> ages;
    };

    struct  Name_pair {
        explicit Name_pair(std::string str): name(std::move(str)){};

        void set_name(const std::string &name) { this->name = name;}
        void set_age(double age) { this->age = age;  }


        [[nodiscard]] const std::string& get_name()const {  return name; }
        [[nodiscard]] double get_age()const { return age; }

    private:
        std::string name;
        double age = 0;
    };

    export class Name_pairs_v2 {
    public:
        Name_pairs_v2(): input_stream(std::cin) {}
        explicit Name_pairs_v2(std::istream& is): input_stream(is){}

        void read_ages();
        void read_names();
        [[nodiscard]] const std::vector<Name_pair>& get_pairs()const {return name_ages;}
        [[nodiscard]] size_t size()const{return name_ages.size();}
        void print(std::ostream&) const;
        void sort();
        static void test();

    private:
        [[nodiscard]] std::vector<std::string> get_vector_names() const;
        [[nodiscard]] std::vector<double> get_vector_ages() const;
        int get_str_iterator(const std::string& a_name, const std::string & b_name);
        bool is_valid_age(double age);
        [[nodiscard]] char skip_spaces() const;
        void clear_name_pairs();

        std::istream& input_stream;
        std::vector<Name_pair> name_ages;

    };

    bool is_equals(const Name_pairs_v2& sorted1, const Name_pairs_v2& sorted2);
    bool comparison(const Name_pairs& sorted_first, const Name_pairs& sorted_second);
    bool comparison(Name_pairs_v2 n_p1, Name_pairs_v2 n_p2);
    export std::ostream& operator<<(std::ostream& os, const Name_pairs& n_p);
    export std::ostream& operator<<(std::ostream& os, const Name_pairs_v2& n_p);
    export bool operator==(const Name_pairs_v2& n_p1, const Name_pairs_v2& n_p2);
    export bool operator!=(const Name_pairs_v2& n_p1, const Name_pairs_v2& n_p2);
    export bool operator==(const Name_pairs& n_p1, const Name_pairs& n_p2);
    export bool operator!=(const Name_pairs& n_p1, const Name_pairs& n_p2);

}