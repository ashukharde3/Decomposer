/*! @file UserInterface.h
 * 
 * @brief Includes declaration for the class UserInterface and its members.
 *  
 * @details
 * This file declares the definition of the class UserInterface along with its 
 * subsequent data members and the member functions prototype.This class is 
 * designed to test the functions from utility.h file.
 * 
 */
#ifndef UTILITY_TEST_H
#define UTILITY_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../declaration.h"

class utility_test : public CPPUNIT_NS::TestFixture {

    CPPUNIT_TEST_SUITE(utility_test);

    CPPUNIT_TEST(testContains);
    CPPUNIT_TEST(testIsPart);
    CPPUNIT_TEST(testIsEqual);
    CPPUNIT_TEST(testIsSubset);
    CPPUNIT_TEST(testContains2);
    CPPUNIT_TEST(testOutOperator);
    CPPUNIT_TEST(testSubOperator);
    CPPUNIT_TEST(testSubOperator1);

    CPPUNIT_TEST_SUITE_END();

public:
    utility_test();
    virtual ~utility_test();
    void setUp();
    void tearDown();

private:
    void testContains();
    void testIsPart();
    void testIsEqual();
    void testIsSubset();
    void testContains2();
    void testOutOperator();
    void testSubOperator();
    void testSubOperator1();

    set_key *key;
    set_str *lhs, *rhs;

};

#endif /* UTILITY_TEST_H */

