//
// Created by Dmytrenko Kyrylo on 08.04.2026.
//
module;

#include <vector>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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
        Link* move_on_this(Link* element, int n); // move backward or forward
        void add(const God&);
        void add_ordered(const God&);
        void add_ordered(Link*);
        [[nodiscard]] Link* find(const std::string&); // by name

        [[nodiscard]] const Link* find(const std::string&) const;
        [[nodiscard]] const God& get_value() const;

        Link*  operator[](int iterator) const;
        [[nodiscard]] int size() const;


    private:
        Link(God ); // create without left and right pointers
        Link(God, Link* left); // in end link
        Link(God, Link* left, Link* right);

        Link* move_right(Link* el);
        Link* move_left(Link* el);

        God properties;
        Link* left = nullptr;
        Link* right = nullptr;
    };


    struct Link_v1 {
        struct God{
            std::string name;
            std::string mythology;
            std::string vehicle;
            std::string weapon;
        };

        Link_v1& operator=(const Link_v1&) = delete;
        Link_v1(const Link_v1&) = delete;
        Link_v1() : properties("BEGIN"){}

        ~Link_v1();

        Link_v1* insert(const God&, const Link_v1* right_link); // create and insert by
        Link_v1* insert(const God&, int index); // create and insert by index
        Link_v1* erase(const std::string&); // by name

        void add(const God&);
        void add_ordered(const God&);
        void add_ordered(Link_v1*);
        [[nodiscard]] Link_v1* find(const std::string&); // by name

        [[nodiscard]] const Link_v1* find(const std::string&) const;
        [[nodiscard]] const God& get_value() const;

        Link_v1*  operator[](int iterator) const;
        [[nodiscard]] int size() const;
        [[nodiscard]] Link_v1* next() const  {return right;}

    private:
        Link_v1(God );
        Link_v1(God, Link_v1* right);

        God properties;

        Link_v1* right = nullptr;
    };


    struct Node {
        double val{0};
        Node* next = nullptr; // for both is right node
        Node* prev = nullptr; // for Forward_node is left node, for Skip_node is down node
        Node* down = nullptr;

        void erase(){ next = nullptr; prev = nullptr; down = nullptr;}
    };


    struct Skipped_link {
        Skipped_link() {
            srand (time(nullptr));
        }

        Node* add(double);
        Node* erase(double);
        Node* find(double);

    private:
        std::vector<Node*> layer;

        Node* first_addition(double);
        Node* insert_to_first_layer(double);
        Node* insert_to_specific_layer(Node*,int number_layer);
        Node* create_node_in_first_layer(double val,Node* current_node, Node* prev_node);

        bool flip_coin();
    };



    void print_all(const Link& link, std::ostream& os);
    void print_all(const Link_v1& link, std::ostream& os);

    void ex4_and_8();
    void ex5();
    void ex6_and_9();
    void ex7();
    void ex10_13();
    void ex14();
    void ex15();


}
