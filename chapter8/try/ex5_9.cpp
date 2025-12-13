//
// Created by Dmytrenko Kyrylo on 13.12.2025.
//
module;
#include <iostream>
#include <ostream>
#include "../../error.h"
module chapter8;

// isbn: n-n-n-x ; n-int, x-letter or digital


namespace ch8::ex5_9 {
    constexpr int COUNT_N = 3;

    //return position of last separator
    [[nodiscard]]int validate_first_part_isbn(const std::string& isbn) {

        int iterator_before_separator = 0;
        int variable_of_isbn = 0;
        int count_variables = 0;
        int last_separator = 0;

        for (int i = 0; i < isbn.size() && count_variables < COUNT_N; ++i) {
            auto ch = isbn[i];

            if (ch == '-' && iterator_before_separator > 0) {
                iterator_before_separator = 0;
                variable_of_isbn = 0;
                ++count_variables;
                last_separator = i;
                continue;
            }

            if (!std::isdigit(ch))
                error("Must be number.");

            variable_of_isbn+= ch-'0' * std::pow(10,iterator_before_separator);
            iterator_before_separator++;

        }

        return last_separator;


    }

    void validate_second_part_isbn(const std::string &isbn, int last_separator_position) {
        auto start_position = 1+last_separator_position;

        if (isbn.size() - start_position != 1  )
            error("last can be one symbol, no more or less");

        for (int i = start_position; i < isbn.size(); ++i) {
            auto ch = isbn[i];
            if (std::isalpha(ch) || std::isdigit(ch))
                return;
            error("must be letter or digit");
        }

    }

    void Book::set_isbn(const std::string &isbn){
        //if validate not successfully just threw exception
        int last_separator_position = validate_first_part_isbn(isbn);
        validate_second_part_isbn(isbn,last_separator_position);

        this->isbn = isbn;

    }

    void Book::test() {
        using namespace try_drill_ex;
        Book b;
        b.set_author("And");
        b.set_copyright_date(Year(1230)/Month{3}/Day{23});
        b.set_title("Line of life");
        b.set_isbn("213-23-34-0");
        b.set_isbn("2-232323-3224-a");

        const std::vector<std::string> bad_variants{"213-23-34-as","213-23-34-;","213-23-34-",
        "213-23--1", "-2-3-#", "#-1-2-3", "1-2-3-#"};

        for (const auto & bad_variant : bad_variants)
        try {
            b.set_isbn(bad_variant);
        } catch (std::exception& ex) {
            std::cout << ex.what();
        }
        Book b2; Book b3;
        b3.set_isbn("2-232323-3224-b");
        b2.set_isbn("2-232323-3224-a");

        std::cout << b
        << (b==b2) << std::endl
        << (b==b3) << std::endl
        << (b!=b2) << std::endl
        << (b!=b3);


    }

}