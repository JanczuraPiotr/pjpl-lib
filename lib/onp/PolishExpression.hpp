//
// Created by piotr@janczura.pl on 2019.06.26
//

#ifndef AUTOMATION_POLISHEXPRESSION_H
#define AUTOMATION_POLISHEXPRESSION_H


#include "lib/def.hpp"
#include "PolishNotation.hpp"
#include "lib/app_ex.hpp"

namespace pjpl::alg {

    namespace ex {
        class Expression : public pjpl::ex::general {
        public:
            Expression(const std::string &what, const std::string &file, int line)
                    : pjpl::ex::general(what, file, line)
            {}
        };

    }


class PolishExpression {

public:

    PolishExpression();
    virtual ~PolishExpression() = default;

//    void setPostfix(const pjpl::alg::PolishNotation::Postfix &postfix);
//    virtual err_t calculate(pjpl::ParamsMap *params, bool &result);

private: // methods

//    virtual err_t _logic(bool &result);

private: // attributes

//    pjpl::alg::PolishNotation::Postfix postfix;
//    pjpl::ParamsMap *params;

};

}


#endif