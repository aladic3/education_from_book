//
// Created by Dmytrenko Kyrylo on 01.12.2025.
//

module;
#include <iostream>

export module drill7;

namespace Drill7 {


    void print_var(const int & var) {
        std::cout << "var = " << var << '\n';
    }

    void swap_r(int& a,int& b) {
        int temp = b;
        b = a;
        a = temp;
        std::cout << "swap_r a = " << a << " b = " << b <<'\n';
    }
    void swap_cr(const int& a , const int &b) {
        int temp = b;
        std::cout << "swap_cr a = " << a << " b = " << b << '\n';
    }
    void swap_v(int a, int b) {
        int temp = a;
        a = b;
        b = temp;
        std::cout << "swap_v a = " << a << " b = " << b << '\n';
    }

    export void test_drill() {
        int x = 7;
        int y = 9;

        swap_r(x,y);
        swap_v(x,y);
        swap_cr(x,y);

        swap_v(7,9);
        swap_cr(7,9);

        const int cx = 7;
        const int cy = 9;

        swap_v(cx,cy);
        //swap_r(cx,cy);
        swap_cr(cx,cy);

        swap_cr (7.7,9.9);
        swap_v(7.7,9.9);

        double dx = 7.7;
        double dy = 9.9;
        swap_cr(dx,dy);
        //swap_r(dx,dy);
        swap_v(dx,dy);

    }

    namespace X {
        export int var;
        export void print();
    }

    namespace Y {
        export int var;
        export void print() {
            print_var(var);
        }
    }

    namespace Z {
        export int var;
        export void print() {
            print_var(var);
        }
    }
}
