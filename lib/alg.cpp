//
// Created by piotr@janczura.pl on 2018.10.05
//

#include "alg.hpp"

namespace pjpl::alg {

std::vector<std::string> collectParams(const std::string &in, const std::string &param)
{
    std::ignore = in;
    std::ignore = param;
    std::vector<std::string> out;
//    std::string::size_type cursor = 0;
//    std::string token;
//
//    while ( (cursor = in.find(param, cursor)) != std::string::npos ) {
//        while (cursor < in.size() && in[cursor++] != '=') ;
//        token = pjpl::str::between(in, "<\">", "<\"/>",cursor,cursor,true);
//        cursor = in.find("<\">", cursor);
//        out.push_back(token);
//    }

    return out;
}

std::vector<std::string> collectInParams(const std::string &in, const std::string &param)
{
    std::ignore = in;
    std::ignore = param;
    std::vector<std::string> out;
//    std::string::size_type cursor = 0;
//    std::string::size_type endPart = 0;
//    std::string token;
//
//    while ( (cursor = in.find(param, cursor)) != std::string::npos ) {
//
//        cursor = in.find(L"[", cursor);
//        endPart = in.find(L"]", cursor);
//        while (!(token = pjpl::wstr::between(in, L"<\">", L"<\"/>", cursor, cursor, true)).empty() &&
//               cursor < endPart) {
//            cursor = in.find(L"<\">", cursor);
//            out.push_back(token);
//        }
//    }

    return out;
}

std::string joinStr(const std::vector<std::string> &vector, const std::string &glue)
{
    std::ignore = vector;
    std::ignore = glue;
    std::stringstream out;
//    bool addGlue = false;
//
//    for (auto it : vector) {
//        if (addGlue) {
//            out << glue;
//        }
//        out << it;
//        addGlue = true;
//    }
    return out.str();
}

std::string joinVariable(const std::vector<std::string> &vector, const std::string &glue)
{
    std::ignore = vector;
    std::ignore = glue;
    std::stringstream out;
//    std::stringstream outIt;
//    bool addGlue = false;
//
//    for (auto it : vector) {
//        if (addGlue) {
//            out << glue;
//        }
//        out << L"<\">" << it << L"<\"/>";
//        addGlue = true;
//    }
    return out.str();
}

}