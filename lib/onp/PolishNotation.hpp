//
// Created by piotr@janczura.pl on 2019.06.24
//

#ifndef AUTOMATION_POLISHNOTATION_H
#define AUTOMATION_POLISHNOTATION_H


#include <string>
#include <vector>
#include <map>

#include "lib/def.hpp"
#include "lib/app_ex.hpp"

namespace pjpl::ex {


class Notation : public pjpl::ex::general {
public:
    Notation(const std::string &what, const std::string &file, int line)
            : pjpl::ex::general(what, file, line)
    {}
};

}

namespace pjpl::alg {

class PolishNotation {
public:

    typedef std::vector<std::string> Postfix;

    PolishNotation();

    virtual ~PolishNotation();

    void expression(AutoId makroId, const std::string &expression);

    Postfix postfix(AutoId macroId);

    void clear();

private: // methods

    Postfix buildPostfix(const std::string &expression);

private: // attributes

    std::map<AutoId, Postfix> postfixList;

};
}





#endif //AUTOMATION_POLISHNOTATION_H
