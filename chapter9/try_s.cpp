//
// Created by Dmytrenko Kyrylo on 24.12.2025.
//
module;
#include <iomanip>
#include <iostream>
import chapter8;

module try_drill;

using namespace ch8::try_drill_ex;
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
}
namespace ch9::try_s {
    void print_birthyear() {
        Date birthday {2002,Month::jul, 31};
        std::cout << std::setw(10) << std::setfill('0') << birthday << std::hex << "\t" << birthday
            << std::oct <<"\t" << birthday ;


    }

    void test_format() {
        double d = 1234.56789;
        int i = 60;
        std::cout <<  std::format("-{:13a}-{:10.3f}-{:40.20e}-{:#08b}\n", d,d,d, i);
    }

}