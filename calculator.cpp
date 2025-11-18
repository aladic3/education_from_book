//
// Created by Dmytrenko Kyrylo on 30.10.2025.
//
/*
grammars:
    statement:
        expression
        declaration
        print
        quit

    print:
        constexpr char print

    quit:
        constexpr char quit

    declaration:
        let variable = expression //initializing
        variable = expression //assert new value

    variable:
        string name


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
        variable
        + - primary
        ( expression )
        { expression )

    number:
        float
 */

#include <utility>

#include "iostream"
#include "error.h"


const std::string input_prompt = "> ";
const std::string result_prompt = "= ";
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char let = 'L';
constexpr char const_name = 'N';
const std::string declarationKey = "let";

class Token {
public:
    char kind_of_token; // can be: q, ;, (, ), {, }, +, -, /, *, 8 (number)
    double value;
    std::string name;

    Token(): kind_of_token(){} //default
    Token(char ch): kind_of_token{ch}{} //operation, quit, print
    Token(char ch, double val): kind_of_token{ch}, value{val}{}
    Token(std::string str, char ch): kind_of_token{ch}, name{std::move(str)}{}

};

class Variable {
private:
    std::string name;
    double value;

public:
    Variable(std::string n): name(std::move(n)){}
    Variable(){}


    void setValue(double val){ value = val;}
    double getValue() const {return value;}
    void setName(std::string n) { name = n;}
    std::string getName() {return name;}
};


class Token_stream {
public:
    void putback(Token t);
    Token get();
    void clean_mess();

private:
    static bool is_can_be_in_variable_name(char input);
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


bool Token_stream::is_can_be_in_variable_name(char input)
// can be char include in variable name?
{
    if (!std::isalpha(input) && !std::isdigit(input)) //if not in alphabet or not number
        return  false;

    return true;
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
        case '=':
            return Token{input};

        case '.': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            std::cin.putback(input);
            double value;
            std::cin >> value;

            return Token{number, value};
        }
        default: {
            if (!std::isalpha(input)) error("Bad input in Token_stream::get()!");

            std::string variable_name;
            variable_name += input;

            while (std::cin.get(input) && is_can_be_in_variable_name(input)) {
                variable_name += input;
            }

            std::cin.putback(input);

            if (variable_name == declarationKey)
                return Token{let};

            return Token{variable_name, const_name};
        }

    }

}

Token_stream ts; // provides get() and pullback
std::vector<Variable> var_table;


bool is_multiply_double_max_min_limit(double left, double right) {
    return std::abs(left) > std::numeric_limits<double>::max() / std::abs(right);
}

bool is_factorial_ull_limit(unsigned long long left, int right) {
    return left > std::numeric_limits<unsigned long long>::max()/right;
}

bool is_declared(const std::string& name) {
    for (Variable& element: var_table) {
        if (name == element.getName()) return true;
    }

    return false;
}

Variable get_var_from_table(const std::string& name) {
    for (Variable& var: var_table) {
        if (var.getName() == name) return var;
    }

    return Variable{};
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

        case const_name: {
            if (!is_declared(token.name)) error("name not declared");

            Variable var = get_var_from_table(token.name);
            return var.getValue();
        }

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
Variable declaration() {
    Token token = ts.get();

    switch (token.kind_of_token) {
        case const_name:{
            Variable variable{token.name};
            if (is_declared(variable.getName())) error("this name also declarative");

            token = ts.get();

            if (token.kind_of_token != '=') error("Symbol '=' expected");

            variable.setValue(expression());
            return variable;

        }
        default:
            error("name expected");

    }

}

double statement() {
    Token token = ts.get();

    switch (token.kind_of_token) {

        case let: {
            Variable variable = declaration();
            var_table.push_back(variable);
            return variable.getValue();
        }


        default:
            ts.putback(token);
            return expression();
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

            result = statement();

            std::cout << result_prompt << result << std::endl;


        } catch (std::exception & exception) {
            std::cerr << exception.what();
            ts.clean_mess();
        }
    }





