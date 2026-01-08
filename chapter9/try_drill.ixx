//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;

#include <string>
#include <utility>
#include <vector>
#import <iostream>

#include "../error.h"
import chapter8;

export module try_drill;


namespace ch9 {
    export void write_to_file(const std::string& file_name, const std::vector<std::string>& vec);
    export void print_vec_of_strings(const std::vector<std::string>& vec);
    export std::ostream& operator<<(std::ostream& os, const std::vector<char>& file); //print file
    export std::istream& operator>>(std::istream& is,  std::vector<char>& file); //read from stream
    export std::vector<double> read_doubles_from_file(const std::string& filename, char terminator = '|');
    export std::vector<int> read_ints_from_file(const std::string& filename, char terminator = '|');
    export std::ostream& operator<< (std::ostream& os, const ch8::try_drill_ex::Date& date);

    std::ifstream open_input_stream(const std::string& file_name);
    std::pair<std::string,std::string> split_after_and_before_word_and_symbols( std::string& word);
    std::ofstream open_output_stream(const std::string& file_name);
    std::vector<std::string> get_separated_words_from_stream(std::istream& is);
    std::vector<std::string> read_words_from_stream(std::istream& is); //symbols after word is separated

    void read_double(std::istream& is, std::vector<double>& vec);
    void read_ints(std::istream& is, std::vector<int>& vec);
    void try_recover_from_fail_bit(std::istream& is, char terminator= '|');
}

namespace ch9::ex21_22 {
    export class Roman;


    int roman_ch_to_int(char ch);
    bool is_valid_roman_str(const std::string& roman_str);
    bool is_valid_roman_int(int roman_int);
    int roman_str_to_int(const std::string& roman_str);
    std::string roman_int_to_str(int roman_int);
    void normalize_roman_str(std::string& roman_str); // to upper_case
    std::istream& operator>>(std::istream&, Roman& roman);
    std::ostream& operator<<(std::ostream&, const Roman& roman);

    class Roman {
    public:
        Roman(std::string roman_str):roman_str(std::move(roman_str)) {
            if (!is_valid_roman_str(roman_str))
                error("Bad string roman");

            normalize_roman_str(roman_str);
            roman_int = roman_str_to_int(roman_str);
        }
        Roman(int roman_int):roman_int(roman_int) {
            if (!is_valid_roman_int(roman_int))
                error("Bad int roman");

            roman_str = roman_int_to_str(roman_int);
        }

        const std::string& get_roman_str()const {return roman_str;}
        int get_roman_int() const {return roman_int;}
        void set_roman_str(const std::string& roman_str);
        void set_roman_int(int roman_int);

    private:
        std::string roman_str{"I"};
        int roman_int = 1;
    };
}

namespace ch9::ex14_16 {
    export std::vector<double> read_doubles_from_file(const std::string& filename, char terminator = '|');
    export std::vector<int> read_ints_from_file(const std::string& filename, char terminator = '|');

    void increase_count_of_value(std::vector<std::pair<int,int>>& value_counts, int value);

    export void write_formatted_doubles_to_file(const std::string& filename, const std::vector<double>& vec);
    export void write_formatted_pairs_to_file(const std::string& filename, const std::vector<std::pair<int,int>>& vec);
    export std::vector<std::pair<int,int>> calculate_count_each_integer_in_vector(const std::vector<int>& vec);
    int get_sum(const std::vector<int>& vec);

    void sort_pairs(std::vector<std::pair<int,int>>& vec);

    export void test();
}

namespace ch9::ex17_19 {


    export struct  Reading {
        Reading(const ch8::try_drill_ex::Date& date, int h, double t, char suffix = 'f'):
                _date(date), _hour(h), _temperature(t){
            if (h < 0 || h > 23)
                error("bad hour in Reading.");

            valid_suffix(suffix);

        }
        [[nodiscard]] ch8::try_drill_ex::Date date() const {return _date;}
        [[nodiscard]] int hour() const{return _hour;}
        [[nodiscard]] double temperature() const {return _temperature;}
        [[nodiscard]] char suffix() const {return _suffix;}
    private:
        ch8::try_drill_ex::Date _date;
        int _hour; //[0;23]
        double _temperature; //in Fahrenheit
        char _suffix;

        void valid_suffix(char suffix);
    };


    std::vector<double> get_temperatures(const std::vector<Reading>& readings);
    export std::pair<double,double> calculate_mean_and_median(const std::vector<Reading>& readings);

    export std::vector<Reading> input_readings(const std::string& file_name);
    export void print_readings(const std::string& file_name, const std::vector<Reading>& readings);

    export void test();


}

namespace ch9::ex13 {
    export struct Classifications {
        Classifications() = default;

        int letter = 0;
        int whitespace = 0;
        int decimal = 0;
        int hexadecimal = 0;
        int uppercase = 0;
        int lowercase = 0;
        int control = 0;
        int punct = 0;
        int printable = 0;
        int grahp = 0;
        int alphanumeric = 0;

        int generous_count_char = 0;

    };


    export Classifications read_and_get_classifications(const std::string& filename);
    void classification_single_char(Classifications& classifications, char ch);

    export void test();

}

namespace  ch9::ex11 {
    export std::vector<char> read_file_to_char_vector(const std::string& filename);
    export std::vector<std::string> read_file_to_str_vector(const std::string& filename);
    export void reverse_order_of_characters( std::vector<char>& file);
    export void reverse_order_of_words(std::vector<std::string>& file);

    export void test();

}

namespace ch9::ex9_10 {
    export std::vector<std::string> split(const std::string& s);
    export std::vector<std::string> split(const std::string& s, const std::string& w); //w is characters


    std::vector<std::string> get_separated_words_from_string(const std::string& s, const std::string& w);

    export void test();
}

namespace ch9::ex5 {
    export std::vector<std::string> read_std_cin(char terminator);
    export void print(const std::vector<std::pair<char,std::string>>&, const std::string& );
    export std::vector<std::pair<char,std::string>> get_all_characters_classifications(const std::string& word);
    std::pair<char,std::string>  get_pair_one_character_classifications( char ch);

    export void test();

}

namespace ch9::ex3 {
    // using func for reading  ch9::ex1::read_file

    const std::vector<char> vowels {'a', 'e', 'i', 'o', 'u', 'y'};

    export [[nodiscard]] std::vector<std::string> read_file(const std::string& file_name);

    export void remove_vowels_from_vector(std::vector<std::string>& vec);
    void remove_vowels_from_word(std::string& word);
    bool is_vowel_letter( char letter);

    export void test();

}

namespace ch9::ex4 {
    export std::vector<std::string> read_std_cin(char terminator);
    export std::vector<int> convert_to_decimal(const std::vector<std::string>& wet_integers); // if one of them non int - error
    bool is_octal(const std::string& wet_integer);
    bool is_hex(const std::string& wet_integer);
    bool is_decimal(const std::string& wet_integer);
    int get_integer(const std::string& wet_integer);
    std::vector<std::string> prepare_wet_str_to_print(const std::vector<std::string>& wet_integers);
    export void print(const std::vector<std::string>& wet_integers, const std::vector<int>& integers);

    export void test();


}

namespace ch9::ex6 {

    const std::vector<std::pair<std::string,std::string>> nt_dictionary {
        {"don't","do not"},
        {"can't","cannot"},
        {"haven't","have not"},
        {"didn't","did not"},
        {"aren't", "are not"},
        {"you’re", "you are"}
    };

    export std::string get_line_of_formatted_string(const std::string& line); //start point
    export std::vector<std::string> get_sorted_and_formatted_words_from_file(const std::string& filename); //start point

    std::vector<std::string> get_formatted_words_from_stream(std::istream& is) ;  //essential part

    void format_by_dictionary(std::string& word);
    void sort_strings(std::vector<std::string>& str_vec) ;
    void add_word_separately_symbols_to_vector(const std::string& word,
        const  std::pair<std::string,std::string>& symbols,
        std::vector<std::string>& vector);

    std::vector<std::string> get_formatted_words_from_line(const std::string& line); //essential part

    std::string get_formatted_line_from_words(const std::vector<std::string>& words); // for print







    export std::string replace_punctuation_with_whitespace(const std::string& str);

    export void test();
}

namespace ch9::ex1 {
    export [[nodiscard]] std::vector<std::string> read_file(const std::string& file_name);
    export [[nodiscard]] std::vector<std::string>read_line_file(const std::string& file_name);
    export void write_line_to_file(const std::string& file_name, const std::vector<std::string>& vec);
    export  std::vector<std::string>& convert_to_lower(std::vector<std::string>& input_lines);



    export void print_str_vec(const std::vector<std::string>& str_v, std::ostream& os);
    export void print_vec_with_line_num(const std::vector<std::string>& str_v, std::ostream& os);

    std::string& str_tolower(std::string& s);

    export void test();

}

namespace ch9::drill {
    export void print_birthyear();
    export void try_reading_different_bases();

    struct UserInfo {
        std::string first_name;
        std::string last_name;
        std::string t_number;
        std::string email;
    };

    export class UserInfoTable {
    public:
        UserInfoTable()= default;
        explicit UserInfoTable(std::vector<UserInfo> table):_table(std::move(table)){};
        void add_row_to_table(const UserInfo& user_info){_table.push_back(user_info);}
        [[nodiscard]] const std::vector<UserInfo>& get_table() const{ return _table;}




    private:
        std::vector<UserInfo> _table;

    };

    std::ostream& print_table_vector(std::ostream& os, const std::vector<UserInfo>& table_vec);
    export std::ostream& operator<<(std::ostream& os, const UserInfoTable& table);
    export  std::ostream& operator<<(std::ostream& os, const UserInfo& row);
    std::vector<UserInfo> test_create_vector_table();
    export  void test_table();
}


namespace  ch9::drill11 {
    export struct Point {
        int x;
        int y;
    };


    export std::vector<Point> read_points_from_file(const std::string& file_name);
    export  void write_points_to_file(const std::string& file_name, const std::vector<Point>& points);
    export std::vector<Point> write_points_to_file_with_prompt(const std::string& file_name);

    std::vector<Point> read_points_count_times(int count_points, std::istream& is);
    std::vector<Point> read_from_prompt();
    std::ofstream& write_points_to_filestream(std::ofstream& ofs, const std::vector<Point>& points);
    void print_points(const std::vector<Point>& points_v);

    export  void test();

    export std::istream& operator>>(std::istream& is,  Point& p);
    export std::ostream& operator<<(std::ostream& os, const Point& p);


}

namespace ch9::try_s {
    export void print_birthyear();
    export void test_format();
}