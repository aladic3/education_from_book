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
    char* str_dup(const char*,int size);

    const char *find_x(const char *str, const char *x);
    const char *find_x(const char *str, const char *x, const std::pair<int,int>& size);
    int str_cmp(const char* s1, const char* s2);
    int str_cmp(const char *s1, const char *s2, const std::pair<int,int>& size);
    std::string cat_dot(const char* s1, const char* s2, const char* separator = ".");
    char* cat_dot_c(const char* s1, const char* s2, const char* separator = ".");
    std::string cat_dot(const std::string& s1, const std::string& s2, const std::string& separator = ".");
    bool isPalindrome(const std::string&);



    char* read_c_string_extendable(std::istream& is, char* buffer, int max);
    void copy_str_to_str(const char* from, char* to);
    char* read_c_string_throwable(std::istream& is, char* buffer, int max);
    bool isPalindrome(const char * input);

    void ex1();
    void ex2();
    void ex3();
    void ex4();
    void ex5();
    void ex7();
    void ex8_9_10();
    void ex11();
    void ex12();
    void ex13();


}

export namespace ch16::exercises::Hunt_the_wumpus {
    struct Room;
    struct Cave;
    struct Antagonist;
    struct Wumpus;
    struct Pit;
    struct Bat;

    
    void init_map(std::vector<Room>&);

    struct Room {

        int number_this = -1;
        Room* next_1 = nullptr;
        Room* next_2 = nullptr;
        Room* next_3 = nullptr;
    };

    struct Cave {
        std::vector<Room> map{20};
    };


}


export namespace ch16::drill {
    void drill1();
    void drill2();

}

export namespace ch16::try_ {
    void test();

}
