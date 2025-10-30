cmake_minimum_required(VERSION 3.31)
project(hello_world)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)




add_executable(hello_world main.cpp
        ex2.cpp
        ex3.cpp
        PPP.h
        sec_2_9.cpp
        drill_2_1.cpp
        ex_2_2.cpp
        ex_2_4.cpp
        ex_2_6.cpp
        ex_2_8.cpp
        ex_2_9.cpp
        ex_2_10.cpp
        ex_2_11.cpp
        try_3_4.cpp
        try_3_4_2_2.cpp
        drills_3.cpp
        try4.cpp
        drill4.cpp
        ex4.cpp
        calculator.cpp

)

# Только для MSVC
if (MSVC)
    add_compile_options(/std:c++latest /experimental:module /scanDependencies)
endif()