/*! \file setstr_compare_test.cc
 * 
 * \brief Includes definitions of the setstr_compare_test class members defined in the 
 * setstr_compare_test.h file
 *  
 * \details
 * This file contains definition of the undefined member functions of the class
 * setstr_compare_test.
 * 
 */
#include "setstr_compare_test.h"
#include "../declaration.h"


CPPUNIT_TEST_SUITE_REGISTRATION(setstr_compare_test);

setstr_compare_test::setstr_compare_test() {
}

setstr_compare_test::~setstr_compare_test() {
}

void setstr_compare_test::setUp() {
}

void setstr_compare_test::tearDown() {
}

void setstr_compare_test::testLess() {
    const set_str lhs = {"a", "b", "c"};
    const set_str& rhs = {"a", "b", "d"};
    setstr_compare _setstr_compare;
    bool result = _setstr_compare.less(lhs, rhs);
    CPPUNIT_ASSERT(result);
}

