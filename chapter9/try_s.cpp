//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <vector>
#include <utility>
#include "../error.h"


//import chapter8;

module try_drill;

namespace ch9 {
    std::pair<std::string,std::string> split_after_and_before_word_and_symbols( std::string& word) {
        std::string symbols_after_word;
        std::string symbols_before_word;

        while (!word.empty() && std::ispunct(word.back())) {
            symbols_after_word += word.back();
            word.pop_back();
        }

        while (!word.empty() && std::ispunct(word.front())) {
            symbols_before_word += word.front();
            word.erase(0,1);
        }

        return std::pair{symbols_before_word, symbols_after_word};
    }
    void write_to_file(const std::string& file_name, const std::vector<std::string>& vec) {
        auto ofs = open_output_stream(file_name);
        for (const auto& el: vec) {
            ofs << el << ' ';
        }
    }
    std::vector<std::string> read_words_from_stream(std::istream& is) {
        std::string word;
        std::vector<std::string> result;

        while (is >> word) {
            auto symbols_after_and_before_word = split_after_and_before_word_and_symbols(word);
            ex6::add_word_separately_symbols_to_vector(word,symbols_after_and_before_word,result);
        }

        return result;
    }
    void print_vec_of_strings(const std::vector<std::string>& vec) {
        for (const auto& el: vec ) {
            std::cout << el << std::endl;
        }
    }

    std::ifstream open_input_stream(const std::string& file_name) {
        std::ifstream ifs {file_name};
        if (!ifs)
            error("can't open file");

        return ifs;
    }
    [[nodiscard]]std::ofstream open_output_stream(const std::string& file_name) {
        std::ofstream ofs {file_name};
        if (!ofs)
            error("can't open file");

        return ofs;
    }

    std::ostream& operator<<(std::ostream& os, const std::vector<char>& file) {
        for (auto& ch: file) {
            os.put(ch);
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, std::vector<char>& file) {
        char ch;
        while (is.get(ch))
            file.push_back(ch);
        return  is;
    }
    std::vector<std::string> get_separated_words_from_stream(std::istream& is) {
        std::vector<std::string> vec;
        std::string str;

        while (is >> str) {
            vec.push_back(str);
        }

        return vec;
    }
}


namespace ch9::ex13 {
    Classifications read_and_get_classifications(const std::string& filename) {
        Classifications result;
        char ch;
        auto is = open_input_stream(filename);

        while (is.get(ch))
            classification_single_char(result,ch);

        return result;

    }
    void classification_single_char(Classifications& classifications, char ch) {
        std::vector<std::pair<bool, std::function<void()>>> classificating{
                {std::isalpha(ch),[&classifications] {classifications.letter++;}},
                {std::isspace(ch),[&classifications] {classifications.whitespace++;}},
                {std::isdigit(ch),[&classifications] {classifications.decimal++;}},
                {std::isxdigit(ch),[&classifications] {classifications.hexadecimal++;}},
                {std::isupper(ch),[&classifications] {classifications.uppercase++;}},
                {std::islower(ch),[&classifications] {classifications.lowercase++;}},
                {std::iscntrl(ch),[&classifications] {classifications.control++;}},
                {std::ispunct(ch),[&classifications] {classifications.punct++;}},
                {std::isprint(ch),[&classifications] {classifications.printable++;}},
                {std::isgraph(ch),[&classifications] {classifications.grahp++;}},
                {std::isalnum(ch),[&classifications] {classifications.alphanumeric++;}},
                {true,[&classifications] {classifications.generous_count_char++;}}
        };

        for (auto& [condition, action]: classificating)
            if (condition)
                action();



    }

    void test() {
        const std::string filename {"readme.txt"};
        auto classifications = read_and_get_classifications(filename);

    }

}


namespace  ch9::ex11 {
    std::vector<char> read_file_to_char_vector(const std::string& filename) {
        auto is = open_input_stream(filename);
        std::vector<char> file;
        is >> file;

        return file;

    }

    std::vector<std::string> read_file_to_str_vector(const std::string& filename) {
        auto is = open_input_stream(filename);
        std::vector<std::string> file = read_words_from_stream(is);

        return file;

    }
    void reverse_order_of_characters(std::vector<char>& file) {
        std::vector<char> reversed_file;
        reversed_file.reserve(file.size());
        const int size = static_cast<int>(file.size());

        for (int i = size-1; i>=0; --i)
            reversed_file.push_back(file[i]);


        file = reversed_file;
    }

    void reverse_order_of_words(std::vector<std::string>& file) {
        const auto file_size = file.size();
        for (int i = 0; i*2 < file_size;++i) {
            const auto left = i;
            const auto right = file_size - (i + 1);

            if (left == right) break;

            std::swap(file[left],file[right]);
        }
    }


    void test() {
        constexpr std::string filename_in {"readme.txt"};
        auto file  = read_file_to_char_vector(filename_in);
        reverse_order_of_characters(file);

        constexpr std::string filename_out {"readme_out.txt"};
        auto os  = open_output_stream(filename_out);
        os << file;
        os.close();

        constexpr std::string filename_out2 {"readme_out2.txt"};
        auto file2 = read_file_to_str_vector(filename_in);
        reverse_order_of_words(file2);
        write_to_file(filename_out2,file2);


    }


}

namespace ch9::ex9_10 {

    std::vector<std::string> get_separated_words_from_string(const std::string& s, const std::string& w) {
        std::vector<std::string> vec;
        std::string str;

        for (auto ch: s) {

            if (w.contains(ch) && str.empty())
                continue;

            if (w.contains(ch)) {
                vec.push_back(str);
                str.erase();
                continue;
            }

            str.push_back(ch);
        }

        if (!str.empty())
            vec.push_back(str);


        return vec;
    }


      std::vector<std::string> split(const std::string& s) {
          std::istringstream isn{s};
          return get_separated_words_from_stream(isn);
      }



      std::vector<std::string> split(const std::string& s, const std::string& w) {//w is characters
            auto copy_w = w + ' '; //space also separating ch
            return get_separated_words_from_string(s,copy_w);
        }



      void test() {
        std::string line = "0xx73\t is hex,adeci!mal!\n";
        std::cout << "original: " << line << std::endl;
        std::cout << "split_v1:\n";
        print_vec_of_strings(split(line));
        std::cout << "split_v2:\n";
        print_vec_of_strings(split(line,"x,!"));

    }
}

namespace ch9::ex5 {
    void print(const std::vector<std::pair<char,std::string>>& classifications, const std::string& word) {
        std::cout <<"\"\"\"" << word << "\"\"\":\n";
        for (const auto& pair: classifications)
            std::cout << std::format("'{}': {}\n",pair.first,pair.second);

    }
    std::vector<std::string> read_std_cin(char terminator) {
        return  ex4::read_std_cin(terminator);
    }
    std::vector<std::pair<char,std::string>> get_all_characters_classifications(const std::string& word) {
        std::vector<std::pair<char,std::string>> result;
        result.reserve(word.size());

        for (auto ch: word) {
            result.push_back(get_pair_one_character_classifications(ch));
        }

        return result;
    }

    std::string get_str_from_vec_classifications(const std::vector<std::pair<bool,std::string>>& classifications) {
        std::string result;
        for (const auto& el: classifications) {
            result+=el.first?std::format("{};",el.second):"";
        }
        return result;
    }
    std::pair<char,std::string> get_pair_one_character_classifications( char ch) {
        std::vector<std::pair<bool,std::string>> classifications{
            {std::isalpha(ch),"letter"},
            {std::isspace(ch),"whitespace"},
            {std::isdigit(ch),"decimal digit"},
            {std::isxdigit(ch),"hexadecimal digit"},
            {std::isupper(ch),"uppercase letter"},
            {std::islower(ch),"lowercase letter"},
            {std::iscntrl(ch),"control character"},
            {std::ispunct(ch),"punct"},
            {std::isprint(ch),"printable"},
            {std::isgraph(ch),"grahp"},
            {std::isalnum(ch),"alphanumeric"}
        };

        return std::pair {ch,get_str_from_vec_classifications(classifications)};

    }

    void test() {
        std::string word = "0x73\t is hexadecimal!\n";
        print(get_all_characters_classifications(word),word);
    }

}



namespace ch9::ex6 {



    void format_by_dictionary( std::string& word) { // return init word if not found
        std::string temp = word;
        ex1::str_tolower(temp);
        for (const auto& el: nt_dictionary) {
            if (temp == el.first) {
                word = el.second;
                return;
            }
        }

    }


    void add_word_separately_symbols_to_vector(const std::string& word,
        const std::pair<std::string,std::string>& symbols,
        std::vector<std::string>& vector)
    {
        if (!symbols.first.empty())
            vector.push_back(symbols.first);

        if (!word.empty())
            vector.push_back(word);

        if (!symbols.second.empty())
            vector.push_back(symbols.second);
    }

    std::vector<std::string> get_formatted_words_from_line(const std::string& line) {
        std::istringstream isn{line};
        std::vector<std::string> result = get_formatted_words_from_stream(isn);
        return result;
    }

    void sort_strings(std::vector<std::string>& str_vec) {
        std::ranges::sort(str_vec.begin(), str_vec.end());
    }



    std::vector<std::string> get_formatted_words_from_stream(std::istream& is) {
        std::vector<std::string> result = read_words_from_stream(is);

        for (auto& word: result)
            format_by_dictionary(word);

        return result;
    }

    std::vector<std::string> get_sorted_and_formatted_words_from_file(const std::string& filename) {
        auto isf = open_input_stream(filename);
        std::vector<std::string> result = get_formatted_words_from_stream(isf);
        sort_strings(result);

        return result;
    }

    std::string get_formatted_line_from_words(const std::vector<std::string>& words) {
        std::string result;

        for (const auto& word: words) {

            result+= std::ispunct(word.front())
                ?word //symbol
                :std::format(" {}",word);//just word
        }

        return result.substr(1,result.size()-1); //first spase
    }

    std::string get_line_of_formatted_string(const std::string& line) { //start point
        auto words = get_formatted_words_from_line(line);
        auto result = get_formatted_line_from_words(words);
        return result;
    }


    std::string replace_punctuation_with_whitespace(const std::string& str) {
        auto copy_str = str;
        for (auto it = copy_str.begin(); it != copy_str.end(); ++it) {
            if (*it == '"') //inside double quotes not changes
            {
                ++it;
                while (*it != '"' && it!=copy_str.end())
                    ++it;
            }

            if (it == copy_str.end())
                break;

            if (std::ispunct(*it))
                *it = ' ';
        }

        return copy_str;
    }

    void test() {
        std::string original {"Didn't\" -- S,o cu!ete \"pl?s!\"?\nAren't\" you haven't a problem?"};
        const std::string filename {"readme.txt"};
        try {

            std::cout << replace_punctuation_with_whitespace(original) << std::endl;
            std::cout << get_line_of_formatted_string(original) << std::endl;
            print_vec_of_strings(get_sorted_and_formatted_words_from_file(filename));
        } catch (std::exception& ex) {
            std::cerr << ex.what();
        }

    }
}


namespace ch9::ex4 {
    std::vector<std::string> read_std_cin(char terminator) {
        std::vector<std::string> result;
        std::cout << std::format("Input integers in hex/oct or decimal"
                                 " format. Use {} for stop inputting: ",terminator);

        while (std::cin) {
            std::string input;

            std::cin >> input;

            if (input[0] == terminator || input.empty())
                break;

            result.push_back(input);
        }

        return  result;
    }

    bool is_octal(const std::string& wet_integer) {
        std::istringstream is {wet_integer};
        char ch;
        is.get(ch);

        if (ch != '0')
            return false;

        while (is.get(ch)) {
            auto n = ch - '0';

            if (!(n >= 0 && n <=7))
                return false;

        }

        return true;
    }
    bool is_hex(const std::string& wet_integer) {

        if (wet_integer.substr(0,2) != "0x")
            return false;

        for (auto ch: wet_integer.substr(2,wet_integer.size())){
            if (!std::isxdigit(ch))
                return false;

        }

        return true;
    }
    bool is_decimal(const std::string& wet_integer) {
        for (auto ch: wet_integer) {
            if (!std::isdigit(ch))
                return false;
        }

        return true;
    }

    int get_integer(const std::string& wet_integer) {
        std::istringstream is {wet_integer};
        int result = 0;

        if (is_hex(wet_integer))
            is >> std::hex >> result;
        else if (is_octal(wet_integer))
            is >> std::oct >> result;
        else if (is_decimal(wet_integer))
            is >> std::dec >> result;

        else
            error("bad input");

        return result;

    }

    std::vector<int> convert_to_decimal(const std::vector<std::string>& wet_integers) {
        std::vector<int> result;
        result.reserve(wet_integers.size());

        for (const auto& wet_integer: wet_integers) {
            result.push_back(get_integer(wet_integer));
        }

        return result;
    }

    std::vector<std::string> prepare_wet_str_to_print(const std::vector<std::string>& wet_integers) {
        auto ws_copy = wet_integers;

        for (auto& wet_integer: ws_copy) {
            if (is_hex(wet_integer))
                wet_integer = std::format("{:10}\thexadecimal",wet_integer);
            else if (is_octal(wet_integer))
                wet_integer = std::format("{:10}\toctal",wet_integer);
            else if (is_decimal(wet_integer))
                wet_integer = std::format("{:10}\tdecimal",wet_integer);

        }

        return ws_copy;

    }

    void print(const std::vector<std::string>& wet_integers, const std::vector<int>& integers) {
        auto formatted_strings = prepare_wet_str_to_print(wet_integers);

        for (int i = 0; i < formatted_strings.size(); i++) {
            std::cout
                << std::format("{:30}\tconverts to{:10}\tdecimal\n",formatted_strings[i],integers[i]);
        }
    }

    void test() {
        auto wet_int = read_std_cin('|');
        auto integer = convert_to_decimal(wet_int);

        print(wet_int,integer);
    }





}

namespace ch9::ex3 {
    [[nodiscard]] std::vector<std::string> read_file(const std::string& file_name) {
       return ex1::read_file(file_name);
    }

    void remove_vowels_from_vector(std::vector<std::string>& vec) {
        for (auto& el: vec) {
            remove_vowels_from_word(el);
        }
    }
    void remove_vowels_from_word(std::string& word) {
        for (auto it = word.begin(); it != word.end(); ++it) {
            if (is_vowel_letter(*it)) {
                word.erase(it);
                --it;
            }

        }
    }
    bool is_vowel_letter( char letter) {
        if (!std::isalpha(letter))
            return false;

        for (auto vowel: vowels)
            if (static_cast<int>(vowel) == std::tolower(letter))
                return true;


        return false;
    }

    void test() {

            const std::string filename = "disemvowels.txt";
            std::vector<std::string> letter {"Hello", "my", "little", "friend.", "How", "ARE", "YOU?"};

            write_to_file(filename,letter);
            auto from_file_vec = read_file(filename);

        try {
            remove_vowels_from_vector(from_file_vec);

            ex1::print_vec_with_line_num(from_file_vec,std::cout);
        } catch (std::exception& ex) {
            std::cerr << ex.what();

        }
    }


}



namespace ch9::ex1 {

    std::vector<std::string> read_file(const std::string& file_name) {
        std::vector<std::string> result;
        auto ifs = open_input_stream(file_name);


        while (ifs) {
            std::string input;

            ifs >> input;

            if (input.empty())
                continue;

            result.push_back(input);
        }

        return  result;
    }

    std::vector<std::string> read_line_file(const std::string& file_name) {
        std::vector<std::string> result;
        auto ifs = open_input_stream(file_name);

        while (ifs) {
            std::string input;

            std::getline(ifs,input);

            if (input.empty())
                continue;

            result.push_back(input);
        }

        return  result;
    }
    void write_line_to_file(const std::string& file_name, const std::vector<std::string>& vec) {
        auto ofs = open_output_stream(file_name);
        print_str_vec(vec,ofs);


    }
    std::string& str_tolower(std::string& s) //from cpprefference
    {
        std::transform(s.begin(), s.end(), s.begin(),
                    // static_cast<int(*)(int)>(std::tolower)         // wrong
                    // [](int c){ return std::tolower(c); }           // wrong
                    // [](char c){ return std::tolower(c); }          // wrong
                       [](unsigned char c){ return std::tolower(c); } // correct
                      );
        return s;
    }
    std::vector<std::string>& convert_to_lower(std::vector<std::string>& input_lines) {
        for (auto& line:input_lines)
           str_tolower(line);

        return input_lines;
    }

    void print_str_vec(const std::vector<std::string>& str_v, std::ostream& os) {
        for (const auto& el: str_v)
            os << el << std::endl;
    }

    void print_vec_with_line_num(const std::vector<std::string>& str_v, std::ostream& os) {
        for (int i = 0; i<str_v.size(); ++i)
            os << str_v[i] << '\t'<< i << std::endl;
    }

    void test() {
        const std::string file_name = "test.txt";
        std::vector<std::string> test_v {"SDFaaw", "fdfEWWE", "SDFwerewr"};
        write_line_to_file(file_name,test_v);
        auto from_file = read_file(file_name);
        print_str_vec(convert_to_lower(from_file), std::cout);
        print_vec_with_line_num(from_file,std::cout);


    }

}

//using namespace ch8::try_drill_ex;
namespace ch9::drill {
     void print_birthyear() {
         int birth_year = 2001;
         int age = 39;
         double d = 1234567.89;
         std::cout << "decimal:" << std::setw(10) << std::showbase << birth_year << '\t'
            << std::hex << "hexadecimal:" << birth_year << '\t'
            << std::oct << "octal:" << birth_year << '\t'
            << std::dec << "decimal age:" << age << '\n'
            << std::format("{:a}\t{:f}\t{:e}\n",d,d,d);
     }

    void try_reading_different_bases() {
         int a,b,c;

         std::cin >> std::hex >> a >> std::oct >> b >> std::dec >> c;

         std::cout << std::format("{:*<#10x}\t{:#010o}\t{:#012b}\n",a,b,c);
     }

    std::ostream& operator<<(std::ostream& os, const UserInfoTable& table){
         return print_table_vector(os,table.get_table());
     }

    std::ostream& print_table_vector(std::ostream& os, const std::vector<UserInfo>& table_vec) {
         for (const auto& el: table_vec)
             os << el;

         return os;
     }

    std::ostream& operator<<(std::ostream& os, const UserInfo& row){
         int width = 40;
         return os <<  std::format("|{:>20}\t|{:>20}\t|{:>40}\t|{:>15}\t|\n",
             row.first_name,row.last_name,row.email,row.t_number);


    }

    std::string get_test_email( int iterator){
        return  std::format("test_email_{:05d}@tmail.com",iterator);
     }
    std::string get_test_f_name( int iterator){
         return std::format("First{:05d}",iterator);

     }
    std::string get_test_l_name(int iterator){
         return std::format("Last{:05d}",iterator);

     }
    std::string get_test_t_number( int iterator){
         return std::format("{:010d}",iterator);
     }

    UserInfo get_test_user_info(int iterator) {
         UserInfo ui;
         ui.email = get_test_email(iterator);
         ui.last_name = get_test_l_name(iterator);
         ui.first_name = get_test_f_name(iterator);
         ui.t_number = get_test_t_number(iterator);

         return ui;
     }

    std::vector<UserInfo> test_create_vector_table() {
         std::vector<UserInfo> t_vector;

         for (int i = 0; i<100; ++i ) {
             UserInfo test_u_info = get_test_user_info(i);
             t_vector.push_back(test_u_info);
         }

         return t_vector;
     }

    void test_table() {
         UserInfoTable t {test_create_vector_table()};
         std::cout << t;


     }
}

namespace  ch9::drill11 {
     std::vector<Point> read_points_from_file(const std::string& file_name) {
         std::ifstream ifs = open_input_stream(file_name);

         std::vector<Point> points;
         Point p{};

         while (ifs >> p)
             points.push_back(p);

         return points;

     }
     std::ofstream& write_points_to_filestream(std::ofstream& ofs, const std::vector<Point>& points) {
         for (const auto& el: points) {
             ofs << el;
         }
         return ofs;
     }
     void write_points_to_file(const std::string& file_name, const std::vector<Point>& points) {
         std::ofstream ofs = open_output_stream(file_name);
         write_points_to_filestream(ofs,points);

     }

    std::vector<Point> read_points_count_times(const int count_points, std::istream& is){
        std::vector<Point> p_vector;
        for (int i = 0; i < count_points && is; ++i) {
            Point p{};
            is >> p;

            if (!is)
                error("Bad input");

            p_vector.push_back(p);

        }
        return p_vector;
    }

    std::vector<Point> read_from_prompt(){
        constexpr int count_points = 7;
        std::cout << std::format("Enter {} points: ", count_points);
        auto p_vector = read_points_count_times(count_points,std::cin);


         return p_vector;
    }

    std::vector<Point> write_points_to_file_with_prompt(const std::string& file_name) {
         std::ofstream ofs = open_output_stream(file_name);

         std::vector<Point> original_points = read_from_prompt();

         write_points_to_filestream(ofs,original_points);

         return original_points;

     }

    void print_points(const std::vector<Point>& points_v) {
         for (const auto& el: points_v) {
             std::cout << el;
         }
     }

    void test() {
         const std::string filename = "mydata.txt";

         auto original_points = write_points_to_file_with_prompt(filename);
         auto processed_points = read_points_from_file(filename);

         if (original_points.size() != processed_points.size())
             error("bad comparing");

         print_points(original_points);
         std::cout << std::endl;
         print_points(processed_points);

     }

     std::istream& operator>>(std::istream& is,  Point& p) {
         return is >> p.x >> p.y;
     }
     std::ostream& operator<<(std::ostream& os, const Point& p) {
        return os << p.x << '\t' << p.y << std::endl;
     }


}
namespace ch9::try_s {
    void print_birthyear() {
        int birthday = 23;
        std::cout << std::setw(10) << std::setfill('0') << birthday << std::hex << "\t" << birthday
            << std::oct <<"\t" << birthday ;


    }

    void test_format() {
        double d = 1234.56789;
        int i = 60;
        std::cout <<  std::format("-{:13a}-{:10.3f}-{:40.20e}-{:#08b}\n", d,d,d, i);
    }

}