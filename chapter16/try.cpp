//
// Created by Dmytrenko Kyrylo on 07.05.2026.
//
module;

#include <iostream>
#include <utility>
#include <vector>

#include "../error.h"

module chapter16;

namespace ch16::try_ {
   void test() {
         const char* ch = nullptr;
         size_t g = std::strlen(ch);
   }

}