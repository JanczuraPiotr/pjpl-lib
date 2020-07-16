//
// Created by piotr@janczura.pl on 2019.06.25
//

#ifndef AUTOMATION_OPERATORS_H
#define AUTOMATION_OPERATORS_H

#include <string>
#include <algorithm>
#include <map>

#include "lib/napisy.h"

namespace pjpl::alg {

class Operators {

public:
    typedef enum Enum {
        UNKNOWN,
        NOT, AND, OR,
        EQ, NEQ, GTEQ, LTEQ,
        GT, LT,
        INSET, NOTINSET,
        ADD, SUB, DIV, MUL, POW
    } Type;

    /**
     * Sprawdza czy token reprezentuje znany operator.
     * @param token
     * @return operator
     */
    static Type check(const std::string &token);
    /*
     * Metoda dokonuje testu pierwszeństwa wykonania dwóch operacji. Jeżeli ich kolejność
     * odpowiada przyjętym regułom w matematyce zwraca true jeżeli nie zwraca false.
     */
    static bool order(const std::string &op1, const std::string &op2);
    /*
     * Zwraca wartość liczbową priorytetu operatora
     */
    static size_t priority(const std::string &op);

};

}



#endif //AUTOMATION_OPERATORS_H
