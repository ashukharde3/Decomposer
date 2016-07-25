/*! @file dependency_test.h
 * 
 * @brief Includes declaration for the class dependency_test and its members.
 *  
 * @details
 * This file declares the definition of the class dependency_test along with its 
 * subsequent data members and the member functions prototype.This class is 
 * designed to test the methods from the Dependency class.
 * 
 */
#ifndef DEPENDENCY_TEST_H
#define DEPENDENCY_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../declaration.h"

class dependency_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(dependency_test);

    CPPUNIT_TEST(testDependency);
    CPPUNIT_TEST(testGetLhs);
    CPPUNIT_TEST(testGetRhs);
    CPPUNIT_TEST(testGetAttribs);
    CPPUNIT_TEST(testDependency2);
    CPPUNIT_TEST(testAddLhs);
    CPPUNIT_TEST(testAddRhs);
    CPPUNIT_TEST(testRemoveLhs);
    CPPUNIT_TEST(testRemoveRhs);
    CPPUNIT_TEST(testIsPresentLhs);
    CPPUNIT_TEST(testIsPresentRhs);
    CPPUNIT_TEST(testIsPresent);
    CPPUNIT_TEST(testSize);
    CPPUNIT_TEST(testSetLhs);
    CPPUNIT_TEST(testSetRhs);
    CPPUNIT_TEST(testClearLhs);
    CPPUNIT_TEST(testClearRhs);
    CPPUNIT_TEST(testClear);
    CPPUNIT_TEST(testOperatorOut);
    CPPUNIT_TEST(testOperatorLess);
    CPPUNIT_TEST(testOperatorGreat);
    CPPUNIT_TEST(testOperatorEq);
    CPPUNIT_TEST(testOperatorNotEq);
    CPPUNIT_TEST(testOperatorPlusEq);

    CPPUNIT_TEST_SUITE_END();

public:
    dependency_test();
    virtual ~dependency_test();
    void setUp();
    void tearDown();

private:
    Dependency *dep;
    set_str *ss1, *ss2;
    void testDependency();
    void testGetLhs();
    void testGetRhs();
    void testGetAttribs();
    void testDependency2();
    void testAddLhs();
    void testAddRhs();
    void testRemoveLhs();
    void testRemoveRhs();
    void testIsPresentLhs();
    void testIsPresentRhs();
    void testIsPresent();
    void testSize();
    void testSetLhs();
    void testSetRhs();
    void testClearLhs();
    void testClearRhs();
    void testClear();
    void testOperatorOut();
    void testOperatorLess();
    void testOperatorGreat();
    void testOperatorEq();
    void testOperatorNotEq();
    void testOperatorPlusEq();

};

#endif /* DEPENDENCY_TEST_H */

