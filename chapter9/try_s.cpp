//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;

#include <fstream>
#include <iomanip>
#include <iostream>
#include <strstream>
#include <string>

#include "../error.h"


//import chapter8;

module try_drill;

namespace ch9::ex3 {
    [[nodiscard]] std::vector<std::string> read_file(const std::string& file_name) {
       return ex1::read_file(file_name);
    }
    void write_to_file(const std::string& file_name, const std::vector<std::string>& vec) {
        auto ofs = ex1::open_output_stream(file_name);
        for (const auto& el: vec) {
            ofs << el << ' ';
        }
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
         /*<< std::setw(width) <<  row.first_name << '|'
            << std::setw(width) << row.last_name << '|'
            << std::setw(width) << row.email << '|'
            << std::setw(width) << row.t_number << '\n';*/

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
         std::ifstream ifs = ex1::open_input_stream(file_name);

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
         std::ofstream ofs = ex1::open_output_stream(file_name);
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
         std::ofstream ofs = ex1::open_output_stream(file_name);

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
         //write_points_to_file(filename,{Point{1,2}, Point{4,5}});
         //print_points(read_points_from_file(filename));

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