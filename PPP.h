// Placeholder header for "Programming: Principles and Practice Using C++" utilities.
// If you plan to add helpers/types from the book, you can place them here.
#pragma once
#include "try4.cpp"
#include "drills_3.cpp"
#include "ex5.cpp"
#include "ex3.cpp"
#include "drill4.cpp"
#include "ex4.cpp"
#include "calculator.cpp"
#include "bitwise_calculator.cpp"

int error(std::string msg);

// Currently empty on purpose.

/*
/------- random numbers ------

    PPP_EXPORT std::default_random_engine& get_rand()
{
    static std::default_random_engine ran;
    return ran;
};

PPP_EXPORT void seed(int s) { get_rand().seed(s); }
PPP_EXPORT void seed() { get_rand().seed(); }

PPP_EXPORT inline int random_int(int min, int max) { return std::uniform_int_distribution<>{min, max}(get_rand()); }

PPP_EXPORT inline int random_int(int max) { return random_int(0, max); }


template<typename C>
using Value_type = typename C::value_type;

template<typename C>
using Iterator = typename C::iterator;
 */