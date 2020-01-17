//
// Created by piotr@janczura.pl on 2019.06.26
//

#include "PolishExpression.h"


namespace pjpl::alg {

PolishExpression::PolishExpression()
{
}

void PolishExpression::setPostfix(const pjpl::alg::PolishNotation::Postfix &postfix)
{
    this->postfix = postfix;
}

pjpl::err_t PolishExpression::calculate(pjpl::alg::ParamsMap *params, bool &result)
{
    this->params = params;
    return _logic(result);
}

err_t PolishExpression::_logic(bool &result) {

    std::wstring token;
    std::wstring leftValue = L"";
    std::wstring rightValue = L"";
    std::wstring rightString = L"";
    ws_stack valuesSet;
    ws_stack tmp;

    for (auto v_ws_it = postfix.begin(); v_ws_it != postfix.end(); v_ws_it++) {
        token = *v_ws_it;

        if (token == L"!=") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( leftValue != rightValue ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L"=") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( leftValue == rightValue ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L">=") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( leftValue >= rightValue ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L"<=") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( leftValue <= rightValue ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L">") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( leftValue > rightValue ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L"<") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( leftValue < rightValue ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L"&&" || token == L"and") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( L"0" != leftValue && rightValue != L"0") {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L"||" || token == L"or") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();

            if ( L"0" != leftValue || rightValue != L"0") {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L"=[") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();
            std::wstring valueConst = valuesSet.top();
            valuesSet.pop();
            valueConst = valueConst.substr(1, valueConst.length() - 2);
            std::vector<std::wstring> inputValuesVS = pjpl::wstr::split(leftValue, L",", true);
            std::vector<std::wstring> constValuesVS;
            std::size_t c = 0;
            std::wstring ws;
            while (!(ws = pjpl::wstr::between(valueConst, L"<\">", L"<\"/>", c, c, true)).empty()) {
                constValuesVS.push_back(ws);
            }

            bool res = false;
            for (auto &it : inputValuesVS) {
                if ( std::find(constValuesVS.begin(), constValuesVS.end(), it ) != constValuesVS.end() ) {
                    res = true;
                    break;
                }
            }
            if ( res ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token == L"![") {
            rightValue = tmp.top();
            tmp.pop();
            leftValue = tmp.top();
            tmp.pop();
            std::wstring valueConst = valuesSet.top();
            valuesSet.pop();
            valueConst = valueConst.substr(1, valueConst.length() - 2);

            std::vector<std::wstring> inputValuesVS = pjpl::wstr::split(leftValue, L",", true);
            std::vector<std::wstring> constValuesVS;
            std::size_t c = 0;
            std::wstring ws;
            while (!(ws = pjpl::wstr::between(valueConst, L"<\">", L"<\"/>", c, c, true)).empty()) {
                constValuesVS.push_back(ws);
            }

            bool res = false;
            for (auto &it : inputValuesVS) {
                if ( std::find(constValuesVS.begin(), constValuesVS.end(), it ) == constValuesVS.end() ) {
                    res = true;
                    break;
                }
            }
            if ( res ) {
                tmp.push(L"1");
            } else {
                tmp.push(L"0");
            }
        } else if (token[0] == L'[') {
            // gdy wartość parametru z wydarzenia będzie porównywana ze zbiorem wartości [....] przez operator =[ lub ![
            tmp.push(rightValue);
            valuesSet.push(token);
        } else {
            /*
             * Tu musi być liczba lub literał definiujący jakąś wartość na mapie zmiennych.
             * Jeżeli to podejście się nie powiedzie należy zwrócić błąd.
             */
            ParamsMap::iterator ws_ws_it;
            for (ws_ws_it = params->begin(); ws_ws_it != params->end(); ++ws_ws_it) {
                if (token == ws_ws_it->first) {
                    rightString = ws_ws_it->second;
                    break;
                }
            }

            if (ws_ws_it == params->end()) {
                // Pętla wyżej odnajduje definicje zmiennych na mapie zmiennych ale po dodaniu operacji porównania
                // dwóch napisów nie mających wartości liczbowych napis może nie być nazwą zmiennej a ciągiem do porównania.
                // Przesyłam go na stos z "nadzieją" że posłuży do porównania typu : "jakiś napis" operator "inny napis"
                for (ws_ws_it = params->begin(); ws_ws_it != params->end(); ++ws_ws_it) {
                    if (token == ws_ws_it->second) {
                        break;
                    }
                }
                rightString = token;
            }
            tmp.push(rightString);
            ws_stack s = tmp;
            while (!s.empty())
            {
                s.pop();
            }
        }
    }
    result = tmp.top() == L"1";
    return OK;
};



}