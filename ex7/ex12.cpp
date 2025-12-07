//
// Created by Dmytrenko Kyrylo on 07.12.2025.
//
module;
#include <iostream>

module exercises7;

namespace exercises7::ex12 {
     void print_until_s(const std::vector<std::string>& input, const std::string& quit) {
         for (const auto & element: input) {
             if (element == quit)
                 break;

             std::cout << element << ' ';
         }

         std::cout << std::endl;
     }

    //doing also how it's doing first version, but exit after second quit reached
     void print_until_ss(const std::vector<std::string>& input, const std::string& quit) {
         bool is_had_first_quit = false;
         for (const auto & element: input) {

             //exit from print after reach 2 quit strings
             if (!is_had_first_quit && element == quit) {
                 is_had_first_quit = true;
                 continue;
             }


             if (is_had_first_quit && element == quit)
                 break;

             std::cout << element << ' ';
         }

         std::cout << std::endl;
     }

     void test() {
        std::vector<std::string> strings {
            "ds", "hs", "ps", "ds", "hs", "ps", "ds", "hs", "ps"};

         print_until_s(strings, "ps");
         print_until_ss(strings,"ps");
     }
}
