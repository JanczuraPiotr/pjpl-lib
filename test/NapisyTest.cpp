/*
 * File:   NapisyTest.cpp
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 12 sierpnia 2018, 11:55
 */

#include "NapisyTest.h"
#include <string>
#include "../../libs/napisy.h"
#include "../../libs/Logger.h"


CPPUNIT_TEST_SUITE_REGISTRATION(NapisyTest);

NapisyTest::NapisyTest() {
}

NapisyTest::~NapisyTest() {
}

void NapisyTest::setUp() {}
void NapisyTest::tearDown() {}

void NapisyTest::after_string_1() {
    std::wstring subject = L"<\">MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> = <\">11<\"/>";
    std::wstring token   = L"<\">";
    std::wstring::size_type start = 0;
    std::wstring::size_type after = pjpl::wstr::after(subject, token, start);

    CPPUNIT_ASSERT_MESSAGE(
            "SUBJECT : "
            + pjpl::wstr::toString(subject)
            + " pozycja -> "
            + std::to_string(after)
            + " [cursor] -> "
            + std::to_string(subject[after])
            , after == 3
    );
}

void NapisyTest::after_string_2() {
    std::wstring subject = L"<\">MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> = <\">11<\"/>";
    std::wstring token   = L"<\">";
    std::wstring::size_type start = 10;
    std::wstring::size_type after = pjpl::wstr::after(subject, token, start);

    CPPUNIT_ASSERT_MESSAGE(
            "SUBJECT : "
            + pjpl::wstr::toString(subject)
            + " pozycja -> "
            + std::to_string(after)
            + " [cursor] -> "
            + std::to_string(subject[after])
            , after == 21
    );
}

void NapisyTest::after_string_3() {
    std::wstring subject = L"<\">MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> = <\">11<\"/>";
    std::wstring token   = L"<\"/>";
    std::wstring::size_type start = 0;
    std::wstring::size_type after = pjpl::wstr::after(subject, token, start);

    CPPUNIT_ASSERT_MESSAGE(
            "SUBJECT : "
            + pjpl::wstr::toString(subject)
            + " pozycja -> "
            + std::to_string(after)
            + " [cursor] -> "
            + std::to_string(subject[after])
            , after == 17
   );
}
void NapisyTest::after_string_4() {
    std::wstring subject = L"<\">MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> = <\">11<\"/>";
    std::wstring token   = L"MonitorId";
    std::wstring::size_type start = 0;
    std::wstring::size_type after = pjpl::wstr::after(subject, token, start);

    CPPUNIT_ASSERT_MESSAGE(
            "SUBJECT : "
            + pjpl::wstr::toString(subject)
            + " pozycja -> "
            + std::to_string(after)
            + " [cursor] -> "
            + std::to_string(subject[after])
            , after == 12
    );
}
void NapisyTest::adjust_token_1() {
    std::vector<std::wstring> set = {{L"<\">"}, {L"<\"/>"}};
    std::wstring subject = L"<\">MonitorId <\"/>=<\">1<\"/> or<\">Person <\"/> = <\">11<\"/>";
    std::wstring::size_type start = 0;
    std::wstring token = pjpl::wstr::adjustToken(subject, start, set);

    CPPUNIT_ASSERT_MESSAGE("DOPASOWANIE -> " + pjpl::wstr::toString(token) , token == L"<\">");
}
void NapisyTest::between_1() {
    std::wstring str = L"[1]";
    std::wstring leftLim = L"[";
    std::wstring rightLim = L"]";
    std::size_t start = 0;
    std::size_t stop  = 0;
    std::wstring token = pjpl::wstr::between(str, leftLim, rightLim, start, stop);

    CPPUNIT_ASSERT(token == L"1");
    CPPUNIT_ASSERT_MESSAGE(std::to_string(start), start == 1);
    CPPUNIT_ASSERT_MESSAGE(std::to_string(stop), stop == 3);

}
void NapisyTest::between_2() {
    std::wstring str = L" ] [ 1 1 2] ";
    std::wstring leftLim = L"[";
    std::wstring rightLim = L"]";
    std::size_t start = 0;
    std::size_t stop  = 0;
    std::wstring token = pjpl::wstr::between(str, leftLim, rightLim, start, stop);

    CPPUNIT_ASSERT(token == L" 1 1 2");
    CPPUNIT_ASSERT(start == 4);
    CPPUNIT_ASSERT(stop == 11);

}
void NapisyTest::between_3() {
    std::wstring str = L" ść ś 1 1 2ć ";
    std::wstring leftLim = L"ś";
    std::wstring rightLim = L"ć";
    std::size_t start = 2;
    std::size_t stop  = 0;
    std::wstring token = pjpl::wstr::between(str, leftLim, rightLim, start, stop);

    CPPUNIT_ASSERT(token == L" 1 1 2");
    CPPUNIT_ASSERT(start == 5);
    CPPUNIT_ASSERT(stop == 12);

}
void NapisyTest::between_4() {
    std::wstring str = L" ść koń 1 1 2świnka ";
    std::wstring leftLim = L"koń";
    std::wstring rightLim = L"świnka";
    std::size_t start = 0;
    std::size_t stop  = 0;
    std::wstring token = pjpl::wstr::between(str, leftLim, rightLim, start, stop);

    CPPUNIT_ASSERT(token == L" 1 1 2");
    CPPUNIT_ASSERT(start == 7);
    CPPUNIT_ASSERT(stop == 19);

}
void NapisyTest::read_lim_is_string_1() {
    std::wstring subject = L" 12345 ĄŚĆŁ-ąśćł";
    std::wstring limes   = L" ";
    std::wstring::size_type start = 2;
    std::wstring::size_type stop  = 0;
    std::wstring token = pjpl::wstr::read(subject, start, stop, limes);

    CPPUNIT_ASSERT(token == L"2345");
    CPPUNIT_ASSERT(token.length() == 4);
    CPPUNIT_ASSERT_MESSAGE("pozycja stop -> " + std::to_string(stop) , stop == 7);
}
void NapisyTest::read_lim_is_string_2() {
    std::wstring subject = L" 12345 ĄŚĆŁ-ąśćł";
    std::wstring limes   = L"Ł";
    std::wstring::size_type start = 0;
    std::wstring::size_type stop  = 0;
    std::wstring token = pjpl::wstr::read(subject, start, stop, limes);

    CPPUNIT_ASSERT_MESSAGE("token -> '" + pjpl::wstr::toString(token) + "'", token == L"12345 ĄŚĆ");
    CPPUNIT_ASSERT(token.length() == 9);
    CPPUNIT_ASSERT_MESSAGE("pozycja stop -> " + std::to_string(stop) , stop == 11);
}
void NapisyTest::read_lim_is_string_3() {
    std::wstring subject = L" 12345 ĄŚĆŁ-ąśćł";
    std::wstring limes   = L"-ąś";
    std::wstring::size_type start = 6;
    std::wstring::size_type stop  = 0;
    std::wstring token = pjpl::wstr::read(subject, start, stop, limes);

    CPPUNIT_ASSERT_MESSAGE("token -> '" + pjpl::wstr::toString(token) + "'", token == L"ĄŚĆŁ");
    CPPUNIT_ASSERT(token.length() == 4);
    CPPUNIT_ASSERT_MESSAGE("pozycja stop -> " + std::to_string(stop) , stop == 14);
}
void NapisyTest::read_lim_is_string_4() {
    std::wstring subject = L"12345 ĄŚĆŁ-ąśćł";
    std::wstring limes   = L"Ł-ą";
    std::wstring::size_type start = 4;
    std::wstring::size_type stop  = 0;
    std::wstring token = pjpl::wstr::read(subject, start, stop, limes);

    CPPUNIT_ASSERT_MESSAGE("token -> '" + pjpl::wstr::toString(token) +"'", token == L"5 ĄŚĆ");
    CPPUNIT_ASSERT(token.length() == 5);
    CPPUNIT_ASSERT_MESSAGE("pozycja stop -> " + std::to_string(stop) , stop == 12);
}