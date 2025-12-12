//
// Created by Dmytrenko Kyrylo on 12.12.2025.
//
module;
#include <algorithm>
#include <iostream>

#include "../../error.h"
module chapter8;


namespace ch8::ex2_4 {
    const std::string prompt_input_names = "Enter names space separate, when final just press 'Enter':\n";

    constexpr double max_age = 300;

    bool Name_pairs::is_valid_age(double age) {
        if (!this->input_stream)
            error("Bad input age!");

        return age >= 0 && age <= max_age;
    }

    void Name_pairs::read_ages() {
        if (names.empty())
            error("Names not exist, but must!");


        double input;

        for (auto & name : names) {
            std::cout << "Enter age for " << name << ": ";
            input_stream >> input;

            if (!is_valid_age(input))
                error("Age is can't exist");

            ages.push_back(input);
        }

    }

    char Name_pairs::skip_spaces() const {
        char ch;
        this->input_stream.get(ch);

        while (std::isspace(ch) && ch != '\n') // omit spaces
            this->input_stream.get(ch);

        if (ch != '\n')
            this->input_stream.putback(ch);

        return ch;
    }

    void Name_pairs::clear_ages_names() {
        this->names.erase(names.begin(), names.end()); //clear names if exist
        this->ages.erase(ages.begin(),ages.end());// clear ages if exist
    }


    void Name_pairs::read_names() {
        std::string input;
        std::cout << prompt_input_names;

        if (!names.empty()) {
            clear_ages_names();
        }

        skip_spaces();
        char input_char;
        do {

            // last char returned
            if (skip_spaces() == '\n') break;

            this->input_stream >> input;
            this->names.push_back(input);
            this->input_stream.get(input_char);
        } while (input_char != '\n');
    }

    void Name_pairs::print() const {
        for (int i = 0; i < this->names.size(); ++i) {
            std::cout << names[i] << ": " << ages[i] << std::endl;
        }
    }



    int Name_pairs::find_index(const std::string& element, const std::vector<std::string>& vector) {
        for (int i = 0; i < vector.size(); ++i) {
            if (element == vector[i]) return i;
        }

        error("str not exist in this vec");
        return -1;
    }

    void Name_pairs::reorganize_ages(const std::vector<std::string>& copy_names,
                                        const std::vector<double>& copy_ages) {
        for (int i = 0; i < names.size(); ++i) {
            int index_of_non_sorted_vec = find_index(names[i], copy_names);
            ages[i] = copy_ages[index_of_non_sorted_vec];
        }
    }

    void Name_pairs::sort() {
            if (names.size() != ages.size())
                error("size of vectors must be equivalent");

            const auto copy_names = names;
            const auto copy_ages = ages;

            std::ranges::sort(names.begin(), names.end());

            reorganize_ages(copy_names, copy_ages);

        }

    void  Name_pairs::test() {
        Name_pairs name_pairs1(std::cin);
        Name_pairs name_pairs2(std::cin);
        name_pairs1.read_names();
        name_pairs1.read_ages();
        name_pairs1.print();
        /*name_pairs1.sort();
        std::cout << "sorted:\n";
        name_pairs1.print();*/

        name_pairs2.read_names();
        name_pairs2.read_ages();
        name_pairs2.print();
        /*name_pairs2.sort();
        std::cout << "sorted:\n";
        name_pairs1.print();*/
        if (name_pairs1 == name_pairs2) {
            std::cout << "Equals";
        } else if (name_pairs1 != name_pairs2) {
            std::cout << "not Equals";
        } else {
            std::cout << "noppp";
        }
    }

    std::ostream& operator<<(std::ostream& os, const Name_pairs& n_p) {
        n_p.print();
        return os;
    }
    bool is_vec_str_equals(const std::vector<std::string>& v1, const std::vector<std::string>& v2) {
        for (int i = 0; i < v1.size(); ++i) {
            if (v1[i] != v2[i])
                return false;
        }

        return true;
    }
    bool is_vec_double_equals(const std::vector<double>& v1, const std::vector<double>& v2) {
        for (int i = 0; i < v1.size(); ++i) {
            if (v1[i] != v2[i])
                return false;
        }

        return true;
    }

    bool comparison(const Name_pairs& sorted_first, const Name_pairs& sorted_second) {
        const auto& first_n = sorted_first.get_names();
        const auto& second_n = sorted_second.get_names();

        if (first_n.size() != second_n.size())
            return false;

        const auto& first_a = sorted_first.get_ages();
        const auto& second_a = sorted_second.get_ages();


        if (!is_vec_double_equals(first_a,second_a))
            return false;

        if (!is_vec_str_equals(first_n,second_n))
            return false;


        return true;
    }

    bool operator==(const Name_pairs& n_p1, const Name_pairs& n_p2) {
        auto copy1 = n_p1;
        auto copy2 = n_p2;
        // comparison after sort
        copy1.sort();
        copy2.sort();
        return comparison(copy1,copy2);
    }

    bool operator!=(const Name_pairs& n_p1, const Name_pairs& n_p2) {
        return !(n_p1 == n_p2);
    }
}
