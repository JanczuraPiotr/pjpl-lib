/*
 * File:   DateTimeTest.h
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 2018-05-27, 15:15:08
 */

#ifndef DATETIMETEST_H
#define DATETIMETEST_H

#include <cppunit/extensions/HelperMacros.h>

class DateTimeTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(DateTimeTest);

    CPPUNIT_TEST(testDateTime);
    CPPUNIT_TEST(testDateTime_copy);
    CPPUNIT_TEST(testDateTime_string_1);
    CPPUNIT_TEST(testDateTime_string_2);
    CPPUNIT_TEST(testDateTime_string_2016_02_28_23_59_59);
    CPPUNIT_TEST(testDateTime_string_2016_02_29_23_59_59);
    CPPUNIT_TEST(testDateTime_string_2017_02_28_23_59_59);
    CPPUNIT_TEST(testDateTime_string_2017_02_29_23_59_59);
    CPPUNIT_TEST(testCheck);
    CPPUNIT_TEST(testSet_string);
    CPPUNIT_TEST(testGetStringDateTime);
    CPPUNIT_TEST(testGetStringDate);
    CPPUNIT_TEST(testGetStringTime);
    CPPUNIT_TEST(testNextSec);
    CPPUNIT_TEST(testDiffSec1);
    CPPUNIT_TEST(testDiffSec2);
    CPPUNIT_TEST(testDiffSec3);
    CPPUNIT_TEST(testDiffSec4);
    CPPUNIT_TEST(testAdd1);
    CPPUNIT_TEST(testAdd2);
    CPPUNIT_TEST(testConstructorDuration1);
    CPPUNIT_TEST(testConstructorDuration2);

    CPPUNIT_TEST_SUITE_END();

public:
    DateTimeTest();
    virtual ~DateTimeTest();
    void setUp();
    void tearDown();

private:
    void testDateTime();
    void testDateTime_copy();
    void testDateTime_string_1();
    void testDateTime_string_2();
    void testDateTime_string_2016_02_28_23_59_59();
    void testDateTime_string_2016_02_29_23_59_59();
    void testDateTime_string_2017_02_28_23_59_59();
    void testDateTime_string_2017_02_29_23_59_59();
    void testCheck();
    void testSet_string();
    void testGetStringDateTime();
    void testGetStringDate();
    void testGetStringTime();
    void testNextSec();
    void testDiffSec1();
    void testDiffSec2();
    void testDiffSec3();
    void testDiffSec4();
    void testAdd1();
    void testAdd2();
    void testConstructorDuration1();
    void testConstructorDuration2();

};

#endif /* DATETIMETEST_H */

