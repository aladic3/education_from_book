//
// Created by Dmytrenko Kyrylo on 03.11.2025.
//

#ifndef HELLO_WORLD_ERROR_H
#define HELLO_WORLD_ERROR_H
#include <string>
#include <utility>

class Bad_exception {
public:
    Bad_exception(std::string  message):str(std::move(message + '\n')){}

    std::string what(){ return str;}

private:
    std::string str;
};

void error(const std::string& msg);


#endif //HELLO_WORLD_ERROR_H