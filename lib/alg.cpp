//
// Created by piotr@janczura.pl on 2018.10.05
//

#include "alg.h"

namespace pjpl::alg {

    pjpl::StrV collectParams(const std::string &in, const std::string &param) {
        pjpl::StrV out;
        std::string::size_type cursor = 0;
        std::string token;

        while ( (cursor = in.find(param, cursor)) != std::string::npos ) {
            while (cursor < in.size() && in[cursor++] != '=') ;
            token = pjpl::str::between(in, "<\">", "<\"/>",cursor,cursor,true);
            cursor = in.find("<\">", cursor);
            out.push_back(token);
        }

        return out;
    }

    pjpl::WStrV collectParams(const std::wstring &in, const std::wstring &param) {
        pjpl::WStrV out;
        std::wstring::size_type cursor = 0;
        std::wstring token;

        while ( (cursor = in.find(param, cursor)) != std::string::npos ) {
            while (cursor < in.size() && in[cursor++] != '=') ;
            token = pjpl::wstr::between(in, L"<\">", L"<\"/>",cursor,cursor,true);
            cursor = in.find(L"<\">", cursor);
            out.push_back(token);
        }

        return out;
    }

    pjpl::WStrV collectInParams(const std::wstring &in, const std::wstring &param) {
        pjpl::WStrV out;
        std::wstring::size_type cursor = 0;
        std::wstring::size_type endPart = 0;
        std::wstring token;

        while ( (cursor = in.find(param, cursor)) != std::string::npos ) {
            cursor = in.find(L"[", cursor);
            endPart = in.find(L"]", cursor);
            while (!(token = pjpl::wstr::between(in, L"<\">", L"<\"/>", cursor, cursor, true)).empty() &&
                   cursor < endPart) {
                cursor = in.find(L"<\">", cursor);
                out.push_back(token);
            }

        }

        return out;
    }

    std::wstring joinWStr(const std::vector<std::wstring> &vector, const std::wstring &glue) {
        std::wstringstream out;
        bool addGlue = false;

        for (auto it : vector) {
            if (addGlue) {
                out << glue;
            }
            out << it;
            addGlue = true;
        }
        return out.str();
    }

    std::wstring joinVariable(const std::vector<std::wstring> &vector, const std::wstring &glue) {
        std::wstringstream out;
        std::stringstream outIt;
        bool addGlue = false;

        for (auto it : vector) {
            if (addGlue) {
                out << glue;
            }
            out << L"<\">" << it << L"<\"/>";
            addGlue = true;
        }
        return out.str();
    }

}