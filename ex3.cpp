//
// Created by Dmytrenko Kyrylo on 03.07.2025.
//
#include <complex>
#include <iostream>
#include <vector>
#include "error.h"

int max(int,int);

void go_to_my_worck() { //begin from my home
    std::cout << "open the door, and go outside house. Turn left. Go to the street. Turn right. Go ahead.\n"
                 "While you reach the school right sight of you - turn on left. This street against school. \n"
                 "go ahead. while you reach end of street you can see front of you iron gates. Right of gates you\n"
                 "will see iron door. Guard open the door and you can go inside of my work place\n";
}


void print_each_char() {
    std::cout << "Input string: ";

    std::string str;
    std::cin >> str;
    int i = 0;

    for (char ch: str) {
        std::cout << ch << " " << i++ << "\n";
    }
}

void game_in_numbers() {
    char possible_num = 50;
    char upper = 100;
    char lower = 0;
    char answer;

    for ( int i = 0; i < 7; ++i) {
        std::cout << "You're num is greater then " << int(possible_num) << "? (y/n)\n";
        std::cin >> answer;


        switch (answer) {
            case 'y':
                lower = possible_num + 1;
                break;

            case 'n':
                upper = possible_num;
                break;

            default:
                return;

        }

        possible_num = (upper + lower) / 2;



    }
    std::cout << "Answer = " << int(possible_num);
}

void converts_digits() {
    std::vector<std::string> digits_str = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    std::string input_v;
    int number = 0;
    std::string result;

    while (std::cin >> input_v) {

        if (input_v == "ex")
            break;

        if (isdigit(input_v[0])) {
            int converted_num = std::stoi(input_v);

            if (converted_num > 9 || converted_num < 0) {
                result = "undefined";
            } else
                result = digits_str[converted_num];


        }
        else {
            for (auto str: digits_str) {
                if (str == input_v)
                    break;

                ++number;
            }

            if (number == 10) {
                result = "undefined";
                number = 0;
            } else {
                result = std::to_string(number);
                number = 0;
            }
        }
        std::cout << result << "\n";
    }

}

int convert_simple_digit(std::string input_v) {
        std::vector<std::string> digits_str = {
             "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
         };


        int number = 0;
        int result;

        if (isdigit(input_v[0])) {
            int converted_num = std::stoi(input_v);

            result = converted_num;
        }
        else {
            for (auto str: digits_str) {
                if (str == input_v)
                    break;

                ++number;
            }

            if (number == 10)
                result = std::numeric_limits<int>::min();
            else
                result = number;

        }
       return result;
}

void mini_calculator() {
    std::cout << "Pls enter operation, num, num (* 2.3 4): ";

    std::string operation;
    std::string s_num1, s_num2;
    int num1, num2;
    constexpr int min_int = std::numeric_limits<int>::min();

    std::cin >> operation >> s_num1 >> s_num2;

    num1 = convert_simple_digit(s_num1);
    num2 = convert_simple_digit(s_num2);

    if (num1 == min_int || num2 == min_int) {
        std::cout << "Error with read numbers\n";
        return;
    }

    if (operation == "*" || operation == "mul")
        std::cout << "result = " << num1 * num2;
    else if (operation == "/" || operation == "div")
        std::cout << "result = " << num1 / num2;
    else if (operation == "+" || operation == "plus")
        std::cout << "result = " << num1 + num2;
    else if (operation == "-" || operation == "minus")
        std::cout << "result = " << num1 - num2;
    else
        std::cout << "I don't know such operation";
}

void grain_and_chess() {
    std::vector<unsigned long long> count_gain = {1000ULL, 1000000ULL, 10000000000000000000ULL};
    std::vector<int> count_square;
    unsigned long long sum = 0;

    int j = 0;

    for (unsigned long long gain: count_gain) {
        for (unsigned long long i = 1; sum < gain; i*=2) {
            sum+=i;
            ++j;
        }

        count_square.push_back(j);
        j = 0;
        sum = 0;

    }
    for (int square: count_square) {
        std::cout << square << " ";
    }
    std::cout << "\n" << std::numeric_limits<double>::max() << "--- double\n"
            << std::numeric_limits<int>::max() << "--- int\n"
            << std::numeric_limits<unsigned long long>::max() << "=== ull\n"
            << std::numeric_limits<unsigned long>::max() << "=== ul\n";

}

void rock_paper_scissors() {
    std::string human_choice;
    int choice;

    std::vector<std::string> computer_choice = {"rock", "paper", "scissors"};
    std::vector<int> num_choices {};


    std::cout << "Enter for randomizing from 0 to 2 (type another for stop) integers for randomizing choices: ";
    while (std::cin >> choice) {
        if (choice >= 0 && choice <= 2)
            num_choices.push_back(choice);
        else
            break;
    }


    for (int choice: num_choices) {
        std::cout << "Enter \"rock, paper or scissors\": ";
        std::cin >> human_choice;

        switch (computer_choice[choice][0]) {
            case 'r':
                switch (human_choice[0]) {
                    case 'r':
                            std::cout << "draw\n";
                            break;

                    case 'p':
                            std::cout << "you win!\n";
                            break;

                    case 's':
                            std::cout << "you defeat!\n";
                            break;

                default:
                            std::cout << "unacceptable input!\n";
                            break;
                }
                break;

            case 'p':
                switch (human_choice[0]) {
                    case 'r':
                        std::cout << "you defeat!\n";
                            break;

                    case 'p':
                        std::cout << "draw\n";
                            break;

                    case 's':
                        std::cout << "you win!\n";
                            break;

                    default:
                        std::cout << "unacceptable input!\n";
                            break;
                }
                break;

            case 's':
                switch (human_choice[0]) {
                    case 'r':
                        std::cout << "you win!\n";
                            break;

                    case 'p':
                        std::cout << "you defeat!\n";
                            break;

                    case 's':
                        std::cout << "draw\n";
                            break;

                    default:
                        std::cout << "unacceptable input!\n";
                            break;
                }
                break;
            default:
                break;
        }

    } {

    }
}

void find_primes() {
    std::vector<int> primes {1,2};
    bool is_prime = true;

    for (int i = 3; i <=100; ++i) {
        is_prime = true;

        for (int j = 2; j < i; ++j) {
            if (i%j == 0) {
                is_prime = false;
                break;
            }


        }

        if (is_prime) {
            primes.push_back(i);

        }


    }

    for (int i: primes) {
        std::cout << i << " ";
    }
}

void find_primes_sieve() {

    int input;

    std::cout << "Write input value n and then program finds the first n primes:";
    std::cin >> input;

    const int count_primes = input;

    const int p = count_primes * (std::log(count_primes) + std::log(std::log(count_primes))) + 10;

    const int limit = max(100, p);

    std::vector<bool> is_primes (limit+1, true);

    is_primes[0] = is_primes[1] = false;

    for (int i = 2; i * i <= limit; ++i) {
        for (int j = i * i; j <= limit; j+=i) {
            is_primes[j] = false;
        }
    }

    int current_count_primes = 0;

    for (int i = 0; i < is_primes.size()  && current_count_primes < count_primes; i++) {
        if (is_primes[i]) {
            std::cout << i << " ";
            ++current_count_primes;
        }

    }

    std::cout << "\nCount primes = " << current_count_primes << "\n"
            << "Size of vector = " << is_primes.size();
}

int find_mode_int (std::vector<int> input) {
    int result = 0;
    int count_res = 0;

    for (int el: input) {
        int possible_result = el;
        int count = 0;

        for (int element: input) {
            if (possible_result == element)
                ++count;
        }

        if (count_res < count) {
            result = possible_result;
            count_res = count;
        }

    }


    return result;
}

std::string find_min_str (const std::vector<std::string> & input) {
    std::string result = input[0];

    for (const std::string& str: input) {

        if (result.size() > str.size())
            result = str;

    }

    return result;
}

std::string find_max_str (const std::vector<std::string> & input) {
    std::string result = input[0];

    for (const std::string& str: input) {

        if (result.size() < str.size())
            result = str;

    }

    return result;
}

std::string find_mode_str (const std::vector<std::string> & input) {
    std::string result;
    int count_res = 0;

    for (const std::string & el: input) {
        const std::string & possible_result = el;
        int count = 0;

        for (const std::string & element: input) {
            if (possible_result == element)
                ++count;
        }

        if (count_res < count) {
            result = possible_result;
            count_res = count;
        }

    }


    return result;
}

void solve_quadratic_equations() {
    double a,b,c, x1, x2, discriminant = 0;

    std::cout << "Enter a: ";
    std::cin >> a;

    std::cout << "Enter b: ";
    std::cin >> b;

    std::cout << "Enter c: ";
    std::cin >> c;

    discriminant = b*b - 4 * a * c;
    std::cout << "discriminant = " << discriminant << "\n";

    if (discriminant > 0) {
        x1 = (-b + std::sqrt(discriminant)) / (2*a);
        x2 = (-b - std::sqrt(discriminant)) / (2*a);
        std::cout << "x1 = " << x1 << "\nx2 = " << x2;
    }
    else if (discriminant == 0) {
        x1 = x2 = (-b) / (2*a);
        std::cout << "x = " << x1;
    }
    else if (discriminant < 0) {
        error("Solves not exist for this input values!");
    }
}

void names_scores_pairs() {
    std::vector<std::string> names;
    std::vector<int> scores;

    std::string input_name;
    int input_score;

    std::cout << "Enter unicum name and score: ";

    while (std::cin >> input_name && std::cin >> input_score) {
        if (input_score == 0 && input_name == "NoName") {
            break;
        }


        for (std::string & el_name: names) {
            if (input_name == el_name) {
                std::cout << "Error! Such name is exist in this vector!";
                return;
            }
        }

        names.push_back(input_name);
        scores.push_back(input_score);

        std::cout << "Enter unicum name and score: ";
    }

    std::cout << "Enter name to find score: ";
    bool is_find = false;

    while (std::cin >> input_name) {
        if (input_name == "NoName")
            break;

        for (int i = 0; i < names.size(); ++i) {
            if (names[i] == input_name) {
                std::cout << names[i] << " " << scores[i] << "\n";
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

        for (int i = 0; i < names.size(); ++i) {
            if (scores[i] == input_score) {
                std::cout << names[i] << " ";
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
int max(int a, int b) {
    int result = a;

    if (a < b)
        result = b;

    return result;
}

