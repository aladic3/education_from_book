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
            std::cout << el << output_label;
        }

        std::cout << std::endl;
    }

    void print(const std::string& output_label, const std::vector<std::string>& vector) {
        for (auto& el: vector) {
            std::cout << el << output_label;
        }

        std::cout << std::endl;
    }



    void print_v2(const std::string& output_label, const std::vector<int>& vector) {
        for (int i = 0; i < vector.size(); ++i) {
            std::cout << output_label << vector[i] << " index: " << i << std::endl;
        }

    }




    void test() {
        print(":", {1,3,4,5,212,32,0});

        ex2::print("? ", std::vector<int>(1000,1));

        print_v2("el:", {1,3,4,5,212,32,0});

        ex2::print_v2("Is hell? ", std::vector<int>(1000,1));
    }
}
