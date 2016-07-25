/*! \file dependency_test.cc
 * 
 * \brief Includes definitions of the dependency_test class members defined in the 
 * dependency_test.h file
 *  
 * \details
 * This file contains definition of the undefined member functions of the class
 * dependency_test.
 * 
 */
#include "dependency_test.h"
#include <sstream>
#include "../dependency.h"


CPPUNIT_TEST_SUITE_REGISTRATION(dependency_test);

dependency_test::dependency_test() {
}

dependency_test::~dependency_test() {
}

void dependency_test::setUp() {
    ss1 = new set_str({"a", "b"});
    ss2 = new set_str({"c", "d"});
    dep = new Dependency(*ss1, *ss2);
}

void dependency_test::tearDown() {
    ss1->clear();
    ss2->clear();
    delete ss1;
    delete ss2;
    delete dep;
}

void dependency_test::testDependency() {
    Dependency d(*dep);
    CPPUNIT_ASSERT(isEqual(dep->lhs, d.lhs) && isEqual(dep->rhs, d.rhs));
}

void dependency_test::testGetLhs() {
    CPPUNIT_ASSERT(isEqual(dep->getLhs(), *ss1));

}

void dependency_test::testGetRhs() {
    CPPUNIT_ASSERT(isEqual(dep->getRhs(), *ss2));
}

void dependency_test::testGetAttribs() {
    set_str s(*ss1);
    s.insert(ss2->begin(), ss2->end());
    CPPUNIT_ASSERT(isEqual(dep->getAttribs(), s));
}

void dependency_test::testDependency2() {
    Dependency d(*ss1, *ss2);
    CPPUNIT_ASSERT(isEqual(*ss1, d.lhs) && isEqual(*ss2, d.rhs));
}

void dependency_test::testAddLhs() {
    const string p = "e";
    dep->addLhs(p);
    CPPUNIT_ASSERT(contains(dep->lhs, p));
}

void dependency_test::testAddRhs() {
    const string p = "g";
    dep->addRhs(p);
    CPPUNIT_ASSERT(contains(dep->rhs, p));
}

void dependency_test::testRemoveLhs() {
    const string p = "a";
    dep->removeLhs(p);
    CPPUNIT_ASSERT_MESSAGE("Remove LHS failed ", !contains(dep->lhs, p));
}

void dependency_test::testRemoveRhs() {
    const string p = "c";
    dep->removeRhs(p);
    CPPUNIT_ASSERT(!contains(dep->rhs, p));
}

void dependency_test::testIsPresentLhs() {
    const string p = "a";
    CPPUNIT_ASSERT(dep->isPresentLhs(p) && !dep->isPresentLhs("w"));
}

void dependency_test::testIsPresentRhs() {
    const string p = "d";
    CPPUNIT_ASSERT(dep->isPresentRhs(p) && !dep->isPresentRhs("w"));
}

void dependency_test::testIsPresent() {
    const string p = "w";
    CPPUNIT_ASSERT(!dep->isPresent(p) && dep->isPresent("a")
            && dep->isPresent("d"));
}

void dependency_test::testSize() {
    unsigned int result = dep->size();
    unsigned int exp = dep->lhs.size() + dep->rhs.size();
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The dependency size is wrong",exp, result);

}

void dependency_test::testSetLhs() {
    dep->setLhs(*ss2);
    CPPUNIT_ASSERT(isEqual(dep->lhs, *ss2));

}

void dependency_test::testSetRhs() {
    dep->setLhs(*ss1);
    CPPUNIT_ASSERT(isEqual(dep->lhs, *ss1));
}

void dependency_test::testClearLhs() {
    dep->clearLhs();
    CPPUNIT_ASSERT(dep->lhs.empty());

}

void dependency_test::testClearRhs() {
    dep->clearRhs();
    CPPUNIT_ASSERT(dep->rhs.empty());
}

void dependency_test::testClear() {
    dep->clear();
    CPPUNIT_ASSERT(dep->lhs.empty() && dep->rhs.empty());
}

void dependency_test::testOperatorOut() {
    std::ostringstream os;
    os << *dep;
    CPPUNIT_ASSERT(os.str() == "a, b -> c, d");
}

void dependency_test::testOperatorLess() {
    Dependency d(*ss2, *ss1);
    CPPUNIT_ASSERT(*dep < d);
}

void dependency_test::testOperatorGreat() {
    Dependency d(*ss2, *ss1);
    CPPUNIT_ASSERT(d > *dep);
}

void dependency_test::testOperatorEq() {
    Dependency d(*dep);
    CPPUNIT_ASSERT(d == *dep);
}

void dependency_test::testOperatorNotEq() {
    Dependency d(*dep);
    CPPUNIT_ASSERT(d == *dep);
}

void dependency_test::testOperatorPlusEq() {

    Dependency d(dep->lhs, {
        "l,m"
    });
    *dep += d;
    CPPUNIT_ASSERT(isSubset(dep->rhs, d.rhs));
}

