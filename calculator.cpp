//
// Created by Dmytrenko Kyrylo on 30.10.2025.
//
/*
grammars:
    expression:
        term
        expression + - term

    term:
        postfix
        term / * % postfix

    postfix:
        primary
        postfix !


    primary:
        number
        + - primary
        ( expression )
        { expression )

    number:
        float
 */

#include "iostream"
#include "error.h"

class Token {
public:
    char kind_of_token; // can be: q, ;, (, ), {, }, +, -, /, *, 8 (number)
    double value;

};


const std::string input_prompt = "> ";
const std::string result_prompt = "= ";
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';

class Token_stream {
public:
    void putback(Token t);
    Token get();
    void clean_mess();

private:
    bool is_full = false;
    Token buffer;

};

void Token_stream::clean_mess() {
    if (is_full && buffer.kind_of_token == print) {
        is_full = false;
        return;
    }
    is_full = false;

    std::cin.clear();
    for (char skip = 0; skip != print; std::cin >> skip);
}





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
        case print: case quit: // for print and exit
        case '*':
        case '/':
        case '+':
        case '-':
        case '(': case ')':
        case '{': case '}':
        case '!':
        case '%':
            return Token{input};

        case '.': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            std::cin.putback(input);
            double value;
            std::cin >> value;

            return Token{number, value};
        }
            default:
            error("Bad input in Token_stream::get()!");
    }

}

Token_stream ts; // provides get() and pullback



bool is_multiply_double_max_min_limit(double left, double right) {
    return std::abs(left) > std::numeric_limits<double>::max() / std::abs(right);
}

bool is_factorial_ull_limit(unsigned long long left, int right) {
    return left > std::numeric_limits<unsigned long long>::max()/right;
}


double expression();


unsigned long long factorial(const int value) {
        int result = 1;

        if (value < 0) error("Minus factorial not exist!");
        if (value <= 1) return result;

        for (int i = 2; i <= value; ++i ) {
            if (is_factorial_ull_limit(result,i))
                error("Overflow factorial result");

            result *= i;
        }

        return result;
}



double primary() {
    Token token = ts.get();

    switch (token.kind_of_token) {
        case '-':
            return -primary();
        case '+':
            return primary();
        case number:
            return token.value;

        case '(': {
            double result = expression();

            token = ts.get();
            if (token.kind_of_token != ')') error("Must be ( expression )!");

            return result;
            break;


        }
        case '{': {
            double result = expression();


            token = ts.get();
            if (token.kind_of_token != '}') error("Must be { expression }!");

            return result;
            break;

        }


            default:
            ts.putback(token);
            error("primary expected");
    }
}

double postfix() {
    double result = primary();
    Token token = ts.get();

    for (;token.kind_of_token == '!';token = ts.get()) {
        result = factorial(static_cast<int>(result));
    }

    ts.putback(token);
    return result;
}



double term() { // deal with * and /
    double left = postfix();
    Token token = ts.get();

    while (true) {
        switch (token.kind_of_token) {
            case '%': {
                double right = postfix();

                if (right == 0) error("Divide (%) by zero!");

                left=std::fmod(left,right);
                break;

            }
            case '/': {
                double right = postfix();

                if (right == 0) error("Divide by zero!");

                left/=right;
                break;
            }


            case '*': {
                double right = postfix();

                if (is_multiply_double_max_min_limit(left,right))
                  error("Multiplication limit fault.");

                left*=right;
                break;
            }

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

void calculation() {
        Token token{};

        double result = 0;
        std::cout << "Welcome to out simple calculator.\n"
                    "Please enter expressions using floating-point numbers.\n"
                "Available operators: =, x, *, /, +, -, (, ), {, }, !." << std::endl;




        while (std::cin)
            try {

            std::cout << input_prompt;

            token = ts.get();

            while (token.kind_of_token == print)
                token = ts.get();

            if (token.kind_of_token == quit)
                return;

            ts.putback(token);

            result = expression();

            std::cout << result_prompt << result << std::endl;


        } catch (std::exception & exception) {
            std::cerr << exception.what();
            ts.clean_mess();
        }
    }





