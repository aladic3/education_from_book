//
// Created by Dmytrenko Kyrylo on 19.08.2025.
//


#include <iostream>
#include <string>
void letter() {
    std::cout << "Enter the your name : ";
    std::string firstName="???";
    std::cin >> firstName;

    std::cout << "Enter the name of the person you want to write to: ";
    std::string friend_name = "??";
    std::cin >> friend_name;


    std::cout << "Dear " << friend_name << ", \n"
        << "How are you? I am fine. I miss you. \n"
        << "If you miss too, You also can send me letter,\n"
           "Im glad to see letter from you.\n";

    //std::cout << "\n\nHave you seen " << friend_name << " lately?\n";

    std::cout << "Input age of friend: ";
    int age = 0;
    std::cin >> age;

    if (age >= 110 || age <= 0) {
        std::cout << "You're kidding!";
        return;
    }

    std::cout << "I hear you just had a birthday and you are " << age << " years old.\n";

    if (age < 12)
        std::cout << "Next year you will be " << age + 1;

    if (age == 17)
        std::cout << "Next year you will be able to vote.";

    if (age > 70)
        std::cout << "Are you retired?";

    std::cout << "Yours sincerely,\n\n" << firstName;
}