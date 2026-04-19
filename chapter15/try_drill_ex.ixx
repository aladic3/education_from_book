//
// Created by Dmytrenko Kyrylo on 08.04.2026.
//
module;

#include <vector>
#include <iostream>


export module chapter15;

export namespace ch15::try_ {
    struct Own_Exception : std::exception {
        Own_Exception(){}
        Own_Exception(const std::string& msg);
        ~Own_Exception() noexcept override;

        const char * what() const noexcept override;

    private:
        std::string* msg = nullptr;
    };

    void test_constructor_and_destructor();
    void sizeof_test();
}

export namespace ch15::drill {
    void part1();
    void part1_2();

    void part2();



    void print_array(std::ostream& os, const int* array, int size_array);
    void set_values_to_elements_array(int start, int* array, int size_array); // start with start ... start+size_array is end
    void set_values_to_elements_array_double(int start, int* array, int size_array); // 1 2 4 8 etc


    void print_vector(std::ostream& os, const std::vector<int>& vector);
    void set_values_to_elements_vector(int start, std::vector<int>& vector); // start with start ... start+size_array is end
    void set_values_to_elements_vector_double(int start, std::vector<int>& vector);
}

export namespace ch15::exercises {

    struct Linked_list_char { // char
        Linked_list_char(char val) : value(val) {}
        Linked_list_char() : value('_'){}

        Linked_list_char operator=(Linked_list_char&) = delete;
        Linked_list_char(Linked_list_char&) = delete;

        ~Linked_list_char();

        void add(char val);
        [[nodiscard]] char get_value() const;
        [[nodiscard]] Linked_list_char* next() const;
    private:
        char value;
        Linked_list_char* right = nullptr;
    };

    std::ostream& operator<<(std::ostream& os, const Linked_list_char& list);


    struct Link {
        struct God{
            std::string name;
            std::string mythology;
            std::string vehicle;
            std::string weapon;
        };

        Link& operator=(const Link&) = delete;
        Link(const Link&) = delete;
        Link() : properties("BEGIN"){}

        ~Link();

        Link* insert(const God&, Link* right_link) const; // create and insert by
        Link* insert(const God&, int index); // create and insert by index
        Link* erase(const std::string&); // by name
        Link* move(Link* element, int n); // move backward or forward
        void add(const God&);
        void add_ordered(const God&);
        [[nodiscard]] Link* find(const std::string&); // by name

        [[nodiscard]] const Link* find(const std::string&) const;
        [[nodiscard]] const God& get_value() const;

        Link*  operator[](int iterator) const;
        [[nodiscard]] int size() const;


    private:
        Link(God );
        Link(God, Link* left); // in end link
        Link(God, Link* left, Link* right);
 
        Link* move_right(Link* el);
        Link* move_left(Link* el);

        God properties;
        Link* left = nullptr;
        Link* right = nullptr;
    };

    void print_all(const Link& link, std::ostream& os);





    void ex4_and_8();
    void ex5();
    void ex6_and_9();
    void ex7();
    void ex10_12();


}
