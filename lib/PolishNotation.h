//
// Created by piotr@janczura.pl on 2019.06.24
//

#ifndef AUTOMATION_POLISHNOTATION_H
#define AUTOMATION_POLISHNOTATION_H


#include <string>
#include <vector>
#include <map>

#include "model/def.h"

namespace pjpl {

    namespace ex {
        class Notation : public pjpl::ex::general {
        public:
            Notation(const std::string &what, const std::string &file, int line)
                    : pjpl::ex::general(what, file, line)
            {}
        };
    };

class PolishNotation {
public:

    typedef std::vector<std::wstring> Postfix;

    explicit PolishNotation();
    virtual ~PolishNotation();

    void expression(pjpl::model::AutoId makroId, const std::wstring &expression);
    Postfix postfix(pjpl::model::AutoId macroId);
    void clear();

private: // methods

    Postfix buildPostfix(const std::wstring &expression);

private: // attributes

    std::map<pjpl::model::AutoId, Postfix> postfixList;

};

}



#endif //AUTOMATION_POLISHNOTATION_H
