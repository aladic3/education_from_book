//
// Created by Dmytrenko Kyrylo on 07.12.2025.
//
module;
#include <algorithm>
#include <vector>
#include <iostream>

#include "../error.h"

module exercises7;

namespace exercises7::ex13 {

    std::vector<int> get_sizes(const std::vector<std::string>& input) {
        std::vector<int> sizes (input.size());

        for (int i = 0; i < input.size(); ++i) {
            sizes[i] = static_cast<int>(input[i].size());
        }

        return sizes;
    }

    const std::string& get_shortest(const std::vector<std::string>& input) {
        if (input.empty())
            error("vector can't be empty!");

        const std::string* shortest = &input.front();

        for (int i = 1; i < input.size(); ++i) {
            if (input[i].size() < shortest->size())
                shortest = &input[i];
        }

        return *shortest;
    }

    const std::string& get_longest(const std::vector<std::string>& input) {
        if (input.empty())
            error("vector can't be empty!");

        const std::string* longest = &input.front();

        for (int i = 1; i < input.size(); ++i) {
            if (input[i].size() > longest->size())
                longest = &input[i];
        }

        return *longest;
    }

    std::vector<std::string> get_sorted_vec(const std::vector<std::string>& input) {
        auto copy = input;
        std::sort(copy.begin(), copy.end());

        return copy;
    }

    const std::string& get_lexicographically_last(const std::vector<std::string>& sorted_vector) {
        return sorted_vector.back();
    }

    const std::string& get_lexicographically_first(const std::vector<std::string>& sorted_vector) {
        return sorted_vector.front();
    }





    strings_details get_details_vec_str(const std::vector<std::string>& input) {
        strings_details details;
        std::vector<std::string> sorted_vec = get_sorted_vec(input);

        details.lexicographically_first = get_lexicographically_first(sorted_vec);
        details.lexicographically_last = get_lexicographically_last(sorted_vec);
        details.longest_str = get_longest(input);
        details.shortest_str = get_shortest(input);

        return details;
    }

    void test() {
        std::vector<std::string> strings {
            "banana", "apple", "Applepie", "100", "20", "B"};

        std::cout << "sizes: \n";
        ex2::print(" ",get_sizes(strings));

        auto details = get_details_vec_str(strings);

        std::cout << " ";
    }
}