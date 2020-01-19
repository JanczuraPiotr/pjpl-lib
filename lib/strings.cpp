//
// Created by piotr@janczura.pl on 2019.11.27
//

#include "strings.h"

std::string strings::toString(const std::wstring &source) {
    std::string s(source.begin(), source.end());
    return s;
}

std::wstring strings::fromString(const std::string &str) {
    std::wstring temp(str.length(),L' ');
    std::copy(str.begin(), str.end(), temp.begin());
    return temp;
}
