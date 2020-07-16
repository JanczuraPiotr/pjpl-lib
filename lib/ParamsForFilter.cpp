/*
 * File:   ParamsForFilter.cpp
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 13 września 2017, 16:46
 */

#include "ParamsForFilter.h"

namespace pjpl::model {

ParamsForFilter::ParamsForFilter()
{

}
//
//void ParamsForFilter::reload(
//        pjpl::model::EventToServeRecord::ptr event
//        , pjpl::model::EventMacroRecord::ptr macro)
//{
//    refresh();
//    pjpl::DateTime now;
//
//    params = event->getParams();
//    inParams = macro->getInParams();
//
////        pjpl::debug("params #############################################################\n",__FILE__,__LINE__);
////        for (auto item1 : *params) {
////            pjpl::debug(pjpl::wstr::toString(item1.first) + " = " + pjpl::wstr::toString(item1.second),__FILE__,__LINE__);
////        }
////        pjpl::debug("inParams BEGIN -------------------------------------------------------------",__FILE__,__LINE__);
////
////        for (auto item : *inParams) {
////            for(auto val : item.second) {
////                pjpl::debug(pjpl::wstr::toString(item.first) + " = " + pjpl::wstr::toString(val), __FILE__, __LINE__);
////            }
////        }
////        pjpl::debug("inParams END -------------------------------------------------------------\n",__FILE__,__LINE__);
//
//    // MacroTriggerTime - czas uruchomienia makra. Gdy Cuse == 'CRON' mamy cron uruchomiony o czasie : MacroTriggerTime
//    (*params)["MacroTriggerTime"] = pjpl::wstr::fromString(now.getStringDateTime().substr(11,5) + ":00");
//    if (event->getVariableId().length() > 0 && std::stoi(event->getVariableId()) > 0) {
//        (*params)["VariableId"]    = event->getVariableId();
//        (*params)["VariableVa"]   = event->getVariableVal();
//    } else {
//        (*params)["VariableId"]    = "";
//        (*params)["VariableVa"]   = "";
//    }
//
//    for (auto &it : *macro->getVariables()) {
//        (*params)["@" + std::to_wstring(it)] = (considoredAsOn(it) ? "1" : "0");
//    }
//
//    (*params)["Weekday"]           = loadWeekday(pjpl::wstr::toString(event->getStartDateTime()));
//
////        pjpl::debug("params BEGIN ..............................................................",__FILE__,__LINE__);
////        for (auto item1 : *params) {
////            pjpl::debug(pjpl::wstr::toString(item1.first) + " = " + pjpl::wstr::toString(item1.second),__FILE__,__LINE__);
////        }
////        pjpl::debug("params END ..............................................................\n",__FILE__,__LINE__);
////        std::cout << std::endl;
//
//    pjpl::InParamsMap functions =
//            monitorsFunction.get(
//                    macro->getNeeded("MonitorId"),
//                    event->getMonitorId());
//
//    for (auto &it : functions) {
//        (*params)[it.first] = pjpl::alg::joinWStr(it.second, ",");
//    }
//
//}
//
//ParamsMap* ParamsForFilter::getParams()
//{
//    return params;
//}
//
//pjpl::InParamsMap* ParamsForFilter::getInParams()
//{
//    return inParams;
//}
//
//std::string ParamsForFilter::getParam(const std::string &name)
//{
//    auto it = params->find(name);
//    if (it != params->end()) {
//        return it->second;
//    } else {
//        return "";
//    }
//}
//
//void ParamsForFilter::setParam(const std::string &key, const std::string &val )
//{
//    (*params)[key] = val;
//};
//
//void ParamsForFilter::variableTracking(pjpl::dev::ChangedValuesMap *changedValueMap)
//{
//    pjpl::DateTime now;
//    BitPortHistory::iterator bphIT;
//
//    for (auto &cvIT : *changedValueMap) {
//        if ( (bphIT = bitPortHistory.find(cvIT.first)) != bitPortHistory.end()) {
//            // Zmiana dotyczy zmiennej, która jest już obserwowana ponieważ "kiedyś" przyjęła wartość ON.
//            // Jest jeszcze w zestawieniu ale może już mieć wartość OFF.
//            // Jeżeli jest przesłana zmiana ustawia ją na ON to przedłużamy o DURATION_ON_FOR_FILTER czas
//            // przez który "trwa jej ON"
//            if (cvIT.second.first > 0) {
//                // Ponowna zmiana na ON - przedłużam wartość ON zmiennej
//                bphIT->second.first = now;
//                bphIT->second.second = true;
//            } else if (cvIT.second.first == 0) {
//                // nowa wartość = 0 [OFF] więc ten bit-port ustawiony na 0 ale gdy poprzednia wartość była ustawiona
//                // na 1[ON] przed upływem DURATION_ON_FOR_FILTER sek to jako obowiązującą pozostawiamy dotychczasową
//                // ale należy ustawić że ta wartość wygasa!!!
//                bphIT->second.first = now; // Ten moment uznajemy za ostatni kiedy zmienna była ON i potrwa to DURATION_ON_FOR_FILTER
//                bphIT->second.second = false;
//            }
//
//            // Jeżeli bphIT->second.first = now i bphIT->second.second = false
//            // to gdy przy kolejnym teście bphIT->second.first + DURATION_ON_FOR_FILTER < now
//            // to zmienna jest już OFF
//
//        } else {
//            // Zmiana dotyczy zmiennej oznaczonej jako ON.
//            // Pamiętamy sekundę kiedy ustawiono jej wartość na ON
//            if (cvIT.second.first > 0) {
//                bitPortHistory.insert(std::make_pair(cvIT.first, std::make_pair(now, true)));
//            }
//        }
//    }
//
//    // Usuwam oznaczenie portów na ON które ponad DURATION_ON_FOR_FILTER sekund temu oznaczone zostały jako OFF
//    for( BitPortHistory::iterator bpIT = bitPortHistory.begin(); bpIT != bitPortHistory.end(); ++bpIT) {
//        if (bpIT->second.second == false) {
//            if ( (bpIT->second.first + boost::posix_time::time_duration(0, 0, DURATION_ON_FOR_FILTER)) < now) {
//                bitPortHistory.erase(bpIT);
//            }
//        }
//    }
//}
//
//void ParamsForFilter::variableInit(pjpl::dev::Variables *variables)
//{
//    pjpl::DateTime now;
//    for (auto &it : *variables) {
//        bitPortHistory.insert(std::make_pair(it.first, std::make_pair(now, (it.second > 0 ? true : false))));
//    }
//}
//
//bool ParamsForFilter::considoredAsOn(pjpl::autom::VariableId variableId)
//{
//    if ( bitPortHistory.find(variableId) != bitPortHistory.end()) {
//        return true;
//    } else {
//        return false;
//    }
//}
//
//std::string ParamsForFilter::loadWeekday(const std::string &dateTime)
//{
//    if (pjpl::DateTime::check(dateTime)) {
//        return std::to_wstring(pjpl::DateTime(dateTime).getWeekdayNr());
//    } else {
//        return "";
//    }
//};
//
//void ParamsForFilter::loadDiskDiskBlocks()
//{
//    if (diskDiskBlocks != hdd.blocks()) {
//        diskDiskBlocks = hdd.blocks();
//        s_diskDiskBlocks = std::to_wstring(diskDiskBlocks);
//    }
//};
//
//void ParamsForFilter::refresh()
//{
//    pjpl::DateTime now;
//    if (now > lastRefresh ) {
//        hdd.refresh();
//        lastRefresh = now;
//        loadDiskDiskBlocks();
//    } else {
//    }
//}

}


