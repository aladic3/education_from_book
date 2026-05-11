//
// Created by Dmytrenko Kyrylo on 07.05.2026.
//



module;

#include <vector>
#include <iostream>


export module chapter16;


export namespace ch16::exercises {
    void to_lower(char* input_str);
    char* str_dup(const char*);

    const char *find_x(const char *str, const char *x);
    int str_cmp(const char* s1, const char* s2);




    void ex1();
    void ex2();
    void ex3();
    void ex4();
    void ex5();

}


export namespace ch16::drill {
    void drill1();
    void drill2();

}

export namespace ch16::try_ {
    void test();

}
