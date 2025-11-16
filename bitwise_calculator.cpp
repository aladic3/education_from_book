//
// Created by Dmytrenko Kyrylo on 05.11.2025.
//
//
// Created by Dmytrenko Kyrylo on 30.10.2025.
//
#pragma once
#include "iostream"
#include "error.h"

class Bitwise_token {
public:
    char kind_of_token; // can be: q, ;, (, ), {, }, +, -, /, *, 8 (number)
    int value;

};

class Token_stream_bitwise {
public:
    void putback(Bitwise_token t);
    Bitwise_token get();

private:
    bool is_full = false;
    Bitwise_token buffer{};

};

void Token_stream_bitwise::putback(Bitwise_token t) {
    if (is_full) error("Buffer is full!");

    buffer = t;
    is_full = true;
}

Bitwise_token Token_stream_bitwise::get() {
    if (is_full) {
        is_full = false;
        return buffer;
    }

    char input = 0;

    if (! (std::cin >> input)) error ("Bad input in Token_stream::get(). std::cin error!");

    switch (input) {
        case '=': case 'x': // for print and exit
        case '&': case '|':  case '^': case '(': case ')': case '{': case '}': // bitwise expressions
            case '!': case '~': // unary operators
            return Bitwise_token{input};

        case '0': case '1': case '2': case '3': case '4': //read int
        case '5': case '6': case '7': case '8': case '9': {
            std::cin.putback(input);
            int value;
            std::cin >> value;

            return Bitwise_token{'8', value};
        }
            default:
            error("Bad input in Token_stream::get()!");
    }

    return Bitwise_token{};
}

Token_stream_bitwise bitwise_ts; // provides get() and pullback

int bitwise_expression(); // declaration so that primary() can call expression()



int bitwise_primary() {  // deal with numbers and parentheses
    Bitwise_token token  = bitwise_ts.get();

    switch (token.kind_of_token) {
        case '(': {
            int input = bitwise_expression();

            token = bitwise_ts.get();
            if (token.kind_of_token != ')') error("Must be ( expression )!");

            return input;

        }
        case '{': {
            int input = bitwise_expression();

            token = bitwise_ts.get();
            if (token.kind_of_token != '}') error("Must be { expression }!");

            return input;
        }

        case '~':
            return ~bitwise_primary();

        case '!': {
            int result = !bitwise_primary();
            return result;
        }



        case '8':
            return token.value;

        default:
            error("Primary expected!");

    }

    return -1;
}

int bitwise_secondary() {
    int left = bitwise_primary();
    Bitwise_token token = bitwise_ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '&': {
                int result = bitwise_primary();
                left&=result;
                break;
            }

            default:
                bitwise_ts.putback(token);
                return left;

        }
        token = bitwise_ts.get();
    }
}

int bitwise_term() {
    int left = bitwise_secondary();
    Bitwise_token token = bitwise_ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '^': {
                int input = bitwise_secondary();
                left^=input;
                break;
            }

            default:
                bitwise_ts.putback(token);
                return left;

        }
        token = bitwise_ts.get();
    }

}

int bitwise_expression() { // deal with + and -
    int left = bitwise_term();
    Bitwise_token token = bitwise_ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '|':
                left|=bitwise_term();
                break;

            default:
                bitwise_ts.putback(token);
                return left;
        }
        token = bitwise_ts.get();
    }


}





