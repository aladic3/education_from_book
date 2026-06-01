//
// Created by Dmytrenko Kyrylo on 07.05.2026.
//



module;

#include <functional>
#include <vector>
#include <iostream>
#include <random>
#include <set>
#include <span>


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
    struct Mortal;
    struct Room;
    struct Game;
    struct Antagonist;
    struct Wumpus;
    struct Pit;
    struct Bat;

    struct Room {
        int number_this = -1;
        Room* next_1 = nullptr;
        Room* next_2 = nullptr;
        Room* next_3 = nullptr;
    };

    constexpr Room hell_room = Room{666};

    
    void init_map(std::vector<Room>&);

    struct Mortal {
        virtual void die() = 0;
        virtual const Room* get_location() = 0;
    };



    struct Pit {
        Pit (const Room& loc) : location(loc){};
        void contact_action();

        const Room& location;
    };

    struct Bat : Mortal{
        Bat (const Room& loc) : location(&loc){};


        [[nodiscard]] const Room* get_location() override { return location;}

        void die() override;

        const Room* location;
    };

    struct Wumpus : Mortal{
        Wumpus(const Room& loc) : location(&loc){}



        void contact_action() {}
        void move(); // random move on 1 step in range from 3 connected rooms


        void die() override;
        [[nodiscard]] const Room* get_location() override { return location;}

        const Room *location;

    };

    struct Antagonist : Mortal{
        Antagonist(const Room& loc) : location(&loc){}


        void die() override;
        [[nodiscard]] const Room* get_location() override { return location;}

        void shoot(std::span<int> trajectory,const std::vector<Mortal*>& mobs);
        bool move(int next_room);
        void bat_move(const Room* wumpus_room, const int depth = 1); // TODO move to nearby room with wumpus

        int arrows_capacity = 5;
        const Room* location;
    };


    struct Game {
        Game();
        void start_game();



    private:
        void init_bats(std::set<int>& sibel_values, int count = 2);
        void init_pits(std::set<int>& sibel_values, int count = 2);
        void init_wumpus(std::set<int>& sibel_values);
        void init_antagonist(std::set<int>& sibel_values);
        std::vector<Mortal*> get_alive_mobs();

        std::vector<Room> map{20};

        std::vector<Pit> pits;
        std::vector<Bat> bats;
        Wumpus* wumpus = nullptr;
        Antagonist* antagonist = nullptr;

        void shoot();
        void move_antagonist();




    };


}


export namespace ch16::drill {
    void drill1();
    void drill2();

}

export namespace ch16::try_ {
    void test();

}
