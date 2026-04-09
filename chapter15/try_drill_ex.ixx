//
// Created by Dmytrenko Kyrylo on 08.04.2026.
//
module;
#include "../error.h"

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
