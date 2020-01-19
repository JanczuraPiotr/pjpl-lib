/*
 * File:   alg.cpp
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 5 października 2018, 15:30
 */

#include "alg.h"

#include <string>
#include <vector>

#include "../../alg/alg.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Alg);

Alg::Alg()
{
}

Alg::~Alg() 
{
}

void Alg::setUp() 
{
}

void Alg::tearDown() {
}

void Alg::join() {

    {
        std::vector<int> elements = {1,2,3,4};
        std::string glue = ",";
        std::string res = pjpl::alg::join(elements, glue);

        CPPUNIT_ASSERT_MESSAGE("is = " + res , res == "1,2,3,4");
    }
    {
        std::vector<double> elements = {1.1,2.2,3.3,99.999};
        std::string glue = ",";
        std::string res = pjpl::alg::join(elements, glue);

        CPPUNIT_ASSERT_MESSAGE("is = " + res, res == "1.1,2.2,3.3,99.999");
    }
    {
        std::vector<std::string> elements = {"1", "2", "3", "4"};
        std::string glue = ",";
        std::string res = pjpl::alg::join(elements, glue);

        CPPUNIT_ASSERT_MESSAGE("is = " + res, res == "1,2,3,4");
    }
}

void Alg::joinVariable() {

//    {
//        std::vector<int> elements = {1,2,3,4};
//        std::wstring glue = L",";
//        std::wstring res = pjpl::alg::joinVariable(elements, glue);
//
//        CPPUNIT_ASSERT_MESSAGE("is = " + pjpl::wstr::toString(res) , res == L"<\">1<\"/>,<\">2<\"/>,<\">3<\"/>,<\"/>4<\"/>");
//    }
//    {
//        std::vector<double> elements = {1.1,2.2,3.3,99.999};
//        std::wstring glue = L",";
//        std::wstring res = pjpl::alg::joinVariable(elements, glue);
//
//        CPPUNIT_ASSERT_MESSAGE("is = " + pjpl::wstr::toString(res), res == L"<\">1.1<\"/>,<\">2.2<\"/>,<\">33<\"/>,<\">99.999<\">");
//    }
    {
        std::vector<std::wstring> elements = {L"1", L"2", L"3", L"4"};
        std::wstring glue = L",";
        std::wstring res = pjpl::alg::joinVariable(elements, glue);

        CPPUNIT_ASSERT_MESSAGE("is = " + pjpl::wstr::toString(res), res == L"<\">1<\"/>,<\">2<\"/>,<\">3<\"/>,<\">4<\"/>");
    }
}

void Alg::collectParams_str() {
    {
        std::string in =
                "<\">Time<\"/>=<\">12:00:00<\"/> and "
                "<\">Time<\"/> = <\"> 12:12:00 <\"/> or "
                "<\">Time<\"/> = <\"> 12:12:12 <\"/>";
        std::vector<std::string> out = pjpl::alg::collectParams(in, "Time");
        CPPUNIT_ASSERT(out.size() == 3);
        CPPUNIT_ASSERT(out[0] == "12:00:00");
        CPPUNIT_ASSERT(out[1] == "12:12:00");
        CPPUNIT_ASSERT(out[2] == "12:12:12");
    }
    {
        std::string in =
                " text-error <\">Time<\"/>=<\">12:00:00<\"/> "
                "and <\">Time<\"/> = <\"> 12:12:00 <\"/> "
                "and <\">Date<\"/> = <\"> 12312 <\"/> "
                "or <\">Date<\"/> = <\"> 12asdfa <\"/> "
                "and <\">x<\"/> != <\"> Y<\"/> "
                "or <\">Time<\"/> = <\">12:12:12<\"/> text error";
        std::vector<std::string> out = pjpl::alg::collectParams(in, "Time");
        CPPUNIT_ASSERT(out.size() == 3);
        CPPUNIT_ASSERT(out[0] == "12:00:00");
        CPPUNIT_ASSERT(out[1] == "12:12:00");
        CPPUNIT_ASSERT(out[2] == "12:12:12");
    }
}

void Alg::collectParams_wstr() {
    {
        std::wstring in =
                L"<\">Time<\"/>=<\">12:00:00<\"/> "
                "and <\">Time<\"/> = <\"> 12:12:00 <\"/> "
                "or <\">Time<\"/> = <\"> 12:12:12 <\"/>";
        std::vector<std::wstring> out = pjpl::alg::collectParams(in, L"Time");
        CPPUNIT_ASSERT(out.size() == 3);
        CPPUNIT_ASSERT(out[0] == L"12:00:00");
        CPPUNIT_ASSERT(out[1] == L"12:12:00");
        CPPUNIT_ASSERT(out[2] == L"12:12:12");
    }
    {
        std::wstring in =
                L" text-error <\">Time<\"/>=<\">12:00:00<\"/> "
                L"and <\">Time<\"/> = <\"> 12:12:00 <\"/> "
                L"and <\">Date<\"/> = <\"> 12312 <\"/> "
                L"or <\">Date<\"/> = <\"> 12asdfa <\"/> "
                L"and <\">x<\"/> != <\"> Y<\"/> "
                L"or <\">Time<\"/> = <\">12:12:12<\"/> text error";
        std::vector<std::wstring> out = pjpl::alg::collectParams(in, L"Time");
        CPPUNIT_ASSERT(out.size() == 3);
        CPPUNIT_ASSERT(out[0] == L"12:00:00");
        CPPUNIT_ASSERT(out[1] == L"12:12:00");
        CPPUNIT_ASSERT(out[2] == L"12:12:12");
    }
}

void Alg::collectInParams_wstr() {
    {
        std::wstring in =
            L" text-error " // <- must be omitted
            L"<\">MonitorId<\"/>=<\">1<\"/> "
            L"and <\">Time<\"/> = <\"> 12:12:00 <\"/> "
            L"and <\">Date<\"/> = <\"> 12312 <\"/> "
            L"or <\">Date<\"/> = <\"> 12asdfa <\"/> "
            L"and <\">x<\"/> != <\"> Y<\"/> "
            L"or <\">MonitorId<\"/> = <\">11<\"/>"
            L"<\">cf-none<\"/>=[<\">7<\"/>,<\">8<\"/>]"
            L" and <\">cf-sr<\"/> =[<\">1<\"/>,<\">2<\"/>,<\">9<\"/>]"
            L" and <\">cf-sw<\"/> =[<\">3<\"/>,<\">5<\"/>]"
            L" and <\">cf-it<\"/> =[<\">4<\"/>,<\">6<\"/>,<\">10<\"/>]"
            L" !blabla "; // <- must be omitted

        std::vector<std::wstring> cfNone = pjpl::alg::collectInParams(in, L"cf-none");
        std::vector<std::wstring> cfSr = pjpl::alg::collectInParams(in, L"cf-sr");
        std::vector<std::wstring> cfSw = pjpl::alg::collectInParams(in, L"cf-sw");
        std::vector<std::wstring> cfIt = pjpl::alg::collectInParams(in, L"cf-it");

        CPPUNIT_ASSERT_MESSAGE("cfNone.size() == " + std::to_string(cfNone.size()) ,cfNone.size() == 2);
        CPPUNIT_ASSERT_MESSAGE("cfNone[0] = " + pjpl::wstr::toString(cfNone[0]), cfNone[0] == L"7");
        CPPUNIT_ASSERT_MESSAGE("cfNone[1] = " + pjpl::wstr::toString(cfNone[1]), cfNone[1] == L"8");

        CPPUNIT_ASSERT_MESSAGE("cfSr.size() == " + std::to_string(cfSr.size()) ,cfSr.size() == 3);
        CPPUNIT_ASSERT_MESSAGE("cfSr[0] = " + pjpl::wstr::toString(cfSr[0]), cfSr[0] == L"1");
        CPPUNIT_ASSERT_MESSAGE("cfSr[1] = " + pjpl::wstr::toString(cfSr[1]), cfSr[1] == L"2");
        CPPUNIT_ASSERT_MESSAGE("cfSr[2] = " + pjpl::wstr::toString(cfSr[2]), cfSr[2] == L"9");

        CPPUNIT_ASSERT_MESSAGE("cfSw.size() == " + std::to_string(cfSw.size()) ,cfSw.size() == 2);
        CPPUNIT_ASSERT_MESSAGE("cfSw[0] = " + pjpl::wstr::toString(cfSw[0]), cfSw[0] == L"3");
        CPPUNIT_ASSERT_MESSAGE("cfSw[1] = " + pjpl::wstr::toString(cfSw[1]), cfSw[1] == L"5");

        CPPUNIT_ASSERT_MESSAGE("cfIt.size() == " + std::to_string(cfIt.size()) ,cfIt.size() == 3);
        CPPUNIT_ASSERT_MESSAGE("cfIt[0] = " + pjpl::wstr::toString(cfIt[0]), cfIt[0] == L"4");
        CPPUNIT_ASSERT_MESSAGE("cfIt[1] = " + pjpl::wstr::toString(cfIt[1]), cfIt[1] == L"6");
        CPPUNIT_ASSERT_MESSAGE("cfIt[2] = " + pjpl::wstr::toString(cfIt[2]), cfIt[2] == L"10");

    }
}