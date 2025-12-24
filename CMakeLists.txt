cmake_minimum_required(VERSION 3.31)
project(hello_world CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)




add_executable(hello_world main.cpp
        #bitwise_calculator.cpp
        #ex6/fibonacci.cpp
        #ex6/string_to_double.cpp
        #drill7/drill7.ixx

        #drill7/test.cpp
        #drill7/x.cpp
        #drill7/test_second.cpp
        #drill7/foo1.ixx
        #drill7/test_third.cpp
        #drill7/foo.h
        #drill7/foo.cpp
        #calculator.h
        #calculator.cpp
        #ex7/exercises7.ixx
        #ex7/ex2.cpp
        #ex7/ex3.cpp
        #ex7/ex5_6.cpp
        #ex7/ex7_8.cpp
        #ex7/ex9.cpp
        #ex7/ex10_11.cpp
        #ex7/ex12.cpp
        #ex7/ex13.cpp
        error.cpp
        chapter8/try/try8.ixx
        chapter8/try/try8_drill8.cpp
        chapter8/try/ex2_4.cpp
        chapter8/try/ex5_9.cpp
        chapter8/try/ex13.cpp
        chapter8/try/ex14_.cpp
        chapter9/try_drill.ixx
        chapter9/try_s.cpp


)


target_sources(hello_world
        PUBLIC
       FILE_SET cxx_modules TYPE CXX_MODULES
       FILES
        #drill7/drill7.ixx
        #drill7/foo1.ixx
        #ex7/exercises7.ixx
        chapter8/try/try8.ixx
        chapter9/try_drill.ixx


)

# Только для MSVC
if (MSVC)

   add_compile_options(/std:c++latest /experimental:module /scanDependencies)
endif()