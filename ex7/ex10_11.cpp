//
// Created by Dmytrenko Kyrylo on 07.12.2025.
//
module;
#include <algorithm>
#include <iostream>

module exercises7;


namespace exercises7::ex10_11{
     int maxv(const std::vector<int>& input_v) {
          int max = input_v.front();
          for (const auto& element: input_v) {
               if (element > max)
                    max = element;
          }

          return max;
     }

     int minv(const std::vector<int>& input_v) {
          int min = input_v.front();
          for (const auto& element: input_v) {
               if (element < min)
                    min = element;
          }

          return min;
     }

     double median_v(const std::vector<int>& input_v) {
          auto copy_v = input_v;

          std::sort(copy_v.begin(),copy_v.end());
          const auto& sorted_v = copy_v;
          const auto size  = input_v.size();
          const auto half_size = size /2;

          return size % 2 == 0 ? (sorted_v[half_size-1] + sorted_v[half_size]) / 2.
               : sorted_v[half_size+1];

     }

     int sum_vec(const std::vector<int>& vec) {
          int sum = 0;
          for (const auto& el: vec) {
               sum+=el;
          }

          return sum;
     }

     double mean_v(const std::vector<int>& input_v) {
          double mean = static_cast<double>(sum_vec(input_v))/
               static_cast<double>(input_v.size());

          return mean;
     }
     Properties_of_vector calculate_properties_of_vector(const std::vector<int>& vec) {
          Properties_of_vector properties_of_vector = {
               median_v(vec),
               maxv(vec),
               minv(vec),
               mean_v(vec)

          };
          return properties_of_vector;
     }

     void test() {
          Properties_of_vector pr1 = calculate_properties_of_vector({1,2,34,0,3,-3});
          Properties_of_vector pr2 = calculate_properties_of_vector({1,2,343,0,3,-32,2});

          std::cout << "pr1: max " << pr1.max_value << " min " << pr1.min_value
               << " mean " << pr1.mean << " median " << pr1.median;


          std::cout << "pr1: max " << pr2.max_value << " min " << pr2.min_value
               << " mean " << pr2.mean << " median " << pr2.median;
     }
}
