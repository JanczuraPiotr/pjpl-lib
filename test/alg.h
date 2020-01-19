/*
 * File:   alg.h
 * Author: Piotr Janczura <piotr@janczura.pl>
 *
 * Created on 5 października 2018, 15:30
 */

#ifndef ALG_H
#define ALG_H

#include <cppunit/extensions/HelperMacros.h>

class Alg : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(Alg);

    CPPUNIT_TEST(join);
    CPPUNIT_TEST(joinVariable);
    CPPUNIT_TEST(collectParams_str);
    CPPUNIT_TEST(collectParams_wstr);
    CPPUNIT_TEST(collectInParams_wstr);

    CPPUNIT_TEST_SUITE_END();
public:

    Alg();
    virtual ~Alg();

    void setUp();
    void tearDown();

private:

    void join();
    void joinVariable();
    void collectParams_str();
    void collectParams_wstr();
    void collectInParams_wstr();
};

#endif /* ALG_H */

