cmake_minimum_required(VERSION 3.31)
project(hello_world CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)




add_executable(hello_world main.cpp
        error.cpp

        chapter9/try_drill.ixx
        chapter9/try_s.cpp
        chapter8/try/try8.ixx
        chapter8/try/try8_drill8.cpp
        chapter8/try/ex14_.cpp
        chapter8/try/ex13.cpp
        chapter8/try/ex5_9.cpp
        chapter8/try/ex2_4.cpp
        chapter9/Roman.cpp


)


target_sources(hello_world PUBLIC
       FILE_SET cxx_modules TYPE CXX_MODULES
       FILES
        chapter9/try_drill.ixx
        chapter8/try/try8.ixx


)

# Только для MSVC
if (MSVC)

   add_compile_options(/std:c++latest /experimental:module /scanDependencies)
endif()