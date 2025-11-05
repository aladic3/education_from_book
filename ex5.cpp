//
// Created by Dmytrenko Kyrylo on 02.11.2025.
//
#include <random>
#include "error.h"
#include "iostream"


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



}


void seed2(std::__1::default_random_engine& engine) {
    int time = static_cast<int>(std::time(nullptr));
    engine.seed(time);

}


std::vector<char> generate_different_letters() {
    std::__1::default_random_engine random_engine;
    seed2(random_engine);


    std::vector<char> result (4,0);

    for (int i = 0; i < result.size(); ++i) {
        std::uniform_int_distribution<int> dist('a','z');

        while (result[i] == 0) {
            char random_letter = dist(random_engine);


            // flag for check unicum
            bool is_unicum = true;
            for (int j = 0; j < i; ++j) {
                if (result[j] == random_letter) {
                    is_unicum = false;
                    break;
                }
            }
            /*for (int element: result) {
                if (element == random_num) {
                    is_unicum = false;
                    break;
                }
            }*/


            result[i] = is_unicum ? random_letter : 0; // if element of vector not generated go again
        }
    }

    return  result;
}

char get_inputted_vec_in_alphabet(const char &input) {
    //check is alphabet char
    if (input >= 'a' && input <= 'z') return input;
    if (input >= 'A' && input <= 'Z') return input+32;

    // else

    error("bad input");
}


std::pair<int,int> calculate_bulls_cows_v2(const std::vector<char>& inputted_vec,
    const std::vector<char>& generated_vec, const int size_vec) {
    std::pair<int,int> bulls_and_cows = {0,0};
    for (int i = 0; i < size_vec; ++i) {

        for (int j = 0; j < size_vec; ++j) {
            if (inputted_vec[i] == generated_vec[j] && i == j) {++bulls_and_cows.first; break;}

            if (inputted_vec[i] == generated_vec[j] && i != j) {++bulls_and_cows.second; break;}
        }
    }

    return bulls_and_cows;
}

void game_bulls_cows_v2() {
    std::string answer = "y";

    while (answer == "y") {
        std::vector<char> generated_vec = generate_different_letters();
        const int size_num = static_cast<int>(generated_vec.size());
        std::pair<int,int> bulls_cows = {0,0};



        std::cout << "Enter letters (size " << size_num << "): ";

        // while input and bulls < size_num (4)
        for (std::string number; bulls_cows.first < size_num && std::cin >> number; ) {

            if (!std::cin || number.size() > size_num)
                error("bad input!");

            std::vector<char> inputted_vec;

            // add and check to vector our input
            for (char & letter: number) {
                char true_letter = get_inputted_vec_in_alphabet(letter);
                inputted_vec.push_back(true_letter);
            }


            bulls_cows = calculate_bulls_cows_v2(inputted_vec,generated_vec,size_num);

            std::cout << "Bulls = " << bulls_cows.first << " Cows = " << bulls_cows.second << std::endl;


        }


        std::cout << "Congratulations! You win!" << std::endl << "If you would proceed new game, input 'y': ";
        std::cin >> answer;


    }




}

