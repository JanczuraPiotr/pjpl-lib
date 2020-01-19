//
// Created by piotr@janczura.pl on 2018.10.05
//

#ifndef AUTOMATION_ALG_H
#define AUTOMATION_ALG_H

#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "lib/def.h"
#include "lib/napisy.h"

namespace pjpl::alg {

    /**
     * Reads: in and collect all values for every occurrence of param. Params and values placed between <"> and <"/>
     * Example, for: <">MonitorId</"> = <">1<"/> and <">MonitorId</"> = <">2<"/> or <">MonitorId</"> = <">3<"/>
     * returns vector[1,2,3]
     * @param in
     * @param param
     * @return
     */
    pjpl::StrV collectParams(const std::string &in, const std::string &param);
    /**
     * Reads: in and collect all values for every occurrence of param. Params and values placed between <"> and <"/>
     * Example, for: <">MonitorId</"> = <">1<"/> and <">MonitorId</"> = <">2<"/> or <">MonitorId</"> = <">3<"/>
     * returns vector[1,2,3]
     * @param in
     * @param param
     * @return
     */
    pjpl::WStrV collectParams(const std::wstring &in, const std::wstring &param);
    /**
     * Reads in and collect all values for params defined between ![...] or =[...]
     * Params name and values in list placed between <"> and <"/>
     * Example,
     * for: "<\">cf-none<\"/>=[<\">7<\"/>,<\">8<\"/>]"
     * returns vector[7,8]
     * for: "<\">cf-none<\"/>![<\">cf-sr<\"/> =[<\">1<\"/>,<\">2<\"/>,<\">9<\"/>]"
     * returns vector[1,2,9]
     * @param in
     * @param param
     * @return
     */
    pjpl::WStrV collectInParams(const std::wstring &in, const std::wstring &param);
    /**
     * Transform vector to string.
     * @tparam T
     * @param vector
     * @param glue
     * @return
     */
    std::wstring joinWStr(const std::vector<std::wstring> &vector, const std::wstring &glue);
    /**
     * Transform vector to string.
     * @tparam T
     * @param vector
     * @param glue
     * @return
     */
    template <class T>
    std::string join(const T &vector, const std::string &glue) {
        std::stringstream out;
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

    std::wstring joinVariable(const std::vector<std::wstring> &vector, const std::wstring &glue);


 }

#endif //AUTOMATION_ALG_H
