//
// Created by piotr@janczura.pl on 2018.10.05
//

#ifndef AUTOMATION_ALG_H
#define AUTOMATION_ALG_H

#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "lib/def.hpp"
#include "lib/napisy.hpp"

namespace pjpl::alg {

/**
 * Reads: in and collect all values for every occurrence of param. Params and values placed between <"> and <"/>
 * Example, for: <">MonitorId</"> = <">1<"/> and <">MonitorId</"> = <">2<"/> or <">MonitorId</"> = <">3<"/>
 * returns vector[1,2,3]
 * @param in
 * @param param
 * @return
 */
std::vector<std::string> collectParams(const std::string &in, const std::string &param);
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
std::vector<std::string> collectInParams(const std::string &in, const std::string &param);
/**
 * Transform vector to string.
 * @tparam T
 * @param vector
 * @param glue
 * @return
 */
std::string joinStr(const std::vector<std::string> &vector, const std::string &glue);
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

std::string joinVariable(const std::vector<std::string> &vector, const std::string &glue);


 }

#endif //AUTOMATION_ALG_H
