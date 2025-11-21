//
// Created by Dmytrenko Kyrylo on 30.10.2025.
//
/*
grammars:
    calculation:
        statement
        print <-- after this ability to assign will be true in each time
        quit

    statement:
        expression
        declaration


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
        parentheses
        sqrt parentheses
        pow ( primary , integer )

    parentheses:
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
constexpr char quit_kind = 'q';
constexpr char print_kind = ';';
const std::string quit_key = "exit";
const std::string print_key = "print";
constexpr char number_kind = '8';
constexpr char let_kind = 'L';
constexpr char name_kind = 'N';
const std::string declarationKey = "let";
const std::string square_root_key = "sqrt";
constexpr char square_root_kind = 'R';
const std::string pow_key = "pow";
constexpr char pow_kind ='P';
constexpr char nothing_kind = '0';
constexpr char space_kind = ' ';
constexpr char new_line_kind = '\n';

double declaration();

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
    Variable(std::string n, double v): name(std::move(n)), value(v){}
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
    static Token translate_keyword_to_token(const std::string& name);
    bool is_full = false;
    Token buffer;

};

Token Token_stream::translate_keyword_to_token(const std::string& name) {
    if (name == declarationKey)
        return Token{let_kind};

    if (name == square_root_key)
        return Token{square_root_kind};

    if (name == pow_key)
        return Token{pow_kind};

    if (name == print_key)
        return Token{print_kind};

    if (name == quit_key)
        return Token{quit_kind};

    return Token{nothing_kind};
}

void Token_stream::clean_mess() {
    if (is_full && buffer.kind_of_token == print_kind) {
        is_full = false;
        return;
    }
    is_full = false;

    std::cin.clear();
    char skip = 0;
    while (skip != print_kind && skip != new_line_kind)
        std::cin.get(skip);

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

    if (! (std::cin.get(input))) error ("Bad input in Token_stream::get(). std::cin error!");

    while (input == space_kind) // omit spaces
        std::cin.get(input);

    switch (input) {
        case print_kind: case quit_kind: // for print and exit
        case '*':
        case '/':
        case '+':
        case '-':
        case '(': case ')':
        case '{': case '}':
        case '!':
        case '%':
        case '=':
        case ',':
            return Token{input};

        case new_line_kind: //possibility print after press enter
            return Token{print_kind};

        case '.': case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            std::cin.putback(input);
            double value;
            std::cin >> value;

            return Token{number_kind, value};
        }
        default: {
            std::string variable_name;
            variable_name += input;

            if (variable_name == "#")
                return translate_keyword_to_token(declarationKey);

            if (!std::isalpha(input)) error("Bad input in Token_stream::get()!");



            while (std::cin.get(input) && is_can_be_in_variable_name(input)) {
                variable_name += input;
            }

            std::cin.putback(input);


            Token result_translate = translate_keyword_to_token(variable_name);

            if (result_translate.kind_of_token != nothing_kind)
                return result_translate;

            return Token{variable_name, name_kind};
        }

    }

}





class VariableTable {
private:
    Variable null_buffer {};
    std::vector<Variable> var_table;

    Variable& get_var_from_table(const std::string &name);
    bool possibility_to_assign;


public:

    Variable& get_null_variable() ;
    VariableTable(): possibility_to_assign(true){}
    void set_unability_to_assign();
    bool is_can_declaration() const;
    void set_ability_to_assign();
    bool is_declared(const std::string& name) ;
    double get_value_variable_from_table(const std::string& name);
    double add_variable_to_table(const std::string& name, double value) ;
    double change_variable_in_table(const std::string& name, double value) ;
    Variable& try_declaration_without_declKey(Token& token, Token_stream& ts);


};

Variable& VariableTable::get_null_variable() {
    return null_buffer;
}


Variable& VariableTable::try_declaration_without_declKey(Token &token, Token_stream& ts) {
    Variable& result = this->null_buffer; // declaration not success, we return null object


        char input = ts.get().kind_of_token;


        set_unability_to_assign();


        if ( input == '=') {
            std::cin.putback(input);
            ts.putback(token);

            declaration();

            result = get_var_from_table(token.name);

        } else
            std::cin.putback(input);



    return result;
}


void VariableTable::set_unability_to_assign() {
    possibility_to_assign = false;
}


bool VariableTable::is_can_declaration() const
// this function assign possibility_to_assign to false value
// because assigning value ability must be one time in first part of expression,
// not anymore
{
    return possibility_to_assign;
}

void VariableTable::set_ability_to_assign() {
    possibility_to_assign = true;
}



double VariableTable::get_value_variable_from_table(const std::string &name) {
    const Variable& var = get_var_from_table(name);
    return var.getValue();
}


bool VariableTable::is_declared(const std::string& name) {
    for (Variable& element: var_table) {
        if (name == element.getName()) return true;
    }

    return false;
}

Variable& VariableTable::get_var_from_table(const std::string &name) {
    for (Variable& var: var_table) {
        if (var.getName() == name) return var;
    }

    error("Not existing var with name: " + name);
    return null_buffer;


}

double VariableTable::add_variable_to_table(const std::string& name, double value) {
    if (is_declared(name))
        error("Variable is also declared! You can create with another name!");

    var_table.emplace_back(name,value);
    return value;
}

double VariableTable::change_variable_in_table(const std::string& name, double value) {
    get_var_from_table(name).setValue(value);
    return value;

}

bool is_multiply_double_max_min_limit(double left, double right) {
    return std::abs(left) > std::numeric_limits<double>::max() / std::abs(right);
}

bool is_factorial_ull_limit(unsigned long long left, int right) {
    return left > std::numeric_limits<unsigned long long>::max()/right;
}




Token_stream ts; // provides get() and pullback
VariableTable variable_table;

double expression();
double declaration();


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

double parentheses(Token& token) {
    switch (token.kind_of_token) {
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
            error("Must be ( expression ) or { expression }");
    }
}

double pow_statement() {
    // pow (x,i) mean "multiply x with itself i times. i - integer"
    Token token = ts.get();
    switch (token.kind_of_token) {
        case '(': {
            double x = expression();

            token = ts.get();

            if (token.kind_of_token != ',') error("comma (',') expected");

            token = ts.get();

            if (token.kind_of_token != number_kind) error ("number expected");

            int power = static_cast<int>(token.value);

            token = ts.get();

            if (token.kind_of_token != ')') error("Must be ( expression )!");

            return std::pow(x,power);

            break;


        }

        default:
            error("Must be ( expression ) ");
    }
}

double primary() {
    Token token = ts.get();
    double result = 0;

    // assigning can be only if first name_kind and after this name must be '=', another we can't do this
    if (token.kind_of_token != name_kind && variable_table.is_can_declaration())
        variable_table.set_unability_to_assign();

    switch (token.kind_of_token) {
        case '-':
            result= -primary();
            break;
        case '+':
            result= primary();
            break;
        case number_kind:
            result= token.value;
            break;

        case name_kind: {

            if (variable_table.is_can_declaration() ) {
                Variable& result_assigning = variable_table.try_declaration_without_declKey(token,ts);

                if (&result_assigning != &variable_table.get_null_variable()) { // if assigning success
                    return result_assigning.getValue();
                }
            }

            result = variable_table.get_value_variable_from_table(token.name);
            break;
        }

        case '(': case '{':
            result= parentheses(token);
            break;

        case square_root_kind: {
            token = ts.get(); // need for parentheses function. after sqrt_kind token must be ( expr ).
            double res_parentheses =  parentheses(token);

            if (res_parentheses < 0)
                error("Negative can't be in square root operation");

            result= std::sqrt(res_parentheses);
            break;

        }

        case pow_kind:
            result= pow_statement();
            break;



        default:
            ts.putback(token);
            error("primary expected");
            break;
    }


    return result;

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

            case '=':
                error("Can't assign here!");
                break;

            default:
                ts.putback(token);

                return left;
        }
        token = ts.get();
    }


}

double declaration() {
    Token token = ts.get();

    switch (token.kind_of_token) {
        case name_kind:{
            const std::string name = token.name;

            token = ts.get();

            if (token.kind_of_token != '=') error("Symbol '=' expected");

            double value = expression();

            if (variable_table.is_declared(name))
                variable_table.change_variable_in_table(name,value);
            else
                variable_table.add_variable_to_table(name,value);

            return value;

        }
        default:
            error("name expected");

    }

}

double statement() {
    Token token = ts.get();

    switch (token.kind_of_token) {

        case let_kind: {
            return declaration();
        }


        default:
            ts.putback(token);
            return expression();
    }
}

void calculation() {
        variable_table.add_variable_to_table("pi",3.1415926535);
        variable_table.add_variable_to_table("e",2.7182818284);
        Token token{};

        double result = 0;
        std::cout << "Welcome to out simple calculator.\n"
                    "Please enter expressions using floating-point numbers.\n"
                "Available operators: =, x, *, /, +, -, (, ), {, }, !." << std::endl;




        while (std::cin)
            try {

            std::cout << input_prompt;

            token = ts.get();
            variable_table.set_ability_to_assign();

            while (token.kind_of_token == print_kind)
                token = ts.get();

            if (token.kind_of_token == quit_kind)
                return;

            ts.putback(token);

            result = statement();

            std::cout << result_prompt << result << std::endl;


        } catch (std::exception & exception) {
            std::cerr << exception.what();
            ts.clean_mess();
        }
    }





