//
// Created by Dmytrenko Kyrylo on 06.12.2025.
//
module;
#include "../error.h"
module exercises7;

namespace exercises7::ex9 {
    std::vector<double> sum(const std::vector<double> & price, const std::vector<double> & weight) {
        if (price.size() != weight.size())
            error("must be equivalent size");

        std::vector<double> result (weight.size());

        for (int i = 0; i < weight.size(); ++i) {
            result[i] = weight[i] * price[i];
        }

        return result;
    }
    void test() {
        std::vector<double> weight = {2.3, 3, 4, 5};
        std::vector<double> price = {3, 4, 5 ,5};

        auto sum = ex9::sum(price,weight);

        ex2::print(" ", sum);
    }
}