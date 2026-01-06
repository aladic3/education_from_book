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
    export enum class Weekday;
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



    export  std::ostream& operator<< (std::ostream& os, Weekday w);
    export  std::ostream& operator<<( std::ostream& os, Month month);
    export std::ostream& operator<<(std::ostream& os, const Date& d);
    export std::istream& operator>>(std::istream& is, Date& d);
    export Month& operator++(Month& month);
    export Weekday& operator++(Weekday& weekday);


    export Date operator/(Date date, int day);
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

    enum class Weekday {
        sat, sun, mon, tue, wed, thu,fri
    };



    struct Day {
        int month_day;
        Weekday weekday;
        long int days_from_1970; // 1 jan 1970 is Thu

        Day(int md, int yy, Month mm):month_day(md) {
            day_init_from_all_date(md,yy,mm);
            days_from_1970 = calculate_days_from_unix_epoch(md,yy,mm);
        }

        void add_Day(int limit) {
            ++month_day;
            ++weekday;
            ++days_from_1970;

            if (month_day > limit)
                month_day = 1;
        }
    private:
        static long int calculate_days_from_unix_epoch(int md, int yy, Month mm);
        void day_init_from_all_date(int md,int yy,Month mm);
    };

    struct Year {
        int y;
        Year(int yy): y(yy){}
    };



    class Date {
    public:
        Date(Year yy, Month mm, int dd):year(yy),month(mm), day(dd,yy.y,mm) {
            if (!is_date(year, month,day))
                error("bad date");
        }

        explicit Date(Year yy):year(yy), month(Month::jan), day(1,year.y,month) {
            if (!is_date(yy, month, day))
                error("bad date");

        }

        Date(Month mm, Day dd): year(2001), month(mm), day(dd.month_day, year.y,month) {
            if (!is_date(year, mm,dd))
                error("bad date");
        }
        Date(Month mm, Year yy): year(yy), month(mm), day(1,yy.y,mm) {
            if (!is_date(yy, mm,day))
                error("bad date");
        }

        Date():year(2001), month(Month::jan), day(1,year.y,month){}

        Date& add_days(int);
        Date& add_one_day();

        Date& set_day(int day);
        Date& set_month(Month month);
        Date& set_year(Year year);
        [[nodiscard]] Weekday get_weekday() const;
        Date next_workday() const;
        int week_of_year();

        static bool is_leapyear(int);
        [[nodiscard]]  Year get_year() const{ return year;}
        [[nodiscard]]  Month get_month() const{ return month;}
        [[nodiscard]]  Day get_day() const{ return day;}
    private:
        int calculate_day_of_year(); // in year 365 or 366 days
        static bool is_day(int,Month month, int year) ;
        bool is_month(Month);
        bool is_year(int);
        bool is_date(Year yy, Month mm, Day dd);

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


namespace ch8::ex5_9 {
    class Patron;
    export class Library;

    export class Book;
    export enum class Genre {
        first, fiction, periodical, nonfiction, biography, children, last
    };

    export std::ostream& operator<<(std::ostream& os, const Book& b);
    std::ostream& operator<<(std::ostream& os, Genre g);

    class Book {
    public:

        Book()= default;
        explicit Book(const std::string& isbn) {
            set_isbn(isbn);
            set_genre(Genre::fiction);
            set_author("Anonym");
            set_title("Nothing");
            set_copyright_date(try_drill_ex::Date{});
        }
        Book(const std::string& isbn,const std::string& author,
                const std::string& title, const try_drill_ex::Date& copyright_date, Genre genre) {
            set_genre(genre);
            set_isbn(isbn);
            set_author(author);
            set_title(title);
            set_copyright_date(copyright_date);

        }


        [[nodiscard]] const std::string & get_isbn() const {
            return isbn;
        }

        void set_isbn(const std::string &isbn);

        [[nodiscard]] const std::string & get_author() const {
            return author;
        }

        void set_author(const std::string &author) {
            this->author = author;
        }

        [[nodiscard]] const std::string & get_title() const {
            return title;
        }

        void set_title(const std::string &title) {
            this->title = title;
        }

        [[nodiscard]] const try_drill_ex::Date & get_copyright_date() const {
            return copyright_date;
        }

        void set_copyright_date(const try_drill_ex::Date &copyright_date) {
            this->copyright_date = copyright_date;
        }

        [[nodiscard]] Genre get_genre() const {return genre;}
        void set_genre(Genre genre);
        static void test();

        bool operator==( const Book& b2) const {
            return isbn == b2.get_isbn();
        }

        bool operator!=( const Book& b2) const {
            return isbn != b2.get_isbn();
        }

    private:
        std::string isbn {"1-1-1-1"};
        std::string author {"Anonym"};
        std::string title {"Enigma"};
        try_drill_ex::Date copyright_date;
        Genre genre = Genre::fiction;
    };





    class Library {
        struct Transaction;
    public:
        void add_book(const std::string& isbn,const std::string& author,
                const std::string& title, const try_drill_ex::Date& copyright_date, Genre genre);
        void add_book(const Book& book);
        //void add_patron(const Patron&);
        void check_out_book(const std::string& isbn, const std::string & user_name);
        void create_and_register_patron(const std::string&);
        [[nodiscard]] std::vector<std::string> get_names_patrons_with_fee() const;
        static void test();


    private:
        void check_patron_repetition(const std::string& user_name) const;
        void check_book_repetition(const std::string& isbn) const;
        [[nodiscard]] int generate_library_card_number();
        [[nodiscard]] const Book& get_book_from_library(const std::string& isbn) const;
        [[nodiscard]] Patron&get_patron_from_library(const std::string &user_name);
        void delete_book_from_library(const Book&);
        void create_and_register_transaction(const Book &, Patron &patron);


        std::vector<Book> books_;
        std::vector<Patron> patrons_;
        std::vector<Transaction> transactions_;
        int next_card_number_ = 0;

    };

    // not exported, private
    class Patron {
    public:
        Patron():user_name("undefined"){}
        Patron(std::string username, int library_card_number): user_name(std::move(username)),
        library_card_number(library_card_number){}

        bool operator==(const Patron & p) const {
            return user_name == p.get_user_name()
                && library_card_number == p.get_library_card_number();
        }

        [[nodiscard]] const std::string & get_user_name() const {
            return user_name;
        }



        [[nodiscard]] int get_library_card_number() const {
            return library_card_number;
        }



        [[nodiscard]] int get_library_fee() const {
            return library_fee;
        }

        void increment_fee() {
            ++library_fee;
        }

        [[nodiscard]] bool owes_fee() const {
            return library_fee != 0;
        }



    private:
        std::string user_name;
        int library_card_number = 0;
        int library_fee = 0;
    };

}

namespace ch8::ex13 {
    export class Rational;



    class Rational {
    public:
        Rational() = default;
        Rational(int integer){ operator=(integer);}
        Rational(double non_integer){ operator=(non_integer);}
        Rational(long long int num, long long int den): numerator(num), denominator(den) { validate_denominator(denominator);}

        static void validate_denominator(long long int);

        [[nodiscard]] long long int get_numerator() const { return numerator; }

        [[nodiscard]] long long int get_denominator() const { return denominator; }

        Rational& simplify_rational();

        bool operator==(const Rational & l) const ;
        bool operator!=(const Rational & l) const ;
        Rational& operator=(int integer) ;
        Rational& operator=(double non_integer) ;

        void multiply_rational_by_long_long_int(long long int multiplier){numerator*=multiplier; denominator*=multiplier;}
        [[nodiscard]] double get_double() const {return static_cast<double>(numerator)/static_cast<double>(denominator);}

    private:

        void reduce_rational_by(long long int value);
        long long int numerator = 0;
        long long int denominator = 1;
    };

    export Rational operator+(Rational r, Rational l);

    export Rational operator-(Rational r, Rational l) ;

    export Rational operator*(const Rational& r, const Rational& l);

    export Rational operator/(const Rational& r, const Rational& l) ;




    export void test();


}


namespace ch8::ex14_15 {
    const  std::vector<std::string> _currency_prompt {"", "USD", "DKK", "UAH", "" };

    export class Money;

    export enum class Currency {
        begin, USD, DKK, UAH, end
    };

    class  Money {
    public:

        Money(const double& amount_currency);
        Money(const double& amount_currency, Currency crr);


        [[nodiscard]] std::string get_currency_prompt() const { return _currency_prompt[static_cast<int>(_currency)];};
        void set_currency(Currency crr);
        void set_monetary_amount(double amount_currency);
        void conversion_this_to_dollars();
        [[nodiscard]] long int get_cents() const {return _monetary_amount;}
        [[nodiscard]] double get_and_set_dollars_amount() ;
        [[nodiscard]] double get_currency_amount() const ;
        [[nodiscard]] double get_dollars_amount() const ;

    private:

        long int _monetary_amount = 0;
        Currency _currency = Currency::USD;

        const std::vector<double> _conversion_factors {-1., 1., 0.5, 40., -1 }; // {begin, ..., end}



        [[nodiscard]] long int get_monetary_amount_in_dollars() const;
        [[nodiscard]] static double monetary_to_currency(long int monetary_amount) ;
    };

    [[nodiscard]]Currency get_currency_from_string(std::string&); // throw error

    export std::ostream& operator<<(std::ostream& os, const Money& money);
    export std::istream& operator>>(std::istream& is, Money& money);
    export Money operator+(const Money& m1, const Money& m2);
    export Money operator-(const Money& m1, const Money& m2);
    export void test();

}