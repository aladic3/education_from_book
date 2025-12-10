//
// Created by Dmytrenko Kyrylo on 02.12.2025.
//

#include "error.h"


class Bad_area {
};

void error(const std::string& msg) {
    throw std::runtime_error(msg + '\n');

}