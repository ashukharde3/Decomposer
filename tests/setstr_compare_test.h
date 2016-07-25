/*! @file setstr_compare_test.h
 * 
 * @brief Includes declaration for the class setstr_compare_test and its members.
 *  
 * @details
 * This file declares the definition of the class setstr_compare_test along with its 
 * subsequent data members and the member functions prototype. This class is 
 * designed to test the methods from the setstr_compare class.
 * 
 */


#ifndef SETSTR_COMPARE_TEST_H
#define SETSTR_COMPARE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

class setstr_compare_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(setstr_compare_test);

    CPPUNIT_TEST(testLess);

    CPPUNIT_TEST_SUITE_END();

public:
    setstr_compare_test();
    virtual ~setstr_compare_test();
    void setUp();
    void tearDown();

private:
    void testLess();

};

#endif /* SETSTR_COMPARE_TEST_H */

