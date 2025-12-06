//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include <vector>
#include <iostream>
module exercises7;

namespace exercises::ex5_6 {
    std::vector<int> reverse_const(const std::vector<int>& input_vec) {
        auto result = std::vector<int>{};

        for (int i = static_cast<int>(input_vec.size()) - 1; i>=0; --i) {
            result.push_back(input_vec[i]);
        }

        return result;
    }

    void reverse_ref(std::vector<int> & input_vec) {

        const auto  limit = input_vec.size()/2;
        auto step = input_vec.size() - 1;
        for (int i = 0; i < limit; ++i) {
            std::swap(input_vec[i], input_vec[step--]);
        }

    }

    std::vector<std::string> reverse_const(const std::vector<std::string>& input_vec) {
        auto result = std::vector<std::string>{};

        for (int i = static_cast<int>(input_vec.size()) - 1; i>=0; --i) {
            result.push_back(input_vec[i]);
        }

        return result;
    }
    void reverse_ref(std::vector<std::string> & input_vec) {
        const auto  limit = input_vec.size()/2;
        auto step = input_vec.size() - 1;
        for (int i = 0; i < limit; ++i) {
            std::swap(input_vec[i], input_vec[step--]);
        }
    }

    void test() {
        std::vector input_vec = {1,2,34,5,6,4,2};
        ex2::print(" " , input_vec);
        auto vec = ex5_6::reverse_const(input_vec);
        ex2::print(" ",vec);


        ex2::print(" " , input_vec);
        ex5_6::reverse_ref(input_vec);
        ex2::print(" ", input_vec);

        // test string
        std::vector<std::string> input_vec_s = {"ds", "x", "sdfsdf", "dsf", "sdfsdf"};
        ex2::print(" " , input_vec_s);
        auto vec_s = ex5_6::reverse_const(input_vec_s);
        ex2::print(" ",vec_s);


        ex2::print(" " , input_vec_s);
        ex5_6::reverse_ref(input_vec_s);
        ex2::print(" ", input_vec_s);

    }
}