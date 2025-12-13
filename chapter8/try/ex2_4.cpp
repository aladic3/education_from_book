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





    void Name_pairs_v2::read_ages() {
        if (this->name_ages.empty())
            error("Pairs not exist, but must. Read_ages member func.");

        double input;

        for (auto & pairs : this->name_ages) {
            std::cout << "Enter age for " << pairs.get_name() << ": ";
            input_stream >> input;

            if (!is_valid_age(input))
                error("Age is can't exist");

            pairs.set_age(input);
        }

    }
    void Name_pairs_v2::read_names() {
        std::string input;
        std::cout << prompt_input_names;

        if (!name_ages.empty())
            clear_name_pairs();

        skip_spaces();
        while (skip_spaces() != '\n') {
            this->input_stream >> input;
            this->name_ages.push_back(Name_pair{input});
        }
    }

    void Name_pairs_v2::print(std::ostream& os) const{
        for (auto& el: this->name_ages) {
            os << el.get_name() << ": " << el.get_age() << '\n';
        }
    }

    std::vector<std::string> Name_pairs_v2::get_vector_names() const{
        std::vector<std::string> res;
        for (const auto& el: name_ages) {
            res.emplace_back(el.get_name());
        }
        return res;
    }

    std::vector<double> Name_pairs_v2::get_vector_ages() const{
        std::vector<double> res;
        for (const auto& el: name_ages) {
            res.emplace_back(el.get_age());
        }
        return res;
    }

    void Name_pairs_v2::sort() { // "4","3","1","2" -> "1", "2", "3", "4". sort by names
        for (int i = 0; i < name_ages.size() - 1; ++i)
            for (int j = i+1; j < name_ages.size(); ++j) {
                auto& a = name_ages[i];
                auto& b = name_ages[j];
                const auto& a_name = a.get_name();
                const auto& b_name = b.get_name();

                auto str_iterator = get_str_iterator(a_name, b_name);

                if (a_name[str_iterator] > b_name[str_iterator]) //first symbol in name
                    std::swap(a,b);
            }


    }

    int Name_pairs_v2::get_str_iterator(const std::string& a_name, const std::string & b_name) {
        int str_iterator = 0;
        unsigned long size_less = a_name.size() < b_name.size() ? a_name.size() : b_name.size();

        while (str_iterator < size_less && a_name[str_iterator] == b_name[str_iterator])
            ++str_iterator;

        return str_iterator;
    }

    //    private:
    bool Name_pairs_v2::is_valid_age(double age) {
        if (!this->input_stream)
            error("Bad input age!");

        return age >= 0 && age <= max_age;

    }
    char Name_pairs_v2::skip_spaces() const {
        char ch;
        this->input_stream.get(ch);

        while (std::isspace(ch) && ch != '\n') // omit spaces
            this->input_stream.get(ch);

        if (ch != '\n')
            this->input_stream.putback(ch);

        return ch;
    }
    void Name_pairs_v2::clear_name_pairs() {
        name_ages.erase(name_ages.begin(), name_ages.end());
    }

    void Name_pairs_v2::test() {
        Name_pairs_v2 name_pairs1(std::cin);
        Name_pairs_v2 name_pairs2(std::cin);
        name_pairs1.read_names();
        name_pairs1.read_ages();
        name_pairs1.print(std::cout);
       // name_pairs1.sort();
       // std::cout << "sorted:\n";
      //  name_pairs1.print(std::cout);

        name_pairs2.read_names();
        name_pairs2.read_ages();
        name_pairs2.print(std::cout);
     //   name_pairs2.sort();
       // std::cout << "sorted:\n";
      //  name_pairs2.print(std::cout);

        if (name_pairs1 == name_pairs2) {
            std::cout << "Equals";
        } else if (name_pairs1 != name_pairs2) {
            std::cout << "not Equals";
        } else {
            std::cout << "noppp";
        }
    }

    bool is_equals(const Name_pairs_v2& sorted1, const Name_pairs_v2& sorted2 ) {
        const auto& pairs1 = sorted1.get_pairs();
        const auto& pairs2 = sorted2.get_pairs();

        for (int i = 0; i < sorted1.size(); ++i) {
            if (pairs1[i].get_name() != pairs2[i].get_name()) // compare names
                return false;

            if (pairs1[i].get_age() != pairs2[i].get_age()) // compare ages
                return false;
        }

        return true;
    }

    bool comparison(Name_pairs_v2 n_p1, Name_pairs_v2 n_p2) {
        if (n_p1.size() != n_p2.size())
            return false;

        n_p1.sort();
        n_p2.sort();

        return is_equals(n_p1,n_p2);
    }

    std::ostream& operator<<(std::ostream& os, const Name_pairs& n_p) {
        n_p.print();
        return os;
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

    std::ostream& operator<<(std::ostream& os, const Name_pairs_v2& n_p) {
        n_p.print(os);
        return os;
    }
    bool operator==(const Name_pairs_v2& n_p1, const Name_pairs_v2& n_p2) {
        return comparison(n_p1,n_p2);
    }
    bool operator!=(const Name_pairs_v2& n_p1, const Name_pairs_v2& n_p2) {
        return !operator==(n_p1, n_p2);
    }

}
