//
// Created by Dmytrenko Kyrylo on 01.12.2025.
//

module;
#include <iostream>
export module drill7;

namespace Try7::dangerously_ugly_code {
    export struct X {
        void f(int x) {
                struct Y {
                    int f(){return 1;} int m;
                };
            int m;
            m = x;
            Y m2;
            m2.f();
        }
        int m;
        void g(int m) {
            if (0<m) f(m+2) ; else {
                g(m+2.4);
            }
        }
         X r() { return X(2); }

        int m3() {
            return  1;
        }

        void main() {
            X a; a.f(2);
            a.m3();
            a.g(-1);
            a.r();
        }
    };
}

namespace Try7::converting {
    void conv1(double y) {
        int x = static_cast<int>(y); //checked conversion
        std::cout << "conv1 " << x << std::endl;
    }

    void conv2(double y) {
        int x = round(y); // 4/5 rounding
        std::cout << "conv2 " << x << std::endl;
    }

    void conv3(int x, int y) {
        double z = double(x)/y;

        std::cout << "conv3 " << z << std::endl;
    }

    export void test() {
        conv1(1001); conv1(7.7); conv1('x');
        conv2(1001); conv2(7.7); conv2('x');
        conv3(1001,1); conv3(7.7, 2); conv3('x', 3);
    }
}

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


