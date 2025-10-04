#include <iostream>
//
// Created by Dmytrenko Kyrylo on 26.08.2025.
//


void sum_penni() {
    int pennies, nickels, dimes, quarters, half_dollar, one_dollar;

    std::cout << "How many pennies do you have: ";
    std::cin >> pennies;


    std::cout << "How many nickels do you have: ";
    std::cin >> nickels;

    std::cout << "How many dimes do you have: ";
    std::cin >> dimes;

    std::cout << "How many quarters do you have: ";
    std::cin >> quarters;

    std::cout << "How many half dollars do you have: ";
    std::cin >> half_dollar;

    std::cout << "How many one-dollar coins do you have: ";
    std::cin >> one_dollar;

    int sum = pennies + nickels*5 + dimes*10 + quarters*25 + half_dollar*50 + one_dollar*100;

    if (pennies > 1)
        std::cout << "You have " << pennies << " pennies.\n";
    else
        std::cout << "You have " << pennies << " pennie.\n";

    if (nickels > 1)
        std::cout << "You have " << nickels << " nickels.\n";
    else
        std::cout << "You have " << nickels << " nickel.\n";

    if (dimes > 1)
        std::cout << "You have " << dimes << " dimes.\n";
    else
        std::cout << "You have " << dimes << " dime.\n";

    if (quarters > 1)
         std::cout << "You have " << quarters << " quarters.\n";
    else
        std::cout << "You have " << quarters << " quarter.\n";

    if (half_dollar > 1)
        std::cout << "You have " << half_dollar << " half dollars.\n";
    else
        std::cout << "You have " << half_dollar << " half dollar.\n";

    std::cout << "The value of all of your coins is " << sum <<" cents.\n";
    std::cout << "The value of dollars is " << sum / 100 << "." << sum % 100 << "\n";

}