/*! \file utility_test.cc
 * 
 * \brief Includes definitions of the utility_test class members defined in the 
 * utility_test.h file
 *  
 * \details
 * This file contains definition of the undefined member functions of the class
 * utility_test.
 * 
 */
#include "utility_test.h"
#include "../utility.h"


#include <sstream>
using std::ostringstream;

CPPUNIT_TEST_SUITE_REGISTRATION(utility_test);

utility_test::utility_test() {
}

utility_test::~utility_test() {
}

void utility_test::setUp() {
    key = new set_key;
    lhs = new set_str;
    rhs = new set_str;
    lhs->insert({"a", "b", "c", "d"});
    rhs->insert({"c", "d"});
    key->insert({"c", "d"});
    key->insert({"a", "b", "c"});
    key->insert({"a", "e", "f"});
}

void utility_test::tearDown() {
    key->clear();
    lhs->clear();
    rhs->clear();
    delete lhs;
    delete rhs;
    delete key;
}

void utility_test::testOutOperator() {
    ostringstream os;

    os << *lhs;
    string str = os.str();
//    std::cout << "Expected:\"" << str << "\"" << std::endl;
    CPPUNIT_ASSERT(str == "a, b, c, d");
}

void utility_test::testSubOperator() {
    *lhs -= *rhs;
    CPPUNIT_ASSERT(isEqual(*lhs,{"a", "b"}));
}

void utility_test::testSubOperator1() {
    set_key key2(*key);
    key2.erase({"a", "b", "c"});
    *key -= key2;

    CPPUNIT_ASSERT(key->size() == 1 &&
            isEqual(*(key->begin()), {
        "a", "b", "c"
    }));
}

void utility_test::testContains() {
    bool result = contains(*key, *rhs);
    CPPUNIT_ASSERT(result);
}

void utility_test::testIsPart() {
    bool result = testSet(*key, *rhs, true);
    CPPUNIT_ASSERT(result);

}

void utility_test::testIsEqual() {
    bool result = isEqual(*lhs, *rhs);
    CPPUNIT_ASSERT(!result && isEqual(*rhs,{"c", "d"}));

}

void utility_test::testIsSubset() {
    const set_str test = {"a", "d", "c"};
    bool result = isSubset(*lhs, test);
    CPPUNIT_ASSERT(result);
}

void utility_test::testContains2() {
    const string val = "a";
    bool result = contains(*lhs, val);
    CPPUNIT_ASSERT(result);

}

