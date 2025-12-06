//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include <algorithm>
#include <vector>
#include <iostream>
#include "../error.h"
module exercises7;

namespace exercises7::ex7_8 {
     int find_index(const std::string& element, const std::vector<std::string>& vector) {
          for (int i = 0; i < vector.size(); ++i) {
               if (element == vector[i]) return i;
          }

          error("str not exist in this vec");
          return -1;
     }




     void sort_ref(std::vector<std::string> &names, std::vector<double> &ages) {
          if (names.size() != ages.size())
               error("size of vectors must be equivalent");

          const auto copy_names = names;
          const auto copy_ages = ages;

          std::ranges::sort(names.begin(), names.end());

          for (int i = 0; i < names.size(); ++i) {
               int index_of_non_sorted_vec = find_index(names[i], copy_names);
               ages[i] = copy_ages[index_of_non_sorted_vec];
          }
     }

     void print(const std::vector<std::string> &names, const std::vector<double> &ages) {
          for (int i = 0; i < names.size(); ++i) {
               std::cout << names[i] << " " << ages[i] << std::endl;
          }

     }

     void test() {
          std::vector<std::string> names = {"Kirill", "Danil", "Olek", "Alec", "Sanya"};
          std::vector<double> ages = {13, 23, 33, 55, 33};


          ex7_8::print(names, ages);
          std::cout << std::endl;

          sort_ref(names,ages);
          ex7_8::print(names,ages);

     }
}