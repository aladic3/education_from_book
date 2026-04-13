//
// Created by Dmytrenko Kyrylo on 13.04.2026.
//

module;

#include <iostream>
#include <vector>

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

    void ex4() {
        stack_test(1,true);
        free_test();
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

    void ex6() {

    }
}