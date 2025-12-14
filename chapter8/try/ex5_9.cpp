//
// Created by Dmytrenko Kyrylo on 13.12.2025.
//
module;
#include <iostream>
#include <ostream>
#include "../../error.h"
#include <chrono>
module chapter8;

// isbn: n-n-n-x ; n-int, x-letter or digital


namespace ch8::ex5_9 {
    constexpr int COUNT_N = 3;
    std::vector<std::string> vec_genre_str{"first",
        "fiction", "periodical", "nonfiction", "biography", "children", "last"};

    std::ostream& operator<<(std::ostream& os, Genre g) {
        auto pointer = static_cast<int>(g);
        os << vec_genre_str[pointer];
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Book& b) {
        os << "Title: " << b.get_title() << std::endl
            << "Author: " << b.get_author() << std::endl
            << "ISBN: " << b.get_isbn() << std::endl
            << "Date: " << b.get_copyright_date() << std::endl
            << "Genre: " << b.get_genre() << std::endl;
        return os;
    }

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
    void Book::set_genre(Genre genre) {
        auto n = static_cast<int> (genre);

        auto min = static_cast<int> (Genre::first);
        auto max = static_cast<int> (Genre::last);

        if (n <= min  || n >= max )
            error("Genre must be valid");

        this->genre = genre;
    }


    void Book::test() {
        using namespace try_drill_ex;
        Book b;
        b.set_author("And");
        b.set_copyright_date(Year(1230)/Month{3}/Day{23});
        b.set_title("Line of life");
        b.set_isbn("213-23-34-0");
        b.set_isbn("2-232323-3224-a");
        b.set_genre(Genre{1});

        const std::vector<std::string> bad_variants{"213-23-34-as","213-23-34-;","213-23-34-",
        "213-23--1", "-2-3-#", "#-1-2-3", "1-2-3-#"};

        for (const auto & bad_variant : bad_variants)
        try {
            b.set_isbn(bad_variant);
        } catch (std::exception& ex) {
            std::cout << ex.what();
        }
        Book b2;
        Book b3("2-232323-3224-a", "Martin", "Noob",
            {2004/Month::aug/27}, Genre::fiction);

        // b2.set_isbn("2-232323-3224-a");

        std::cout << b
        << (b==b2) << std::endl
        << (b==b3) << std::endl
        << (b!=b2) << std::endl
        << (b!=b3) << std::endl
        << b3
        << b2;


    }

    struct Library::Transaction{
        Book book;
        int patron_card_number;
        try_drill_ex::Date date;
    };

    void Library::check_book_repetition(const std::string& isbn) const{
        for (const auto& el: books_) {
            if (el.get_isbn() == isbn)
                error("cant add book with existed isbn");
        }
    }

    void Library::check_patron_repetition(const std::string& user_name) const{
        for (const auto& el: patrons_) {
            if (el.get_user_name() == user_name)
                error("cant add patron with existed name");
        }
    }


    void Library::add_book(const std::string& isbn,const std::string& author,
              const std::string& title, const try_drill_ex::Date& copyright_date, Genre genre) {
        check_book_repetition(isbn);
        books_.emplace_back(isbn,author, title, copyright_date, genre);
    }

    void Library::delete_book_from_library(const Book& book) {
        // Erase all even numbers
        for (auto it = books_.begin(); it != books_.end();)
        {
            if (*it == book) {
                books_.erase(it);
                return;
            }

            ++it;
        }

        error("book not found. get_position_book_in_library");
    }

    void Library::check_out_book(const std::string& isbn, const std::string & user_name) {
        const auto& book = get_book_from_library(isbn);
        auto& patron = get_patron_from_library(user_name);

        if (patron.owes_fee())
            error("this user can't do transaction");

        create_and_register_transaction(book,patron);



    }

    void Library::create_and_register_patron(const std::string & user_name) {
        check_patron_repetition(user_name);
        patrons_.emplace_back(user_name,generate_library_card_number());
    }

    std::vector<std::string> Library::get_names_patrons_with_fee() const {
        std::vector<std::string> owes_fee;
        for (const auto& el: this->patrons_) {
            if (el.owes_fee())
                owes_fee.emplace_back(el.get_user_name());
        }

        return  owes_fee;
    }

    int Library::generate_library_card_number() {
        return this->next_card_number_++;
    }

    try_drill_ex::Date get_date_now() {
        const std::chrono::time_point now{std::chrono::system_clock::now()};
        const std::chrono::year_month_day ymd{std::chrono::floor<std::chrono::days>(now)};

        return try_drill_ex::Date{static_cast<int>(ymd.year()),
            try_drill_ex::Month{static_cast<unsigned>(ymd.month())},
            static_cast<unsigned>(ymd.day())};
    }

    auto Library::get_book_from_library(const std::string& isbn) const -> const Book& {
        for (const auto& book: this->books_) {
            if (book.get_isbn() == isbn)
                return book;
        }
        // error throws
        error("book not exist");

    }

    auto Library::get_patron_from_library(const std::string &user_name)  -> Patron&  {
        for (auto& patron: this->patrons_) {
            if (patron.get_user_name() == user_name)
                return patron;
        }
        // error throws
        error("patron not exist");


    }


    void Library::create_and_register_transaction(const Book& book,  Patron& patron) {
        try_drill_ex::Date date_now = get_date_now();
        // this book go out, copy to transaction, then delete
        Transaction transaction {book, patron.get_library_card_number(), date_now};

        //after complete save book and patron, delete book from library
        this->transactions_.push_back(std::move(transaction));
        // delete book from library
        delete_book_from_library(book);
        // and set fee to user
        patron.increment_fee();
    }



}