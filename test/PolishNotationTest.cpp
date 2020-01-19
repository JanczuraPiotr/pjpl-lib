#ifndef POLISH_NOTATION_H
#define POLISH_NOTATION_H

#include "../../libs/Logger.h"
#include "PolishNotationTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(PolishNotationTest);


PolishNotationTest::PolishNotationTest() {

}

PolishNotationTest::~PolishNotationTest() {

}

void PolishNotationTest::setUp() {

}

void PolishNotationTest::tearDown() {

}

void PolishNotationTest::expression_add() 
{
    std::wstring expression = L"<\">a<\"/>+<\">b<\"/>";    
    pjpl::alg::PolishNotation polishNotation;
    pjpl::alg::PolishNotation::Postfix result;

    try {
        polishNotation.expression(1, expression);
        result = polishNotation.postfix(1);
    } catch (...) {
        CPPUNIT_ASSERT_MESSAGE("exception ... ", false);
    }

    CPPUNIT_ASSERT_MESSAGE("powinno być : 3", result.size() == 3);
    CPPUNIT_ASSERT_MESSAGE("powinno być : a jest -> " + pjpl::wstr::toString(result.at(0)), result.at(0) == L"a");
    CPPUNIT_ASSERT_MESSAGE("powinno być : b jest -> " + pjpl::wstr::toString(result.at(1)), result.at(1) == L"b");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(2)), result.at(2) == L"+");
}

void PolishNotationTest::expression_add_space() 
{
    std::wstring expression = L"<\"> a<\"/> + <\"> b<\"/>";    
    pjpl::alg::PolishNotation polishNotation;
    pjpl::alg::PolishNotation::Postfix result;

    try {
        polishNotation.expression(1, expression);
        result = polishNotation.postfix(1);
    } catch (...) {
        CPPUNIT_ASSERT_MESSAGE("exception ... ", false);
    }

    CPPUNIT_ASSERT_MESSAGE("powinno być : 3", result.size() == 3);
    CPPUNIT_ASSERT_MESSAGE("powinno być : a jest -> " + pjpl::wstr::toString(result.at(0)), result.at(0) == L"a");
    CPPUNIT_ASSERT_MESSAGE("powinno być : b jest -> " + pjpl::wstr::toString(result.at(1)), result.at(1) == L"b");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(2)), result.at(2) == L"+");
}

void PolishNotationTest::expression_add_mul()
{
    std::wstring expression = L"<\">a<\"/> + <\">b<\"/>*<\">c<\"/>";
    pjpl::alg::PolishNotation polishNotation;
    pjpl::alg::PolishNotation::Postfix result;

    try {
        polishNotation.expression(1, expression);
        result = polishNotation.postfix(1);
    } catch (...) {
        CPPUNIT_ASSERT_MESSAGE("exception ... ", false);
    }

    CPPUNIT_ASSERT_MESSAGE("powinno być : 3", result.size() == 5);
    CPPUNIT_ASSERT_MESSAGE("powinno być : a jest -> " + pjpl::wstr::toString(result.at(0)), result.at(0) == L"a");
    CPPUNIT_ASSERT_MESSAGE("powinno być : b jest -> " + pjpl::wstr::toString(result.at(1)), result.at(1) == L"b");
    CPPUNIT_ASSERT_MESSAGE("powinno być : c jest -> " + pjpl::wstr::toString(result.at(2)), result.at(2) == L"c");
    CPPUNIT_ASSERT_MESSAGE("powinno być : * jest -> " + pjpl::wstr::toString(result.at(3)), result.at(3) == L"*");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(4)), result.at(4) == L"+");
}

void PolishNotationTest::expression_add_mul_bracked()
{
    std::wstring expression = L"<\">a<\"/> + <\">b<\"/>*<\">c<\"/>*(<\">d<\"/> + <\">e<\"/>)";
    pjpl::alg::PolishNotation polishNotation;
    pjpl::alg::PolishNotation::Postfix result;

    try {
        polishNotation.expression(1, expression);
        result = polishNotation.postfix(1);
    } catch (...) {
        CPPUNIT_ASSERT_MESSAGE("exception ... ", false);
    }

    CPPUNIT_ASSERT_MESSAGE("powinno być : 8 jest -> " + std::to_string(result.size()), result.size() == 9);
    CPPUNIT_ASSERT_MESSAGE("powinno być : a jest -> " + pjpl::wstr::toString(result.at(0)), result.at(0) == L"a");
    CPPUNIT_ASSERT_MESSAGE("powinno być : b jest -> " + pjpl::wstr::toString(result.at(1)), result.at(1) == L"b");
    CPPUNIT_ASSERT_MESSAGE("powinno być : c jest -> " + pjpl::wstr::toString(result.at(2)), result.at(2) == L"c");
    CPPUNIT_ASSERT_MESSAGE("powinno być : * jest -> " + pjpl::wstr::toString(result.at(3)), result.at(3) == L"*");
    CPPUNIT_ASSERT_MESSAGE("powinno być : d jest -> " + pjpl::wstr::toString(result.at(4)), result.at(4) == L"d");
    CPPUNIT_ASSERT_MESSAGE("powinno być : e jest -> " + pjpl::wstr::toString(result.at(5)), result.at(5) == L"e");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(6)), result.at(6) == L"+");
    CPPUNIT_ASSERT_MESSAGE("powinno być : * jest -> " + pjpl::wstr::toString(result.at(7)), result.at(7) == L"*");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(8)), result.at(8) == L"+");
}

void PolishNotationTest::expression_complicated() 
{
    // a + b * c - ( d - (e / f) + g) + h + ((i - j / k) * l)
    std::wstring expression = 
    L" <\">a<\"/> + <\">b<\"/> * <\">c<\"/> - ( <\">d<\"/> - (<\">e<\"/> / <\">f<\"/>) + <\">g<\"/>)+ <\">h<\"/> + ((<\">i<\"/> - <\">j<\"/> / <\">k<\"/>) * <\">l<\"/>)";

    pjpl::alg::PolishNotation polishNotation;
    pjpl::alg::PolishNotation::Postfix result;

    try {
        polishNotation.expression(1, expression);
        result = polishNotation.postfix(1);
    } catch (...) {
        CPPUNIT_ASSERT_MESSAGE("exception ... ", false);
    }

    CPPUNIT_ASSERT_MESSAGE("powinno być : 23 jest -> " + std::to_string(result.size()), result.size() == 23);
    CPPUNIT_ASSERT_MESSAGE("powinno być : a jest -> " + pjpl::wstr::toString(result.at(0)), result.at(0) == L"a");
    CPPUNIT_ASSERT_MESSAGE("powinno być : b jest -> " + pjpl::wstr::toString(result.at(1)), result.at(1) == L"b");
    CPPUNIT_ASSERT_MESSAGE("powinno być : c jest -> " + pjpl::wstr::toString(result.at(2)), result.at(2) == L"c");
    CPPUNIT_ASSERT_MESSAGE("powinno być : * jest -> " + pjpl::wstr::toString(result.at(3)), result.at(3) == L"*");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(4)), result.at(4) == L"+");
    CPPUNIT_ASSERT_MESSAGE("powinno być : d jest -> " + pjpl::wstr::toString(result.at(5)), result.at(5) == L"d");
    CPPUNIT_ASSERT_MESSAGE("powinno być : e jest -> " + pjpl::wstr::toString(result.at(6)), result.at(6) == L"e");
    CPPUNIT_ASSERT_MESSAGE("powinno być : f jest -> " + pjpl::wstr::toString(result.at(7)), result.at(7) == L"f");
    CPPUNIT_ASSERT_MESSAGE("powinno być : / jest -> " + pjpl::wstr::toString(result.at(8)), result.at(8) == L"/");
    CPPUNIT_ASSERT_MESSAGE("powinno być : - jest -> " + pjpl::wstr::toString(result.at(9)), result.at(9) == L"-");
    CPPUNIT_ASSERT_MESSAGE("powinno być : g jest -> " + pjpl::wstr::toString(result.at(10)), result.at(10) == L"g");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(11)), result.at(11) == L"+");
    CPPUNIT_ASSERT_MESSAGE("powinno być : - jest -> " + pjpl::wstr::toString(result.at(12)), result.at(12) == L"-");
    CPPUNIT_ASSERT_MESSAGE("powinno być : h jest -> " + pjpl::wstr::toString(result.at(13)), result.at(13) == L"h");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(14)), result.at(14) == L"+");
    CPPUNIT_ASSERT_MESSAGE("powinno być : i jest -> " + pjpl::wstr::toString(result.at(15)), result.at(15) == L"i");
    CPPUNIT_ASSERT_MESSAGE("powinno być : j jest -> " + pjpl::wstr::toString(result.at(16)), result.at(16) == L"j");
    CPPUNIT_ASSERT_MESSAGE("powinno być : k jest -> " + pjpl::wstr::toString(result.at(17)), result.at(17) == L"k");
    CPPUNIT_ASSERT_MESSAGE("powinno być : / jest -> " + pjpl::wstr::toString(result.at(18)), result.at(18) == L"/");
    CPPUNIT_ASSERT_MESSAGE("powinno być : - jest -> " + pjpl::wstr::toString(result.at(19)), result.at(19) == L"-");
    CPPUNIT_ASSERT_MESSAGE("powinno być : l jest -> " + pjpl::wstr::toString(result.at(20)), result.at(20) == L"l");
    CPPUNIT_ASSERT_MESSAGE("powinno być : * jest -> " + pjpl::wstr::toString(result.at(21)), result.at(21) == L"*");
    CPPUNIT_ASSERT_MESSAGE("powinno być : + jest -> " + pjpl::wstr::toString(result.at(22)), result.at(22) == L"+");
}

#endif //POLISH_NOTATION_H