//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;

#include <fstream>
#include <string>
#include <utility>
#include <vector>
#import <iostream>

#include "../error.h"


export module try_drill;
export import chapter8;

namespace ch9::test {
    export struct Roman_test_helper {
        inline static std::vector<std::pair<std::string,int>> good_romans_2 = {
        {"I", 1},
        {"II", 2},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"VI", 6},
        {"IX", 9},
        {"X", 10},
        {"XI", 11},
        {"XIV", 14},
        {"XV", 15},
        {"XIX", 19},
        {"XX", 20},
        {"XL", 40},
        {"XLIV", 44},
        {"XLIX", 49},
        {"L", 50},
        {"LVIII", 58},
        {"LX", 60},
        {"XC", 90},
        {"XCIV", 94},
        {"XCIX", 99},
        {"C", 100},
        {"CXL", 140},
        {"CL", 150},
        {"CD", 400},
        {"CDXLIV", 444},
        {"D", 500},
        {"DXC", 590},
        {"CM", 900},
        {"CMXC", 990},
        {"M", 1000},
        {"MCM", 1900},
        {"MCMXL", 1940},
        {"MCMXC", 1990},
        {"MCMXCIV", 1994},
        {"MM", 2000},
        {"MMXXIII", 2023},
        {"MMXL", 2040},
        {"MMCD", 2400},
        {"MMCM", 2900},
        {"MMM", 3000},
        {"MMMCM", 3900},
        {"MMMCMXC", 3990},
        {"MMMCMXCV", 3995},
        {"MMMCMXCIX", 3999},
        {"D", 500},
        {"L", 50},
        {"V", 5}
    };

        inline static std::vector<std::string> bad_romans_2 = {
        // запрещённые повторы
        "IIII",
        "VV",
        "LL",
        "DD",
        "MMMM",

        // неправильные вычитания
        "IL",
        "IC",
        "ID",
        "IM",
        "VX",
        "XD",
        "XM",
        "LC",
        "LD",
        "DM",

        // двойное / цепное вычитание
        "IIV",
        "IIX",
        "XXC",
        "CCM",

        // нарушение канонической структуры
        "MCMC",
        "CMC",
        "CMCM",
        "XCX",
        "IXI",
        "IXX",

        // некорректные формы чисел
        "VIV",
        "LIL",
        "DCD",
        "VIIII",
        "LXXXX",
        "DCCCC",

        // мусор / не-римские
        "ABC",
        "A",
        "X1V",
        "MCMXCI!",
        "",
        " ",
        " I",
        "I ",
        "X V",

        // прочие некорректные
        "IMX",
        "MXM",
        "DDM",
        "IIIV"
    };


        inline static std::vector<std::pair<std::string, int>> good_romans = {

        {"MMMCMXCIX", 3999},
        {"V", 5},
        {"MCM", 1900},
        {"MM", 2000},
        {"L", 50},
        {"LVIII", 58},
        {"VI", 6},
        {"D", 500},


        {"IX", 9},
        {"X", 10},
        {"XIV", 14},
        {"XV", 15},
        {"XIX", 19},
        {"XX", 20},
        {"IV", 4},
        {"XL", 40},
        {"XLIV", 44},
        {"XLIX", 49},

        {"III", 3},

        {"XC", 90},
        {"XCIV", 94},
        {"C", 100},
        {"CD", 400},
        {"CDXLII", 442},

        {"I", 1},
        {"II", 2},
        {"CM", 900},
        {"CMXLIV", 944},
        {"M", 1000},
        {"MCMXCIV", 1994},
        {"MMXXIV", 2024},

    };

        inline static std::vector<std::string> bad_romans = {
        "IIV",
        "XXC",      // неправильный порядок
        "MCMC",     // повтор вычитательной конструкции
        "IIII",     // > 3 повторов I
        "VV",       // V нельзя повторять
        "LL",       // L нельзя повторять
        "DD",       // D нельзя повторять
        "VX",       // нельзя вычитать V
        "IL",       // I нельзя вычитать из L
        "IC",       // I нельзя вычитать из C
        "ID",       // запрещено
        "IM",       // запрещено
        "XM",       // X нельзя вычитать из M
        "XD",       // X нельзя вычитать из D
        "LC",       // L не участвует в вычитании
        "DM",       // D не участвует в вычитании

        "DDM",      // повтор D + порядок
        "MMMM",     // > 3999
        "ABC",      // мусор
        "",         // пустая строка
    };
    };

}

namespace ch9 {
    export void print_str_vec(const std::vector<std::string>& str_v, std::ostream& os);
    export void write_to_file(const std::string& file_name, const std::vector<std::string>& vec);
    export void print_vec_of_strings(const std::vector<std::string>& vec);
    export std::ostream& operator<<(std::ostream& os, const std::vector<char>& file); //print file
    export std::istream& operator>>(std::istream& is,  std::vector<char>& file); //read from stream
    export std::vector<double> read_doubles_from_file(const std::string& filename, char terminator = '|');
    export std::vector<int> read_ints_from_file(const std::string& filename, char terminator = '|');
    export std::ostream& operator<< (std::ostream& os, const ch8::try_drill_ex::Date& date);

    export [[nodiscard]] std::ifstream open_input_stream(const std::string& file_name);
    export [[nodiscard]] std::ifstream open_input_stream_file_system(const std::string &file_name_path);
    std::pair<std::string,std::string> split_after_and_before_word_and_symbols( std::string& word);
    export [[nodiscard]] std::ofstream open_output_stream(const std::string& file_name);
    export std::vector<std::string> get_separated_words_from_stream(std::istream& is);
    std::vector<std::string> read_words_from_stream(std::istream& is); //symbols after word is separated

    void read_double(std::istream& is, std::vector<double>& vec);
    void read_ints(std::istream& is, std::vector<int>& vec);
    void try_recover_from_fail_bit(std::istream& is, char terminator= '|');
    export int get_number_from_strint(std::string& str);

    export [[nodiscard]] std::vector<std::string> read_file(const std::string& file_name);
    export [[nodiscard]] std::vector<std::string>read_lines_file(const std::string& file_name);
    export void write_lines_to_file(const std::string& file_name, const std::vector<std::string>& vec);
}

namespace ch9::ex23_24 {
    std::vector<std::string> get_concatenation_vector(const std::vector<std::string>& read_result_1,
            const std::vector<std::string> & read_result_2);
    //return name new file
    export std::string concatenates_two_files(const std::string& f_name1, const std::string& f_name2);

    //Write a program that takes two files containing sorted whitespace-separated words and
    //merges them, preserving order.
    export std::vector<std::string> merge_two_already_sorted_files(const std::string& f_name1, const std::string& f_name2);
    std::string read_stream_and_return_last(std::string& word, std::ifstream& stream);
    export class Sorting_Read {
        std::ifstream input_stream_1, input_stream_2;
        std::string word_1, word_2;

        std::string read_stream_1_and_get_last_word();
        std::string read_stream_2_and_get_last_word();

    public:
        Sorting_Read(const std::string& file_name1, const std::string& file_name2):
                        input_stream_1(open_input_stream(file_name1)),
                        input_stream_2(open_input_stream(file_name2)) {
            input_stream_1 >> word_1;
            input_stream_2 >> word_2;
        }

        std::string get_next_str();
    };

    export std::vector<int> get_vector_integers_from_file(const std::string& file_name);
    export int get_sum_integers_from_vector(const std::vector<int>& vec_numbers);



    export void test();

}

namespace ch9::ex21_22 {
    export class Roman;

    export struct Roman_helper {
        inline static const std::vector<std::pair<char,int>> basic_values{
                {'M',1000},
                {'D',500},
                {'C', 100},
                {'L', 50},
                {'X', 10},
                {'V', 5},
                {'I', 1}
        };
        static constexpr  std::string non_repeatable_romans {"VLD"};
        static constexpr std::string all_possible_romans {"VLDIXCM"};
        inline static const std::vector<std::pair<char,std::string>> subtractions_rules{
                {'I',"XV"},
                {'X',"LC"},
                {'C',"DM"}
        };
    };


    bool is_inputted_by_int(const std::string& i_string, Roman& roman);
    bool is_inputted_by_string(const std::string& i_string, Roman& roman);
    bool is_good_subtraction(char current_roman, char last_roman);
    bool is_good_repeating(char last_roman, char current_roman, int& count_repeat);
    bool is_roman(char current_roman);
    int roman_ch_to_int(char ch);
    char roman_int_to_ch(int r);
    bool is_valid_roman_str(const std::string& roman_str);
    bool is_valid_roman_int(int roman_int);
    int roman_str_to_int(const std::string& roman_str);
    std::string roman_int_to_str(int roman_int);

    export std::istream& operator>>(std::istream& is, Roman& roman);
    export std::ostream& operator<<(std::ostream& os, const Roman& roman);

    export void test();

    class Roman {
    public:
        Roman()= default;
        Roman(const std::string& roman_str):roman_str(roman_str) {
            if (!is_valid_roman_str(roman_str))
                error("Bad string roman:"+roman_str);

            roman_int = roman_str_to_int(roman_str);
        }
        Roman(int roman_int):roman_int(roman_int) {
            roman_str = roman_int_to_str(roman_int);
        }

        [[nodiscard]] const std::string& get_roman_str()const {return roman_str;}
        [[nodiscard]] int get_roman_int() const {return roman_int;}
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
    export bool is_decimal(const std::string& wet_integer);  //ch9::ex4::
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

    export  std::vector<std::string>& convert_to_lower(std::vector<std::string>& input_lines);




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