//
// Created by piotr@janczura.pl on 2020.01.20
//

#include "DateTimeTest.h"

#include <limits>
#include <iostream>

#include "../lib/DateTime.h"

namespace test{

TEST_F(DateTimeTest, init_from_string_YYYY_MM_dd_hh_mm_ss)
{
    pjpl::String dateString("1970-01-01 00:00:00");
    pjpl::DateTime dateTime(dateString);

    EXPECT_EQ(dateTime.getStringDateTime(), dateString);
    EXPECT_EQ(dateTime.getStringDate(), dateString.substr(0, 10));
    EXPECT_EQ(dateTime.getStringTime(), dateString.substr(11, 9));
}

TEST_F(DateTimeTest, check)
{
    pjpl::String timeStr = "1r111";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11-11 12:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::DATE_HOUR);
    timeStr = "1111-11-11 00:00:00";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::DATE_HOUR);
    timeStr = "1111-11-11 ";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11-11";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::DATE);
    timeStr = "1111-k1-11 12:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11-41 12:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11-11 12:52:52";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::DATE_HOUR);
    timeStr = "1111-11-11 32:52:52";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11-1112:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11-11:12:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111k11-11 12:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "11y1-11-11 12:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "111-11-11 12:12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11-11 12:12";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
    timeStr = "1111-11";
    EXPECT_TRUE(pjpl::DateTime::check(timeStr) == pjpl::DateTime::Type::BAD);
}

TEST_F(DateTimeTest, transformFromYmD)
{
    {
        std::string inDate = "11-11-2011";
        std::string outDate = "2011-11-11";
        EXPECT_EQ(pjpl::DateTime::transformFromYmD(inDate), outDate);
    }
    {
        std::string inDate = "11.11.2011";
        std::string outDate = "2011-11-11";
        EXPECT_EQ(pjpl::DateTime::transformFromYmD(inDate), outDate);
    }
}

TEST_F(DateTimeTest, time_t)
{
    pjpl::DateTime dt;
    std::time_t tt = boost::posix_time::to_time_t(boost::posix_time::microsec_clock::local_time());
    if (dt.time_t() != tt) {
        if (dt.time_t() <= tt + 2) {
            // zakładam że w czasie testu może zmienić się czas pomiędzy konstruktorem dt a odczytem time_t
            EXPECT_TRUE(false);
        }
    }
}

TEST_F(DateTimeTest, testGetStringTime)
{
    std::string sDateTime   = "2018-02-28 23:59:59";
    std::string sDate       = "2018-02-28";
    std::string sTime       = "23:59:59";
    try {
        pjpl::DateTime dt1(sDateTime);
        EXPECT_EQ(dt1.getStringTime(), sTime);
    } catch (...) {
        EXPECT_TRUE(false) << ("input = " + sDateTime);
    }

    sDateTime   = "2018-02-28 00:00:00";
    sDate       = "2018-02-28";
    sTime       = "00:00:00";
    try {
        pjpl::DateTime dt2(sDateTime);
        EXPECT_EQ(dt2.getStringDateTime(), sDateTime);
    } catch (std::exception &e) {
        EXPECT_TRUE(false) << ("input = " + sDateTime + " exception : " + e.what());
    } catch (...) {
        EXPECT_TRUE(false) << ("input = " + sDateTime);
    }
}


TEST_F(DateTimeTest,testDateTime_copy) {
    pjpl::DateTime dt1;
    pjpl::DateTime dt2(dt1);
    if (dt1.time_t() != dt2.time_t()) {
        EXPECT_TRUE(false);
    }
}

TEST_F(DateTimeTest, testDateTime_string_1)
{
    std::string sData = "2018-01-12 23:59:59";
    pjpl::DateTime dt(sData);
    EXPECT_EQ(dt.getString(), sData) << ("input data = " + sData + " result data = " + dt.getString());
}

TEST_F(DateTimeTest,testDateTime_string_2) {
    std::string sData = "2018-01-31 23:59:59";
    pjpl::DateTime dt(sData);
    EXPECT_EQ(dt.getString(), sData) << ("input data = " + sData + " result data = " + dt.getString());
}

TEST_F(DateTimeTest, testDateTime_string_2016_02_28_23_59_59) {
    std::string sData = "2016-02-28 23:59:59";
    pjpl::DateTime dt(sData);
    EXPECT_EQ(dt.getString(), sData) << ("input data = " + sData + " result data = " + dt.getString());
}

TEST_F(DateTimeTest, testDateTime_string_2016_02_29_23_59_59){
    std::string sData = "2016-02-29 23:59:59";
    pjpl::DateTime dt(sData);
    EXPECT_EQ(dt.getString(), sData) << ("input data = " + sData + " result data = " + dt.getString());
}

TEST_F(DateTimeTest, testDateTime_string_2017_02_28_23_59_59) {
    std::string sData = "2017-02-28 23:59:59";
    pjpl::DateTime dt(sData);
    EXPECT_EQ(dt.getString(), sData) << ("input data = " + sData + " result data = " + dt.getString());
}

TEST_F(DateTimeTest, testDateTime_string_2017_02_29_23_59_59) {
    pjpl::String sData = "2017-02-29 23:59:59";
    try {
        pjpl::DateTime dateTime(sData);// boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::gregorian::bad_day_of_month> >);
        FAIL() << "nie wykryto złego dnia w dacie 2017-02-29 23:59:59";
    } catch (...) {
    }
}

TEST_F(DateTimeTest, testGetStringDateTime){
    std::string sd = "2018-02-28 23:59:59";
    try {
        pjpl::DateTime dt1(sd);
        EXPECT_EQ(dt1.getString(), sd) << ("input = " + sd + " result = " + dt1.getString());
    } catch (...) {
        EXPECT_TRUE(false) << ("input = " + sd);
    }

    sd = "2018-02-28 00:00:00";
    try {
        pjpl::DateTime dt2(sd);
        EXPECT_EQ(dt2.getString(), sd) << ("input = " + sd + " result = " + dt2.getString());
    } catch (...) {
        EXPECT_TRUE(false) << ("input = " + sd);
    }
}

TEST_F (DateTimeTest, testGetStringDate) {
    std::string sDateTime   = "2018-02-28 23:59:59";
    std::string sDate       = "2018-02-28";
    std::string sTime       = "23:59:59";
    try {
        pjpl::DateTime dt1(sDateTime);
        EXPECT_EQ(dt1.getStringDate(), sDate) << ("input = " + sDateTime + " result = " + dt1.getStringDate());
    } catch (...) {
        EXPECT_TRUE(false) << ("input = " + sDateTime );
    }

    sDateTime   = "2018-02-28 00:00:00";
    sDate       = "2018-02-28";
    sTime       = "00:00:00";
    try {
        pjpl::DateTime dt2(sDateTime);
        EXPECT_EQ(dt2.getStringDate(), sDate) << ("input = " + sDateTime + " result = " + dt2.getStringDate());
    } catch (...) {
        EXPECT_TRUE(false) << ("input = " + sDateTime);
    }
}

//TEST_F(DateTimeTest, testNextSec) {
//    {
//        std::string sd = "2016-02-28 23:59:59";
//        pjpl::DateTime dt(sd);
//        dt.nextSec();
//        CPPUNIT_ASSERT_MESSAGE("input = " + sd + " po dt.nextSec() result = " + dt.getString(), dt.getString() == "2016-02-29 00:00:00");
//    }
//    {
//        std::string sd = "2017-02-28 23:59:59";
//        pjpl::DateTime dt(sd);
//        dt.nextSec();
//        CPPUNIT_ASSERT_MESSAGE("input = " + sd + " po dt.nextSec() result = " + dt.getString(), dt.getString() == "2017-03-01 00:00:00");
//    }
//    {
//        std::string sd = "2018-12-31 23:59:59";
//        pjpl::DateTime dt(sd);
//        dt.nextSec();
//        CPPUNIT_ASSERT_MESSAGE("input = " + sd + " po dt.nextSec() result = " + dt.getString(), dt.getString() == "2019-01-01 00:00:00");
//    }
//}
//
//    void DateTimeTest::testDiffSec1() {
//        std::string sd1 = "2016-01-01 23:59:59";
//        std::string sd2 = "2016-01-02 00:00:00";
//        pjpl::DateTime dt1(sd1);
//        pjpl::DateTime dt2(sd2);
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt1.diffInSec(dt2) | input "
//                "sd1 -> " + sd1 + " | "
//                                  "sd2 -> " + sd2 + " | "
//                                                    "result = " + std::to_string(dt1.diffInSec(dt2))
//                , dt1.diffInSec(dt2) == 1);
//    }
//
//    void DateTimeTest::testDiffSec2() {
//        std::string sd1 = "2016-12-31 23:59:59";
//        std::string sd2 = "2017-01-01 00:00:00";
//        pjpl::DateTime dt1(sd1);
//        pjpl::DateTime dt2(sd2);
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt1.diffInSec(dt2) input "
//                "sd1 -> " + sd1 + " | "
//                                  "sd2 -> " + sd2 + " | "
//                                                    "result = " + std::to_string(dt2.diffInSec(dt1))
//                , dt2.diffInSec(dt1) == -1);
//    }
//
//    void DateTimeTest::testDiffSec3() {
//        std::string sd1 = "2016-02-28 23:59:59";
//        std::string sd2 = "2016-02-29 00:00:00";
//        pjpl::DateTime dt1(sd1);
//        pjpl::DateTime dt2(sd2);
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt1.diffInSec(dt2) input "
//                "sd1 -> " + sd1 + " | "
//                                  "sd2 -> " + sd2 + " | "
//                                                    "result = " + std::to_string(dt1.diffInSec(dt2))
//                , dt1.diffInSec(dt2) == 1);
//    }
//    void DateTimeTest::testDiffSec4() {
//        std::string sd1 = "2016-02-27 23:59:59";
//        std::string sd2 = "2016-02-28 00:00:00";
//        pjpl::DateTime dt1(sd1);
//        pjpl::DateTime dt2(sd2);
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt1.diffInSec(dt2) input "
//                "sd1 -> " + sd1 + " | "
//                                  "sd2 -> " + sd2 + " | "
//                                                    "result = " + std::to_string(dt1.diffInSec(dt2))
//                , dt1.diffInSec(dt2) == 1);
//    }
//    void DateTimeTest::testAdd1() {
//        std::string sd1 = "2016-02-27 23:59:59";
//        boost::posix_time::time_duration td(0,0,1);
//        pjpl::DateTime dt1(sd1);
//        pjpl::DateTime dt2 = dt1 + td;
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt1.diffInSec(dt2) input "
//                "sd1 -> " + sd1 + " | "
//                                  "time_duration ->  (0,0,1)| "
//                                  "result = " + dt2.getString()
//                , dt2.getString() == "2016-02-28 00:00:00");
//    }
//    void DateTimeTest::testAdd2() {
//        std::string sd1 = "2016-02-27 23:59:59";
//        boost::posix_time::time_duration td(24,0,1);
//        pjpl::DateTime dt1(sd1);
//        pjpl::DateTime dt2 = dt1 + td;
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt1.diffInSec(dt2) input "
//                "sd1 -> " + sd1 + " | "
//                                  "time_duration ->  (24,0,1)| "
//                                  "result = " + dt2.getString()
//                , dt2.getString() == "2016-02-29 00:00:00");
//    }
//    void DateTimeTest::testConstructorDuration1() {
//        pjpl::DateTime dt1;
//        pjpl::DateTime dt2(dt1, boost::posix_time::time_duration(0, 0, 11));
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt2 - dt1 > 10 -> " + std::to_string(dt1.diffInSec(dt2))
//                , dt1.diffInSec(dt2) == 11 || dt1.diffInSec(dt2) == 10);
//    }
//    void DateTimeTest::testConstructorDuration2() {
//        pjpl::DateTime dt1;
//        pjpl::DateTime dt2(boost::posix_time::time_duration(0, 0, 11));
//        CPPUNIT_ASSERT_MESSAGE(
//                "dt2 - dt1 > 10 -> " + std::to_string(dt1.diffInSec(dt2))
//                , dt1.diffInSec(dt2) == 11 || dt1.diffInSec(dt2) == 10);
//    }
}