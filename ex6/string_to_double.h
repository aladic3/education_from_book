//
// Created by Dmytrenko Kyrylo on 02.12.2025.
//

#ifndef HELLO_WORLD_STRING_TO_DOUBLE_H
#define HELLO_WORLD_STRING_TO_DOUBLE_H
#include  <iostream>
#include <map>
#include "../error.h"


size_t find_dot_position(const std::string& possible_double) ;

double find_double_from_string(std::string &possible_double);

std::pair<int,std::string> get_multiply_and_strDoubleWithoutMinus(const std::string& wet_possible_double);


double transparent_from_string_to_double(const std::string& wet_possible_double) ;
#endif //HELLO_WORLD_STRING_TO_DOUBLE_H