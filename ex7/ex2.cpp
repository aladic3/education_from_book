//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include <iostream>
#include <vector>
module exercises7;

namespace exercises::ex2 {
    void print(const std::string& output_label, const std::vector<int>& vector) {
        for (auto& el: vector) {
            std::cout << output_label << el << std::endl;
        }

    }
    void print_v2(const std::string& output_label, const std::vector<int>& vector) {
        for (int i = 0; i < vector.size(); ++i) {
            std::cout << output_label << vector[i] << " index: " << i << std::endl;
        }

    }


    void test() {
        print("Vector el:", {1,3,4,5,212,32,0});

        ex2::print("Is hell? ", std::vector<int>(1000,1));

        print_v2("Vector el:", {1,3,4,5,212,32,0});

        ex2::print_v2("Is hell? ", std::vector<int>(1000,1));
    }
}
