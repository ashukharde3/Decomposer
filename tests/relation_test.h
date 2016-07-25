/*! @file relation_test.h
 * 
 * @brief Includes declaration for the class relation_test and its members.
 *  
 * @details
 * This file declares the definition of the class relation_test along with its 
 * subsequent data members and the member functions prototype. This class is 
 * designed to test the methods from the Relation class.
 * 
 */
#ifndef RELATION_TEST__H
#define RELATION_TEST__H

#include <cppunit/extensions/HelperMacros.h>
#include "../declaration.h"

class relation_test : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(relation_test);

    CPPUNIT_TEST(testRelation);
    CPPUNIT_TEST(testRelation2);
    CPPUNIT_TEST(testAddAtributte);
    CPPUNIT_TEST(testAddAtributtes);
    CPPUNIT_TEST(testRemoveAtributte);
    CPPUNIT_TEST(testRemoveDependency);
    CPPUNIT_TEST(testRemoveDependency2);
    CPPUNIT_TEST(testAddDependencies);
    CPPUNIT_TEST(testAddDependency);
    CPPUNIT_TEST(testAddDependency2);
    CPPUNIT_TEST(testFindDepLHS);
    CPPUNIT_TEST(testIsNormal);
    CPPUNIT_TEST(testIsDepAttribPresent);
    CPPUNIT_TEST(testIsSuperkey);
    CPPUNIT_TEST(testIsPartialkey);
    CPPUNIT_TEST(testIsPrime);
    CPPUNIT_TEST(testGetClosure);
    CPPUNIT_TEST(testGetCandidatekey);
    CPPUNIT_TEST(testGetViolation);
    CPPUNIT_TEST(testGetMinimalCover);
    CPPUNIT_TEST(testDecomposePreserving);
    CPPUNIT_TEST(testDecomposeNotPreserving);
    CPPUNIT_TEST(testClearDependencies);
    CPPUNIT_TEST(testClearAttributes);
    CPPUNIT_TEST(testGetAttributes);
    CPPUNIT_TEST(testGetDependencies);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST(testSetName);

    CPPUNIT_TEST_SUITE_END();

public:
    relation_test();
    virtual ~relation_test();
    void setUp();
    void tearDown();

private:
    Relation *rel;
    void testRelation();
    void testRelation2();
    void testAddAtributte();
    void testAddAtributtes();
    void testRemoveAtributte();
    void testRemoveDependency();
    void testRemoveDependency2();
    void testAddDependencies();
    void testAddDependency();
    void testAddDependency2();
    void testFindDepLHS();
    void testIsNormal();
    void testIsDepAttribPresent();
    void testIsSuperkey();
    void testIsPartialkey();
    void testIsPrime();
    void testGetClosure();
    void testGetCandidatekey();
    void testGetViolation();
    void testGetMinimalCover();
    void testDecomposePreserving();
    void testDecomposeNotPreserving();
    void testClearDependencies();
    void testClearAttributes();
    void testGetAttributes();
    void testGetDependencies();
    void testGetName();
    void testSetName();
    

};

#endif /* RELATION_TEST__H */

