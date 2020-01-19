//
// Created by piotr@janczura.pl on 2019.11.27
//

#ifndef PLAYOUT_BECKEND_STRINGS_H
#define PLAYOUT_BECKEND_STRINGS_H

#include <string>

class strings {
public:

    static std::string toString(const std::wstring &source);
    static std::wstring fromString(const std::string &str);
};


#endif //PLAYOUT_BECKEND_STRINGS_H
