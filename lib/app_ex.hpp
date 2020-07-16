//
// Created by piotr@janczura.pl on 2018.09.25.
//

#ifndef AUTOMATION_EXCEPTION_H
#define AUTOMATION_EXCEPTION_H

#include <string>
#include <exception>

namespace pjpl::ex {


class general : public std::exception {

public:
    general(const std::string &file, int line);
    general(const std::string &msg, const std::string &file, int line);
    ~general() override = default;

    std::string msg();
    std::string file();
    int line();

protected:
    const std::string _msg;
    const std::string _file;
    const int _line = -1;

};


}

#endif //AUTOMATION_EXCEPTION_H
