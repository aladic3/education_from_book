//
// Created by Dmytrenko Kyrylo on 02.11.2025.
//
#include <iostream>


class Name_value {
public:
    std::string name;
    int score = 0;
};


void names_scores_pairs_v2() {
    std::vector<Name_value> name_values;

    std::string input_name;
    int input_score;

    std::cout << "Enter unicum name and score: ";

    while (std::cin >> input_name && std::cin >> input_score) {
        if (input_score == 0 && input_name == "NoName") {
            break;
        }


        for (auto &[name, score]: name_values) {
            if (input_name == name) {
                std::cout << "Error! Such name is exist in this vector!";
                return;
            }
        }


        name_values.push_back({input_name,input_score});

        std::cout << "Enter unicum name and score: ";
    }

    std::cout << "Enter name to find score: ";
    bool is_find = false;

    while (std::cin >> input_name) {
        if (input_name == "NoName")
            break;

        for (int i = 0; i < name_values.size(); ++i) {
            if (name_values[i].name == input_name) {
                std::cout << name_values[i].name << " " << name_values[i].score << "\n";
                is_find = true;
                break;
            }
        }

        if (is_find == false) {
            std::cout << "name not found\n";
        }

        std::cout << "Enter name to find score: ";
        is_find = false;
    }

    std::cout << "Enter score to find all names: ";
    while (std::cin >> input_score) {

        if (input_score == -1)
            break;

        for (int i = 0; i < name_values.size(); ++i) {
            if (name_values[i].score == input_score) {
                std::cout << name_values[i].name << " ";
                is_find = true;

            }
        }

        if (!is_find) {
            std::cout << "names not found\n";
        }

        is_find = false;
        std::cout << "\nEnter score to find all names: ";
    }

    // for (int i = 0; i < names.size(); ++i) {
    //     std::cout << names[i] << " " << scores[i] << "\n";
    // }


}

