//
// Created by piotr@janczura.pl on 2019.06.25
//

#include "Operators.hpp"

namespace pjpl::alg {

Operators::Type Operators::check(const std::string &token)
{
    auto it = std::find(pjpl::wstr::operators.begin(), pjpl::wstr::operators.end(), token);

    if (it != pjpl::wstr::operators.end()) {

               if (*it == "=") {       return Enum::EQ;
        } else if (*it == "!=") {      return Enum::NEQ;
        } else if (*it == "and") {     return Enum::AND;
        } else if (*it == "or") {      return Enum::OR;
        } else if (*it == "!") {       return Enum::NOT;
        } else if (*it == ">=") {      return Enum::GTEQ;
        } else if (*it == "<=") {      return Enum::LTEQ;
        } else if (*it == "<") {       return Enum::LT;
        } else if (*it == ">") {       return Enum::GT;
        } else if (*it == "=[") {      return Enum::INSET;
        } else if (*it == "![") {      return Enum::NOTINSET;
        } else if (*it == "AND") {     return Enum::AND;
        } else if (*it == "OR") {      return Enum::OR;
        } else if (*it == "NOT") {     return Enum::NOT;
        } else if (*it == "not") {     return Enum::NOT;
        } else if (*it == "&&") {      return Enum::AND;
        } else if (*it == "||") {      return Enum::OR;
        } else if (*it == "+") {       return Enum::ADD;
        } else if (*it == "-") {       return Enum::SUB;
        } else if (*it == "*") {       return Enum::MUL;
        } else if (*it == "/") {       return Enum::DIV;
        } else if (*it == "^") {       return Enum::POW;
        } else {
            return Enum::UNKNOWN;
        }

    } else {
        return Enum::UNKNOWN;
    }
}

bool Operators::order(const std::string &op1, const std::string &op2)
{
    if (check(op1) && !check(op2))
        return true;
    if (!check(op1))
        return false;
    return priority(op1) >= priority(op2) ? true : false;
}

std::size_t Operators::priority(const std::string &op)
{
    // operatorsPriority.seconds -- priorytet operatora
    // http://en.cppreference.com/w/cpp/language/operator_precedence
    static const std::map<std::string, int> operatorsPriority = {

            { "___unary__minus___", 16 - 3},
            { "___unary__plus___", 16 - 3},
            { "!", 16 - 3},
            { "*", 16 - 5},
            { "/", 16 - 5},
            { "+", 16 - 6},
            { "-", 16 - 6},
            { "^", 16 - 7}, // potęga
            { ">=", 16 - 8},
            { ">", 16 - 8},
            { "<", 16 - 8},
            { "<=", 16 - 8},
            { "=", 16 - 9},
            { "!=", 16 - 9},
            { "&&", 16 - 13},
            { "and", 16 - 13},
            { "||", 16 - 14},
            { "or", 16 - 14},
            // @todo przetestować priorytet operatorów : "=[...]", "![...]" . Nadałem je trochę z głowy.
            { "=[", 16 - 9},
            { "![", 16 - 9},
    };

    return operatorsPriority.at(op);
}

}

