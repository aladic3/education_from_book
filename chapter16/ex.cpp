//
// Created by Dmytrenko Kyrylo on 07.05.2026.

module;
#include <iostream>

module chapter16;

namespace ch16::exercises {
    void to_lower(char* input_str) {
        for (char* p = input_str; *p != 0; ++p) {
            if (*p > 'A' && *p < 'Z')
                *p += 32;
        }
    }

    void print_str(const char* str) {
        for (const char* p = str; *p != 0; ++p)
            std::cout << *p;

        std::cout << std::endl;
    }

    int str_len(const char* str) {
        int result = 0;

        for (const char* p = str; *p != 0; ++p)
            ++result;

        return result;
    }

    char* str_dup(const char* str) {
        int len = str_len(str);
        char* res = new char [len];
        for (int i = 0; i < len; ++i) {
            res[i] = str[i];
        }

        return res;
    }

    const char *find_x(const char *str, const char *x) {
        const char* px = x;
        const char *result = nullptr;

        bool processing = false;
        for (const char* ps = str; *ps != 0 && *px != 0; ++ps) {
            if (processing && *ps != *px) {
                px = x;
                processing = false;
            }

            if (*ps == *px) {
                if (processing == false)
                    result = ps;
                ++px;
                processing = true;
            }
        }

        if (*px == 0)
            return result;

        return nullptr;
    }


    void ex3() {
        char s[] {"Hello, world! ellow bababa."};
        char x[] {"world!"};

        const char* found = find_x(s, "world!");
        found = find_x(s,"ellow ba");
        if (found == nullptr) {
            std::cout << "Not found";
            return;
        }


        print_str(found);
    }

    void ex1() {
        char str [] = "Hello, World! NICE TO SEE YOU!!!\n";
        print_str(str);
        to_lower(str);
        print_str(str);
    }

    void ex2() {
        char buffer [256] {"Good game... It was nice idea...Last your idea..."};
        char* copy = str_dup(buffer);

        print_str(buffer);
        print_str(copy);

        delete copy;
    }




}