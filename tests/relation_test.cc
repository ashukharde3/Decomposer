/*! \file relation_test.cc
 * 
 * \brief Includes definitions of the relation_test class members defined in the 
 * relation_test.h file
 *  
 * \details
 * This file contains definition of the undefined member functions of the class
 * relation_test.
 * 
 */

#include "relation_test.h"
#include "../relation.h"


CPPUNIT_TEST_SUITE_REGISTRATION(relation_test);

relation_test::relation_test() {
}

relation_test::~relation_test() {
}

void relation_test::setUp() {
    rel = new Relation("R",{"a", "b", "c", "d", "e", "f", "g", "h"});
    rel->dependencies.insert(Dependency({"a"},
    {
        "b", "f"
    }));

    rel->dependencies.insert(Dependency({"a", "c"},
    {
        "d", "g"
    }));

    rel->dependencies.insert(Dependency({"b", "c", "d"},
    {
        "e", "h"
    }));
}

void relation_test::tearDown() {
    delete rel;
}

void relation_test::testRelation() {
    const string p = "R";
    const set_str temp = {"a", "b", "c", "d", "e", "f", "g", "h"};
    set_dep t2;
    t2.insert(Dependency({"a"},
    {
        "b", "f"
    }));

    t2.insert(Dependency({"a", "c"},
    {
        "d", "g"
    }));

    t2.insert(Dependency({"b", "c", "d"},
    {
        "e", "h"
    }));

    CPPUNIT_ASSERT_MESSAGE("parameterized constructor failed",
            rel->name == p && isEqual(temp, rel->attributes)
            && isEqual(t2, rel->dependencies));

}

void relation_test::testRelation2() {
    Relation s(*rel);
    CPPUNIT_ASSERT_MESSAGE("copy constructor failed",
            rel->name == s.name
            && isEqual(s.attributes, rel->attributes)
            && isEqual(s.dependencies, rel->dependencies));
}

void relation_test::testAddAtributte() {
    const string p = "i", p1 = "a";

    CPPUNIT_ASSERT_MESSAGE("adding new attribute failed",
            rel->addAtributte(p) && contains(rel->attributes, p));

    CPPUNIT_ASSERT_MESSAGE("adding empty string or existing attribute failed",
            !rel->addAtributte(p1) && !rel->addAtributte(""));
}

void relation_test::testAddAtributtes() {
    const set_str& p = {"k", "l", "m", "a", "b"};

    CPPUNIT_ASSERT_MESSAGE("adding new attribute set failed",
            (rel->addAtributtes(p) && isSubset(rel->attributes, p)));

    CPPUNIT_ASSERT_MESSAGE("adding existing attribute set failed",
            !rel->addAtributtes(rel->attributes));

}

void relation_test::testRemoveAtributte() {
    const string p = "a", q = "x";

    CPPUNIT_ASSERT_MESSAGE("removing existing attribute failed",
            rel->removeAtributte(p) && !contains(rel->attributes, p));

    CPPUNIT_ASSERT_MESSAGE("removing non-existing attribute failed",
            !rel->removeAtributte(q) && !contains(rel->attributes, q));
}

void relation_test::testRemoveDependency() {
    const set_str p0 = {"a", "c"};
    const set_str p1 = {"d"};
    Dependency d(p0,{"d", "g"});
    Dependency d1(p0, p1);
    Dependency d2(p0,{"g"});
    bool res = rel->removeDependency(p0, p1);
    CPPUNIT_ASSERT_MESSAGE("remove dependency with existing lhs and subset of rhs failed",
            res && !contains(rel->dependencies, d)
            && !contains(rel->dependencies, d1)
            && contains(rel->dependencies, d2));
}

void relation_test::testRemoveDependency2() {
    Dependency d({"a", "c"},
    {
        "d", "g"
    });
    CPPUNIT_ASSERT_MESSAGE("remove complete dependency failed",
            rel->removeDependency(d)
            && !contains(rel->dependencies, d)
            && !rel->removeDependency(d));
}

void relation_test::testAddDependencies() {
    Dependency d1({"x", "y"},
    {
        "b", "f"
    });
    Dependency d2({"p", "q"},
    {
        "r", "s"
    });
    Dependency d3({"x", "y"},
    {
        "z"
    });

    Dependency d4({"b"},
    {
        "l", "m", "n"
    });

    set_dep d = {d1, d2, d3, d4};
    unsigned int orig = rel->getDependencies().size();
    CPPUNIT_ASSERT_MESSAGE("add dependencies with no existing lhs and no update failed",
            !(rel->addDependencies(d, false)));
    unsigned int size = rel->addDependencies(d, true);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("add dependencies with update and no existing attributes failed",
            (unsigned int) 4, size);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("add dependencies with update and no existing attributes failed to reduce dependencies",
            (unsigned int) rel->dependencies.size(), (unsigned int) (orig + size - 1));

}

void relation_test::testAddDependency() {
    const set_str p0 = {"a"};
    const set_str p1 = {"c", "e", "b", "f"};
    Dependency d(p0,{"b", "f"});
    Dependency d1(p0, p1);
    itr_dep i = rel->addDependency(p0, p1, false);

    CPPUNIT_ASSERT_MESSAGE("add dependency with existing lhs and rhs failed",
            i != rel->dependencies.end()
            && !contains(rel->dependencies, d)
            && contains(rel->dependencies, d1));

}

void relation_test::testAddDependency2() {
    const set_str p0 = {"a"};
    const set_str p1 = {"x", "y", "z"};
    Dependency d(p0, p1);
    itr_dep i = rel->addDependency(p0, p1, false);
    CPPUNIT_ASSERT_MESSAGE("add dependency with no update" \
             " existing lhs and non existing rhs failed",
            i == rel->dependencies.end());
    i = rel->addDependency(p0, p1, true);
    d.rhs.insert({"b", "f"});
    CPPUNIT_ASSERT_MESSAGE("add dependency with update" \
            " existing lhs and non existing rhs failed",
            i != rel->dependencies.end() &&
            contains(rel->dependencies, d)
            && isSubset(rel->attributes, p1));
    //std::cout << *rel << std::endl;
}

void relation_test::testFindDepLHS() {
    const set_str p0 = {"a"};
    const set_str p1 = {"b", "f"};

    Dependency d(p0, p1);
    CPPUNIT_ASSERT_MESSAGE("find dependency with lhs failed",
            *(rel->findDepLHS(p0)) == d &&
            rel->findDepLHS(p1) == rel->dependencies.end());
}

void relation_test::testIsNormal() {
    //    bool result = rel->isNormal(Relation::_2NF);
    CPPUNIT_ASSERT_MESSAGE("test normal failed", !rel->isNormal(Relation::_2NF)
            && !rel->isNormal(Relation::_3NF)
            && !rel->isNormal(Relation::_BCNF));

}

void relation_test::testIsDepAttribPresent() {
    set_str l = {"a"};
    set_str r = {"b", "f"};
    Dependency d1(l, r);
    l = {"x"};
    r = {"y"};
    Dependency d2(r, l);

    CPPUNIT_ASSERT_MESSAGE("find dependency attributes are present in relation failed",
            rel->isDepAttribPresent(d1)
            && !rel->isDepAttribPresent(d2));

}

void relation_test::testIsSuperkey() {
    set_str a = {"a"};
    set_str b = {"a", "c"};
    set_str c = {"c", "d"};
    set_str d = {"a", "b", "c", "d"};

    CPPUNIT_ASSERT_MESSAGE("failed to check is attribute set is super-key",
            !rel->isSuperkey(a) && rel->isSuperkey(b)
            && !rel->isSuperkey(c) && rel->isSuperkey(d));
}

void relation_test::testIsPartialkey() {
    set_str a = {"a"};
    set_str b = {"a", "c"};
    set_str c = {"c", "d"};
    set_str d = {"a", "b", "c", "d"};
    CPPUNIT_ASSERT_MESSAGE("failed to check is attribute set is partial key",
            rel->isPartialkey(a) && !rel->isPartialkey(b)
            && !rel->isPartialkey(c) && !rel->isPartialkey(d));

}

void relation_test::testIsPrime() {
    set_str a = {"a"};
    set_str b = {"a", "c"};
    set_str c = {"c", "d"};
    set_str d = {"a", "b", "c", "d"};
    CPPUNIT_ASSERT_MESSAGE("failed to check is attributes are prime attributes",
            rel->isPrime(a) && rel->isPrime(b)
            && !rel->isPrime(c) && !rel->isPrime(d));
}

void relation_test::testGetClosure() {
    set_str b = {"a", "c"};
    set_str c = {"b"};
    CPPUNIT_ASSERT_MESSAGE("closure operation failed",
            isEqual(rel->getClosure(b), rel->attributes)
            && isEqual(rel->getClosure(c), c));
}

void relation_test::testGetCandidatekey() {
    set_str b = {"a", "c"};
//    std::cout<<rel->getCandidatekey()<<std::endl;
    CPPUNIT_ASSERT_MESSAGE("candidate key set is invalid",
            contains(rel->getCandidatekey(), b)
            && rel->getCandidatekey().size() == 1);
}

void relation_test::testGetViolation() {
    Dependency d1({"a"},
    {
        "b", "f"
    });

    Dependency d2({"a", "c"},
    {
        "d", "g"
    });
    set_dep v = rel->getViolation(Relation::_2NF);

    CPPUNIT_ASSERT_MESSAGE("dependency set with normal form violation is invalid",
            contains(v, d1) && v.size() == 1);


}

void relation_test::testGetMinimalCover() {
    Dependency d({"d"},
    {
        "e", "h"
    });
    Dependency d1({"d", "b", "c"},
    {
        "e", "h"
    });
    rel->dependencies.insert(d);
    set_dep mc = rel->getMinimalCover();


    CPPUNIT_ASSERT_MESSAGE("invalid minimal cover set", contains(mc, d)
            && !contains(mc, d1) && mc.size() == 3);

}

void relation_test::testDecomposePreserving() {
    set_rel res = rel->decomposePreserving();
    Dependency d1({"a"},
    {
        "b", "f"
    });
    Dependency d2({"a", "c"},
    {
        "d", "g"
    });
    Dependency d3({"b", "c", "d"},
    {
        "e", "h"
    });
    Relation r1("R1",{"a", "b", "f"},
    {
        d1
    });
    Relation r2("R2",{"a", "c", "d", "g"},
    {
        d2
    });
    Relation r3("R3",{"b", "c", "d", "e", "h"},
    {
        d3
    });

    if (true /*check result*/) {
        CPPUNIT_ASSERT_MESSAGE("Invalid FD preserving decomposition",
                res.size() == 3
                && contains(res, r1)
                && contains(res, r2)
                && contains(res, r3));
    }
}

void relation_test::testDecomposeNotPreserving() {
    set_rel res = rel->decomposeNotPreserving();
    //std::cout << std::boolalpha << res << std::endl;
    bool result = true;
    for (Relation r : res) {
        if (!r.isNormal(Relation::_BCNF)) {
            result = false;
            break;
        }
    }
    CPPUNIT_ASSERT_MESSAGE("Invalid non FD preserving decomposition", result);

}

void relation_test::testClearDependencies() {
    rel->clearDependencies();
    CPPUNIT_ASSERT_MESSAGE("clear dependencies failed", 
            rel->dependencies.empty());

}

void relation_test::testClearAttributes() {
    rel->clearAttributes();
    CPPUNIT_ASSERT_MESSAGE("clear attributes failed", rel->attributes.empty());
}

void relation_test::testGetAttributes() {
    CPPUNIT_ASSERT_MESSAGE("getAttributes failed", 
            rel->getAttributes() == rel->attributes);
}

void relation_test::testGetDependencies() {
    CPPUNIT_ASSERT_MESSAGE("getDependencies failed", 
            isEqual(rel->getDependencies() , rel->dependencies));
}

void relation_test::testGetName() {
    CPPUNIT_ASSERT_MESSAGE("getName failed", rel->getName() == rel->name);
}

void relation_test::testSetName() {
    rel->setName("S");
    CPPUNIT_ASSERT_MESSAGE("setName failed", rel->name == "S");
}


