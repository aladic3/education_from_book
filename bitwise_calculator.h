//
// Created by Dmytrenko Kyrylo on 02.12.2025.
//

#ifndef HELLO_WORLD_BITWISE_CALCULATOR_H
#define HELLO_WORLD_BITWISE_CALCULATOR_H
#include <iostream>

#include "error.h"


class Bitwise_token {
public:
    char kind_of_token; // can be: q, ;, (, ), {, }, +, -, /, *, 8 (number)
    int value;

};

class Token_stream_bitwise {
public:
    void putback(Bitwise_token t);
    Bitwise_token get();

private:
    bool is_full = false;
    Bitwise_token buffer{};

};









#endif //HELLO_WORLD_BITWISE_CALCULATOR_H