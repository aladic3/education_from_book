cmake_minimum_required(VERSION 3.31)
project(hello_world)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)




add_executable(hello_world main.cpp
        bitwise_calculator.cpp
        ex6/fibonacci.cpp
        ex6/string_to_double.cpp


)

# Только для MSVC
if (MSVC)
    add_compile_options(/std:c++latest /experimental:module /scanDependencies)
endif()