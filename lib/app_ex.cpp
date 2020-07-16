//
// Created by piotr@janczura.pl on 2018.09.25.
//

#include "app_ex.hpp"

namespace pjpl::ex {

general::general(const std::string &file, int line)
        : exception()
        , _msg("pjpl::ex::genera")
        , _file(file)
        , _line(line)
{
}

general::general(const std::string &msg, const std::string &file, int line)
        : exception()
        , _msg(msg)
        , _file(file)
        , _line(line)
{
}

std::string general::msg()
{
    if (_line > 0) {
        return _msg + "  " + _file + ":" + std::to_string(_line);
    } else {
        return _msg;
    }
}

std::string general::file()
{
    return _file;
}

int general::line()
{
        return _line;
}

}