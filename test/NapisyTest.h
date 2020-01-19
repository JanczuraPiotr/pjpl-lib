/*
 * File:   NapisyTest.h
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 12 sierpnia 2018, 11:55
 */

#ifndef NAPISYTEST_H
#define NAPISYTEST_H

#include <cppunit/extensions/HelperMacros.h>

class NapisyTest  : public CPPUNIT_NS::TestFixture {

    CPPUNIT_TEST_SUITE(NapisyTest);

    CPPUNIT_TEST(after_string_1);
    CPPUNIT_TEST(after_string_2);
    CPPUNIT_TEST(after_string_3);
    CPPUNIT_TEST(after_string_4);
    CPPUNIT_TEST(adjust_token_1);
    CPPUNIT_TEST(between_1);
    CPPUNIT_TEST(between_2);
    CPPUNIT_TEST(between_3);
    CPPUNIT_TEST(between_4);
    CPPUNIT_TEST(read_lim_is_string_1);
    CPPUNIT_TEST(read_lim_is_string_2);
    CPPUNIT_TEST(read_lim_is_string_3);
    CPPUNIT_TEST(read_lim_is_string_4);

    CPPUNIT_TEST_SUITE_END();

public:
    NapisyTest();
    virtual ~NapisyTest();

    void setUp();
    void tearDown();

private:
    void after_string_1();
    void after_string_2();
    void after_string_3();
    void after_string_4();
    void adjust_token_1();
    void between_1();
    void between_2();
    void between_3();
    void between_4();
    void read_lim_is_string_1();
    void read_lim_is_string_2();
    void read_lim_is_string_3();
    void read_lim_is_string_4();
};

#endif /* NAPISYTEST_H */

