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
        calculator.h
        calculator.cpp
        chapter10/ex.ixx
        chapter10/ex.cpp
        chapter15/try_drill_ex.ixx
        chapter15/try.cpp
        chapter15/drill.cpp
        chapter15/ex.cpp
        chapter16/ex.cpp
        chapter16/try.cpp
        chapter16/drill.cpp
        chapter16/try_drill_ex.ixx
        chapter17/try_drill_ex.ixx
        chapter17/try.cpp
        chapter17/drill.cpp
        chapter17/ex.cpp
        chapter18/try.cpp
        chapter18/drill.cpp
        chapter18/ex.cpp
        chapter18/try_drill_ex.ixx
        chapter18/vector.cpp


)


target_sources(hello_world PUBLIC
       FILE_SET cxx_modules TYPE CXX_MODULES
       FILES
        chapter9/try_drill.ixx
        chapter8/try/try8.ixx
        chapter10/ex.ixx
        chapter15/try_drill_ex.ixx
        chapter16/try_drill_ex.ixx
        chapter17/try_drill_ex.ixx
        chapter18/try_drill_ex.ixx
)

# Только для MSVC
if (MSVC)

   add_compile_options(/std:c++latest /experimental:module /scanDependencies)
endif()