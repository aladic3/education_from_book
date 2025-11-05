//
// Created by Dmytrenko Kyrylo on 30.10.2025.
//
#include "iostream"
#include "error.h"

class Token {
public:
    char kind_of_token; // can be: q, ;, (, ), {, }, +, -, /, *, 8 (number)
    double value;

};

class Token_stream {
public:
    void putback(Token t);
    Token get();

private:
    bool is_full = false;
    Token buffer;

};

void Token_stream::putback(Token t) {
    if (is_full) error("Buffer is full!");

    buffer = t;
    is_full = true;
}

Token Token_stream::get() {
    if (is_full) {
        is_full = false;
        return buffer;
    }

    char input = 0;

    if (! (std::cin >> input)) error ("Bad input in Token_stream::get(). std::cin error!");

    switch (input) {
        case '=': case 'x': // for print and exit
        case '*': case '/': case '+': case '-': case '(': case ')': case '{': case '}': case '!':
            return Token{input};

        case '.': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            std::cin.putback(input);
            double value;
            std::cin >> value;

            return Token{'8', value};
        }
            default:
            error("Bad input in Token_stream::get()!");
    }

}

Token_stream ts; // provides get() and pullback

double expression(); // declaration so that primary() can call expression()

int factorial(const int value) {
    int result = 1;

    if (value < 0) error("Minus factorial not exist!");
    if (value <= 1) return result;

    for (int i = 2; i <= value; ++i ) {
        result *= i;
    }

    return result;
}

double primary() {  // deal with numbers and parentheses
    Token token  = ts.get();

    switch (token.kind_of_token) {
        case '(': {
            double input = expression();

            token = ts.get();
            if (token.kind_of_token != ')') error("Must be ( expression )!");

            return input;

        }
        case '{': {
            double input = expression();

            token = ts.get();
            if (token.kind_of_token != '}') error("Must be { expression }!");

            return input;
        }


        case '8': {
            double result = token.value;

            token = ts.get();

            if (token.kind_of_token == '!')
                result = factorial(static_cast<int>(result));
            else
                ts.putback(token);


            return result;
        }



        default:
            error("Primary expected!");

    }
}

double term() { // deal with * and /
    double left = primary();
    Token token = ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '/': {
                double input = primary();

                if (input == 0) error("Divide by zero!");

                left/=input;
                break;
            }


            case '*':
                left*=primary();
                break;

            default:
                ts.putback(token);
                return left;

        }
        token = ts.get();
    }

}

double expression() { // deal with + and -
    double left = term();
    Token token = ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '+':
                left+=term();
                break;

            case '-':
                left-=term();
                break;

            default:
                ts.putback(token);
                return left;
        }
        token = ts.get();
    }


}





