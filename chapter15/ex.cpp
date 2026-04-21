//
// Created by Dmytrenko Kyrylo on 13.04.2026.
//

module;

#include <iostream>
#include <utility>
#include <vector>

#include "../error.h"

module chapter15;

namespace ch15::exercises {
    constexpr  int global_var_1 = 1;
    constexpr int global_var_2 = 2;
    const long global_var_3 = 3;
    constexpr float global_var_4 = 4;

    void stack_test(int arg_1, bool arg_2) {
        double local_1 = 3;
        bool local_2 = true;
        long long int local_3 = 1;

        std::cout << "\nStack store laid in memory test...\n";
        std::cout << "arg_1(int): " << &arg_1 << " " << sizeof(arg_1) << std::endl
            << "arg_2(bool): " << &arg_2 << " " << sizeof(arg_2) << std::endl
            << "local_1(double): " << &local_1<< " "  << sizeof(local_1) << std::endl
            << "local_2(bool): " << &local_2<< " "  << sizeof(local_2) << std::endl
            << "local_3(llint): " << &local_3<< " "  << sizeof(local_3) << std::endl;
    }

    void static_test() {
        std::cout << "\nStatic store laid in memory test...\n";
        std::cout << "constexpr g1(int): " << &global_var_1 << std::endl
            << "constexpr g2(int): " << &global_var_2 << std::endl
            << "const g3(long): " << &global_var_3 << std::endl
            << "constexpr g4(float): " << &global_var_4 << std::endl;
    }

    void free_test() {
        constexpr int size = 10;
        int* p1 = new int(3);
        int* p2 = new int[size];
        double* p3 = new double[size];

        std::cout << "\nFree store laid in memory test...\n";
        std::cout << "size(int): " << &size << std::endl;
        std::cout << "p1(int*): " << p1 << std::endl;

        for (int i = 0; i < size; ++i)
            std::cout << "p2[" << i << "](int*):" << &p2[i]
                << "\tp3[" << i << "](double*):" << &p3[i] << std::endl;

        delete[] p3;
        delete[] p2;
        delete p1;
    }

    Linked_list_char::~Linked_list_char() {
        delete right;
    }

    void Linked_list_char::add(char val) {
        if (right)
            return right->add(val);

        right = new Linked_list_char(val);
    }

    char Linked_list_char::get_value() const {
        return value;
    }

    Linked_list_char * Linked_list_char::next() const {
        if (right)
            return right;

        return nullptr;
    }

    void print_all(const Link& link, std::ostream &os) {
        for (int i = 0; i < link.size(); i++) {
            const auto& properties = link[i]->get_value();
            os << properties.name << '\t' << properties.mythology << '\t'
            << properties.vehicle << '\t' << properties.weapon << '\n';
        }

    }

    Link::Link(God  val) : properties(std::move(val)){}

    Link::Link(God val, Link* left) : properties(std::move(val)), left(left) {}

    Link::Link(God val, Link *left, Link *right) : properties(std::move(val)), left(left), right(right){}

    // ReSharper disable once CppMemberFunctionMayBeStatic
    Link * Link::move_right(Link *el) {
        if (el->right == nullptr)
            return nullptr;

        el->left->right = el->right;
        el->right->left = el->left;

        Link* right_el = el->right;
        el->left = right_el;
        el->right = right_el->right;
        right_el->right = el;

        if (el->right) el->right->left = el;

        return el;
    }

    Link * Link::move_left(Link *el) {
        if (el->left == this)
            return nullptr;

        el->left->right = el->right;
        if (el->right) el->right->left = el->left;

        Link* left_el = el->left;
        el->right = left_el;
        el->left = left_el->left;
        left_el->left = el;

        el->left->right = el;

        return el;
    }

    Link::~Link() {
        if (left)
            left->right = nullptr;

        delete right;
    }

    Link * Link::insert(const God & val, Link * right_link) const {
        if (right_link == nullptr)
            return nullptr;

        Link* temp = right_link->left;
        right_link->left = new Link(val,right_link->left,right_link);
        temp->right = right_link->left;

        return right_link->left;
    }

    Link * Link::insert(const God & val, int index) {
        Link * right_link = this->operator[](index);
        return insert(val,right_link);
    }

    Link * Link::erase(const std::string & val) {
        Link* element = find(val);

        if (element == nullptr)
            return nullptr;

        if (element->right)
            element->right->left = element->left;

        if (element->left)
             element->left->right = element->right;

        element->left = nullptr;
        element->right = nullptr;

        return element;
    }

    Link * Link::move(Link *element, int n) {
        if (element == nullptr || n == 0)
            return nullptr;

        Link* res_moving = element;
        int increment_i = 1;

        if (n < 0) increment_i = -1;

        if (increment_i > 0)
            for (int i = 0; i != n && res_moving; i+=increment_i)
                res_moving = move_right(element);
        else
            for (int i = 0; i != n && res_moving; i+=increment_i)
                res_moving = move_left(element);

        return element;
    }

    void Link::add(const God & val) {
        if (right)
            // ReSharper disable once CppDFANullDereference
            return right->add(val);

        right = new Link(val,this);
    }

    void Link::add_ordered(const God & element) { // by first word only
        char first_word_new = static_cast<char>(
                std::tolower(element.name[0]));
        for (int i = 0; i < size(); i++) {
            char first_word_current = static_cast<char>(
                std::tolower(this->operator[](i)->get_value().name[0]));

            if (first_word_new <= first_word_current) {
                insert(element,i);
                return;
            }

        }
        add(element);
    }

    void Link::add_ordered(Link * node) {
        if (node)
            add_ordered(node->get_value());
        delete node;
    }

    Link * Link::find(const std::string & val) {
        Link *temp = this->right;

        for (int i = 0; i < size(); i++) {
            if (val == temp->get_value().name)
                return temp;
            temp = temp->right;
        }

        return nullptr;
    }

    const Link * Link::find(const std::string & val) const {
        Link *temp = this->right;

        for (int i = 0; i < size(); i++) {
            if (val == temp->get_value().name)
                return temp;
            temp = temp->right;
        }

        return nullptr;
    }

    const Link::God& Link::get_value() const{
        return properties;
    }

    Link* Link::operator[](int iterator) const {
        if (iterator >= size())
            error("out of range");

        Link *temp = this->right;

        for (int i = 0; i < iterator; i++)
            temp = temp->right;

        return temp;
    }

    int Link::size() const{
        const Link* temp = this;
        int count = 0;

        while (temp->right) {
            ++count;
            temp = temp->right;
        }

        return count;
    }

    std::ostream & operator<<(std::ostream &os,  Linked_list_char& list) {
        for (Linked_list_char* link = list.next(); link != nullptr; link = link->next())
            os << link->get_value();

        return os;
    }

    void ex4_and_8() {
        stack_test(1,true); // stack grow down
        free_test(); // free grow up
        static_test();
    }

    void ex5() {
        constexpr long size_p = 1000000000;
        float* p;
        long long int sum_size = 0;
        try {
            for (int i = 0;;++i) {
                p = new float[size_p];
                for (long long j = 0; j < size_p; ++j)
                    p[j] = 1;
                std::cout << i << "p: "  << &p[0] << " s(p):" << sizeof(*p) << std::endl;
                sum_size += (sizeof(*p) * size_p) / 1048576;
            }
        } catch (std::exception& ) {
            std::cerr << "sum size = " << sum_size; // Mb
        }

    }

    void ex6_and_9() {
        Linked_list_char list;
        constexpr char terminator = '!';

        std::cout << "For terminate enter \'" << terminator <<"\'. Enter smth:\n";

        for (char input = static_cast<char>(std::cin.get()); input != terminator; std::cin.get(input))
            list.add(input);

        std::cout << "\nInputted:\n";
        std::cout << list;
    }

    void ex7() {
        std::string buffer;
        constexpr char terminator = '!';
        std::cout << "For terminate enter \'" << terminator <<"\'. Enter smth:\n";

        for (char input = static_cast<char>(std::cin.get()); input != terminator; std::cin.get(input))
            buffer.push_back(input);

        std::cout << "\nInputted:\n";
        std::cout << buffer;
    }

    void ex10_13() {
        Link* aedra = new Link;
        Link* daedra = new Link;
        Link* nine = new Link;
        Link link;
        link.add({"First","Daedra"});
        link.add_ordered({"Gaaaal"});
        link.add_ordered({"Boooo"});
        link.add_ordered({"J"});
        daedra->add_ordered(link.erase("First"));
        link.add({"Second","Aedra"});
        Link* p0 = link[0];
        Link* p = link.insert({"Third","Nine"},0);
        p = link.insert({"Fourth","Nine"},p);
        p = link.find("Second");
        p = link.move(link[0],10);
        p = link.move(link[3], -10);
        p = link.erase(p->get_value().name);

        aedra->add_ordered(link.erase("Second"));
        nine->add_ordered(link.erase("Fourth"));
        nine->add_ordered(link.erase("Third"));

        link.add_ordered({"Arnold"});
        link.add_ordered({"Zelenskiy"});
        link.add_ordered({"Kyrylo"});

        std::cout << "<<<<<<<<<<link\n";
        print_all(link,std::cout);
        std::cout << "<<<<<<<<<<aedra\n";
        print_all(*aedra,std::cout);
        std::cout << "<<<<<<<<<<daedra\n";
        print_all(*daedra,std::cout);
        std::cout << "<<<<<<<<<<nine\n";
        print_all(*nine,std::cout);

        delete link[1];
        delete link[0];
        delete p;


    }
}