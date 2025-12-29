//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;

#include <fstream>
#include <iomanip>
#include <iostream>

#include "../error.h"

//import chapter8;

module try_drill;


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
         std::ifstream ifs {file_name};
         std::vector<Point> points;
         Point p{};

         if (!ifs)
             error("Can't open input file");

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
         std::ofstream ofs {file_name};

         if (!ofs)
             error("can't  open output file");

         !write_points_to_filestream(ofs,points);


     }

    std::vector<Point> read_from_prompt(){
        std::vector<Point> p_vector;
        constexpr int count_points = 7;
        std::cout << std::format("Enter {} points: ", count_points);

        for (int i = 0; i < count_points && std::cin; ++i) {
            Point p{};
            std::cin >> p;

            if (!std::cin)
                error("Bad input");

            p_vector.push_back(p);

        }

         return p_vector;
    }

    std::vector<Point> write_points_to_file_with_prompt(const std::string& file_name) {
         std::ofstream ofs {file_name};

         if (!ofs)
             error("Can't open output file");

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