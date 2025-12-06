cmake_minimum_required(VERSION 3.31)
project(hello_world)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)




add_executable(hello_world main.cpp
        bitwise_calculator.cpp
        ex6/fibonacci.cpp
        ex6/string_to_double.cpp
        drill7/drill7.ixx
        error.cpp
        drill7/test.cpp
        drill7/x.cpp
        drill7/test_second.cpp
        drill7/foo1.ixx
        drill7/test_third.cpp
        drill7/foo.h
        drill7/foo.cpp
        calculator.h
        calculator.cpp


)


target_sources(hello_world
        PUBLIC
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES
        drill7/drill7.ixx
        drill7/foo1.ixx


)

# Только для MSVC
if (MSVC)
    add_compile_options(/std:c++latest /experimental:module /scanDependencies)
endif()