//
// Created by piotr@janczura.pl on 2019.06.25
//

#include "Operators.h"

namespace pjpl::alg {

Operators::Type Operators::check(const std::wstring &token)
{
    auto it = std::find(pjpl::wstr::operators.begin(), pjpl::wstr::operators.end(), token);

    if (it != pjpl::wstr::operators.end()) {

               if (*it == L"=") {       return Enum::EQ;
        } else if (*it == L"!=") {      return Enum::NEQ;
        } else if (*it == L"and") {     return Enum::AND;
        } else if (*it == L"or") {      return Enum::OR;
        } else if (*it == L"!") {       return Enum::NOT;
        } else if (*it == L">=") {      return Enum::GTEQ;
        } else if (*it == L"<=") {      return Enum::LTEQ;
        } else if (*it == L"<") {       return Enum::LT;
        } else if (*it == L">") {       return Enum::GT;
        } else if (*it == L"=[") {      return Enum::INSET;
        } else if (*it == L"![") {      return Enum::NOTINSET;
        } else if (*it == L"AND") {     return Enum::AND;
        } else if (*it == L"OR") {      return Enum::OR;
        } else if (*it == L"NOT") {     return Enum::NOT;
        } else if (*it == L"not") {     return Enum::NOT;
        } else if (*it == L"&&") {      return Enum::AND;
        } else if (*it == L"||") {      return Enum::OR;
        } else if (*it == L"+") {       return Enum::ADD;
        } else if (*it == L"-") {       return Enum::SUB;
        } else if (*it == L"*") {       return Enum::MUL;
        } else if (*it == L"/") {       return Enum::DIV;
        } else if (*it == L"^") {       return Enum::POW;
        } else {
            return Enum::UNKNOWN;
        }

    } else {
        return Enum::UNKNOWN;
    }
}

bool Operators::order(const std::wstring &op1, const std::wstring &op2)
{
    if (check(op1) && !check(op2))
        return true;
    if (!check(op1))
        return false;
    return priority(op1) >= priority(op2) ? true : false;
}

std::size_t Operators::priority(const std::wstring &op)
{
    // operatorsPriority.seconds -- priorytet operatora
    // http://en.cppreference.com/w/cpp/language/operator_precedence
    static const std::map<std::wstring, int> operatorsPriority = {

            { L"___unary__minus___", 16 - 3},
            { L"___unary__plus___", 16 - 3},
            { L"!", 16 - 3},
            { L"*", 16 - 5},
            { L"/", 16 - 5},
            { L"+", 16 - 6},
            { L"-", 16 - 6},
            { L"^", 16 - 7}, // potęga
            { L">=", 16 - 8},
            { L">", 16 - 8},
            { L"<", 16 - 8},
            { L"<=", 16 - 8},
            { L"=", 16 - 9},
            { L"!=", 16 - 9},
            { L"&&", 16 - 13},
            { L"and", 16 - 13},
            { L"||", 16 - 14},
            { L"or", 16 - 14},
            // @todo przetestować priorytet operatorów : "=[...]", "![...]" . Nadałem je trochę z głowy.
            { L"=[", 16 - 9},
            { L"![", 16 - 9},
    };

    return operatorsPriority.at(op);
}

}

