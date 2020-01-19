#ifndef POLISH_NOTATION_TEST_H
#define POLISH_NOTATION_TEST_H

#include "../../alg/PolishNotation.h"

#include <cppunit/extensions/HelperMacros.h>

class PolishNotationTest : public CPPUNIT_NS::TestFixture {

    CPPUNIT_TEST_SUITE(PolishNotationTest);

    CPPUNIT_TEST(expression_add);
    CPPUNIT_TEST(expression_add_space);
    CPPUNIT_TEST(expression_add_mul);
    CPPUNIT_TEST(expression_add_mul_bracked);
    CPPUNIT_TEST(expression_complicated);
    
    CPPUNIT_TEST_SUITE_END();

public:

    PolishNotationTest();
    virtual ~PolishNotationTest();

    void setUp();
    void tearDown();

private:

    void expression_add();
    void expression_add_space();
    void expression_add_mul();
    void expression_add_mul_bracked();
    void expression_complicated();

};

#endif //POLISH_NOTATION_H