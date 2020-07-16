//
// Created by piotr@janczura.pl on 2019.06.24
//

#include "PolishNotation.h"
#include "Operators.h"

namespace pjpl::alg {


PolishNotation::PolishNotation()
    : postfixList()
{

}

PolishNotation::~PolishNotation()
{
}

void PolishNotation::expression(pjpl::AutoId makroId, const std::string &expression)
{
    postfixList.insert(std::make_pair(makroId, buildPostfix(expression)));
}

void PolishNotation::clear()
{
    postfixList.clear();
}

PolishNotation::Postfix PolishNotation::buildPostfix(const std::string &expression)
{
    std::size_t                 cursor  = 0;
    std::string                 expr    = expression + ")";
    pjpl::alg::Operators::Type  op      = pjpl::alg::Operators::Enum::UNKNOWN;
    pjpl::alg::Operators::Type  opTmp   = pjpl::alg::Operators::Enum::UNKNOWN;
    std::stack<std::string>     stack;
    Postfix                     postfix;
    std::string                 token;


    size_t tokenizerStop = 0;
    std::string leftValue;
    stack.push("(");

    while (!stack.empty()) {
        /*
         * Przebudowa na zapis przyrostkowy (notacja polska)
         */
        while ( cursor < expr.size() && isspace(expression[cursor])) {
            ++cursor;
        }

        if (expr.find("<\">", cursor) == cursor) {
            token = pjpl::wstr::between(expr, "<\">", "<\"/>", cursor, tokenizerStop, true);
            cursor = tokenizerStop;
        } else {
            token = pjpl::wstr::token(expr, cursor, tokenizerStop);
            cursor = tokenizerStop;
        }

        while (cursor < expr.size() && isspace(expr[cursor])) {
            cursor++;
        }

        //------------------------------------------------------------------------------

        if ( (opTmp = pjpl::alg::Operators::check(token)) != pjpl::alg::Operators::Enum::UNKNOWN) {
            op = opTmp;
            while (pjpl::alg::Operators::order(stack.top(), token)) {
                postfix.push_back(stack.top());
                stack.pop();
            }
            stack.push(token);
            if (token == "![" || token == "=[") {
                // od ![ lub =[ do ] znajduje się lista wartości, liczby lub zmienne.
                token = pjpl::wstr::read(expression, cursor, cursor, "]");
                postfix.push_back("["+token+"]");
            }
        } else if (token == "(") {
            stack.push(token);
        } else if (token == ")") {
            while (stack.top() != "(") {
                postfix.push_back(stack.top());
                stack.pop(); //usuwanie operatora
            };
            stack.pop(); //usuwanie nawiasu "("
        } else {
            if (token.empty()) {
                throw pjpl::ex::Notation("token -> \"\""  , __FILE__, __LINE__);
            }

            postfix.push_back(token);

            if (op == pjpl::alg::Operators::Enum::UNKNOWN) {
                // token zawiera lewy składnik wyrażenia

                leftValue = token;
            } else {
                // token zawiera prawy składnik wyrażenia
                if (leftValue.length() > 0) {
                }
                op = pjpl::alg::Operators::Enum::UNKNOWN;
                leftValue = "";
            }
        }
    };
    return postfix;
}

PolishNotation::Postfix PolishNotation::postfix(pjpl::AutoId macroId)
{
    return postfixList[macroId];
}

}

