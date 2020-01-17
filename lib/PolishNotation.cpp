//
// Created by piotr@janczura.pl on 2019.06.24
//

#include "PolishNotation.h"
#include "Operators.h"

namespace pjpl {


PolishNotation::PolishNotation()
{

}

PolishNotation::~PolishNotation()
{
}

void PolishNotation::expression(pjpl::model::AutoId makroId, const std::wstring &expression)
{
    postfixList.insert(std::make_pair(makroId, buildPostfix(expression)));
}

void PolishNotation::clear()
{
    postfixList.clear();
}

PolishNotation::Postfix PolishNotation::buildPostfix(const std::wstring &expression)
{
    std::size_t                 cursor  = 0;
    std::wstring                expr    = expression + L")";
    pjpl::alg::Operators::Type   op      = pjpl::alg::Operators::Enum::UNKNOWN;
    pjpl::alg::Operators::Type   opTmp   = pjpl::alg::Operators::Enum::UNKNOWN;
    std::stack<std::wstring>    stack;
    Postfix                     postfix;
    std::wstring                token;


    size_t tokenizerStop = 0;
    std::wstring leftValue;
    stack.push(L"(");

    while (!stack.empty()) {
        /*
         * Przebudowa na zapis przyrostkowy (notacja polska)
         */
        while ( cursor < expr.size() && isspace(expression[cursor])) {
            ++cursor;
        }

        if (expr.find(L"<\">", cursor) == cursor) {
            token = pjpl::wstr::between(expr, L"<\">", L"<\"/>", cursor, tokenizerStop, true);
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
            if (token == L"![" || token == L"=[") {
                // od ![ lub =[ do ] znajduje się lista wartości, liczby lub zmienne.
                token = pjpl::wstr::read(expression, cursor, cursor, L"]");
                postfix.push_back(L"["+token+L"]");
            }
        } else if (token == L"(") {
            stack.push(token);
        } else if (token == L")") {
            while (stack.top() != L"(") {
                postfix.push_back(stack.top());
                stack.pop(); //usuwanie operatora
            };
            stack.pop(); //usuwanie nawiasu "("
        } else {
            if (token.empty()) {
                throw pjpl::alg::ex::Notation("token -> \"\""  , __FILE__, __LINE__);
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
                leftValue = L"";
            }
        }
    };
    return postfix;
}

PolishNotation::Postfix PolishNotation::postfix(pjpl::model::AutoId macroId)
{
    return postfixList[macroId];
}

}

