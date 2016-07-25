/*! \file relation.cc
 * 
 * \brief Includes definitions of the Relation class members defined in the 
 * relation.h file
 *  
 * \details
 * This file contains definition of all the undefined member functions of the 
 * class Relation. 
 */
#include "relation.h"
#include "utility.h"
#include "dependency.h"
#include "violation.h"

#include <functional> 
#include <algorithm>
#include <vector>
using std::vector;

#include<iomanip>

/**
 * 
 * @param rset a set_rel representing the set of the sub relation. All the 
 * decomposed sub relation will be added to this set.
 * @param r a relation object which is to be decomposed into the sub-relations.
 * @param details a boolean parameter with default value false. If true the steps
 * involved in the decomposition will be printed on standard output stream cout.
 * @details This is a recursive static function. If the relation parameter r is 
 * not in the BCNF, then it uses the algorithm for the non-preserving FD decomposition
 * algorithm to construct the sub-relation and repeats the procedure until all 
 * the sub-relations are in BCNF.
 * 
 */
void Relation::decompose(set_rel &rset, const Relation &r, bool details) {
    if (r.isNormal(Relation::_BCNF)) {
        rset.insert(r);
        if (details) {
            std::cout << std::endl << std::setw(WIDTH) << std::right << ""
                    << std::endl << std::setw(WIDTH) << std::right << "" << "Sub-relation added: " << r << std::endl;
            std::cout << std::setw(WIDTH) << std::right << "" << "Candidate key: " << r.getCandidatekey() << std::endl;
        }
        return;
    }
    set_dep v = r.getViolation(Relation::_BCNF);

    if (details) {
        std::cout << std::endl << std::setw(WIDTH) << std::right << "" << "Relation is not in BCNF : " << r << std::endl;
        std::cout << std::setw(WIDTH) << std::right << "" << "Candidate key: " << r.getCandidatekey() << std::endl;
        std::cout << std::setw(WIDTH) << std::right << "" << "Violations " << v << std::endl;
    }
    const Dependency& d = *(v.begin());
    set_str list = r.getAttributes();
    set_str dep = d.getAttribs();
    list -= d.getRhs();
    Relation r1((r.getName() + "1"), list);
    r1.addDependencies(r.getDependencies(), false);

    Relation r2((r.getName() + "2"), dep);
    r2.addDependencies(r.getDependencies(), false);

    Relation::decompose(rset, r1, details);
    Relation::decompose(rset, r2, details);
}

/**
 * 
 * @param keys A set of existing working set in candidate key calculation.
 * @param atribs The attribute set referred to calculate the next iteration of 
 * working set in candidate key calculation.
 * @details This is the static method to calculate the next working set in 
 * candidate key calculation. The working set involves all the possible combination 
 * of relation attribute which is to be tested to determine the candidate key.
 * The next iteration of working set will be constructed by adding one of the 
 * remaining attribute to find out all the possible combinations.
 */
void Relation::getNextIteration(set_key& keys, const set_str& atribs) {
    set_key ret;
    for (itr_key i = keys.begin(); i != keys.end(); ++i) {
        for (itr_str j = atribs.begin(); j != atribs.end(); ++j) {
            set_str s = *i;
            if (s.insert(*j).second)
                ret.insert(s);
        }
    }
    keys.clear();
    keys = ret;
}

/**
 * 
 * @param str is the string representing the name of the Relation.
 * @param attribs is the set_str object that represents the attribute set for the
 * newly constructed relation.It have default value as empty set_str object so 
 * the constructor can be used with different no of arguments the relation
 * object will have an empty attribute set, if the attrib parameter is not provided.
 * @param is the set_dep object that represents the dependency set for the
 * newly constructed relation.It have default value as empty set_dep object so 
 * the constructor can be used with different no of arguments and the relation
 * object will have an empty dependency set, if the dep parameter is not provided.
 */
Relation::Relation(const string &str, const set_str &attribs, const set_dep &dep) :
name(str), attributes(attribs) {
    addDependencies(dep);
}

/**
 * 
 * @param orig is the constant reference to the Relation object from which the 
 * data members used to initialize newly constructed object.
 * @details The copy constructor uses all the data member from the parameter orig
 * and initialize the data members of new object.
 */
Relation::Relation(const Relation& orig) :
name(orig.name), attributes(orig.attributes) {
    addDependencies(orig.dependencies);
}

/**
 * @details The destructor will clear all the name, attribute set and 
 * dependency set of the relation object.
 */
Relation::~Relation() {
    name.clear();
    dependencies.clear();
    attributes.clear();
}

/**
 * 
 * @param str a string set parameter represents the lhs value to search for.
 * @return The iterator position of the dependency object from the dependency 
 * set if the dependency is found with same lhs as the parameter. It returns the
 * set::end iterator of the attribute set if the parameter is not equal to the 
 * any of dependency object's lhs form the dependency set of the relation.
 */
itr_dep Relation::findDepLHS(const set_str &str) const {
    return (find_if(dependencies.begin(), dependencies.end(),
            [ & ] (const Dependency & d) {
                return (isEqual(d.lhs, str));
            }));
}

/**
 * @details This method will combined all the rhs set into one dependency object,
 * from the dependency set of the relation, if multiple dependency have same lhs
 * set.
 */
void Relation::reducedDependencies(void) {
    for (itr_dep i = dependencies.begin(); i != dependencies.end();) {
        unsigned int count = count_if(dependencies.begin(), dependencies.end(),
                [ & ] (const Dependency & d) {
                    return (isEqual(d.lhs, i->lhs));
                });
        if (count > 1) {
            set_str lhs = i->lhs;
            set_str rhs = i->rhs;
            for_each(dependencies.begin(), dependencies.end(),
                    [ & ] (const Dependency & d) {
                        if (isEqual(d.lhs, lhs)) {
                            rhs.insert(d.rhs.begin(), d.rhs.end());
                        }
                    });
            Dependency d(lhs, rhs);
            dependencies.insert(d);
            dependencies.erase(i++);
        } else {
            ++i;
        }

    }
}

/**
 * 
 * @param lhs is string set representing the lhs side of the dependency.
 * @param rhs is string set representing the rhs side of the dependency.
 * @param update is boolean parameter with default value true. If the update 
 * value is true then all the attributes form lhs and rhs which are not part of
 * the attribute set of the relation object will added to the attribute set 
 * first. No new attribute will be inserted into the relation attribute set if
 * the update value is false.
 * @return If the dependency is added into the dependency set for the relation
 * object, the iterator pointing to the newly added dependency object will be 
 * returned. If dependency is already present in the dependency set then the iterator 
 * pointing to the existing dependency object will be returned. If no dependency 
 * is added to the relation then the set::end for the dependency set will be returned.
 * @details All the the attributes from the rhs which are subset of lhs will be 
 * removed first and if the rhs is empty then the dependency will not be added to 
 * the relation. If the rhs is not empty then the new Dependency object will be 
 * created with lhs and modified rhs and the private method Relation::addDependency
 * will be used with the update parameter value to insert the dependency into the
 * dependency set. In this case the return value from Relation::addDependency will
 * be returned back.
 * 
 */
itr_dep Relation::addDependency(const set_str &lhs, const set_str &rhs, bool update) {
    set_str temp = rhs;
    for (itr_str i = temp.begin(); i != temp.end();) {
        if (contains(lhs, *i)) {
            temp.erase(i++);
        } else {
            ++i;
        }
    }
    if (temp.empty())
        return dependencies.end();
    Dependency d = Dependency(lhs, temp);
    return addDependency(d, update);
}

/**
 * 
 * @param dep A dependency object to be inserted into the dependency set of the 
 * relation.
 * @param update is boolean parameter with default value true. If the update 
 * value is true then all the attributes form lhs and rhs which are not subset of
 * attribute set of the relation, will added to the attribute set first. No new 
 * attribute will be inserted into the relation attribute set if the update value 
 * is false and the lhs and rhs contains some attributes which are not subset of
 * relation attribute set. 
 * @return If the dependency is added into the dependency set for the relation
 * object, the iterator pointing to the newly added dependency object will be 
 * returned. If dependency is already present in the dependency set then the iterator 
 * pointing to the existing dependency object will be returned. If no dependency 
 * is added to the relation then the set::end for the dependency set will be returned.
 * @details If lhs and rhs are subset of the attribute set of the relation,
 * then the dependency will added to the set. If the update option is ture and 
 * lhs or rhs are not subset of the attribute set then all the attributes from 
 * both lhs and rhs will be inserted into the relation attribute set first, then
 * the dependency will be added. If update is false and the lhs is not subset of 
 * the attribute set of relation then no dependency will be added. If update is 
 * false and only rhs is not subset of relation attribute set then the only those
 * attributes from the rhs which are part of the attribute set will be considered 
 * and all other attributes will be discarded from rhs and then the dependency 
 * will be inserted into the dependency set. Note that if dependency is inserted 
 * into the dependency set then private method Relation::reduceDependecy will be
 * used to minimize the dependency set with same lhs values and the resultant 
 * position of the newly inserted dependency will be returned.
 */
itr_dep Relation::addDependency(const Dependency &dep, bool update) {

    Dependency d(dep);
    if (!isSubset(attributes, dep.getAttribs())) {
        if (update) {
            set_str ss = dep.getAttribs();
            attributes.insert(ss.begin(), ss.end());
        } else {
            if (isSubset(attributes, d.lhs)) {

                for (itr_str i = d.rhs.begin(); i != d.rhs.end();) {
                    if (!contains(attributes, *i))
                        d.rhs.erase(i++);
                    else
                        ++i;
                }
                if (d.rhs.empty())
                    return dependencies.end();
            } else {
                return dependencies.end();
            }
        }
    }
    dependencies.insert(d);
    reducedDependencies();
    return this->findDepLHS(dep.lhs);
}

/**
 * 
 * @param dep is a constant reference to the Dependency object for which the check
 * is to be performed.
 * @return true if all the attributes form the dependency lhs and rhs 
 * set are subset of the attribute set of the relation object, false otherwise.
 */
bool Relation::isDepAttribPresent(const Dependency &dep) const {
    return (count_if(attributes.begin(), attributes.end(),
            [ & ] (const string & s) {
                return dep.isPresent(s);
            }) > 0);
}

/**
 * 
 * @param lhs is string set representing the lhs side of the dependency.
 * @param rhs is string set representing the rhs side of the dependency.
 * @return true if the dependency is found and removed from the dependency set
 * false otherwise.
 * @details It creates the temporary Dependency object from lhs and rhs and then 
 * uses private method Relation::removeDependency to remove it from the 
 * dependency set.
 */
bool Relation::removeDependency(const set_str &lhs, const set_str &rhs) {
    Dependency d(lhs, rhs);
    return (removeDependency(d));
}

/**
 * 
 * @param dep constant reference to the dependency object to be removed from the
 * dependency set.
 * @return true if the dependency is found and removed, false otherwise.
 * @details This method will first finds the exact match for the dependency by 
 * finding the dependency object from the dependency set which has same lhs and 
 * rhs as parameter dep. If no such dependency is found, then the dependency with
 * the same lhs will be searched. If found then the only the rhs part of parameter
 * dep will be removed from the from the matching result. If no dependency is found
 * to remove or modify then the false value will be returned.
 */
bool Relation::removeDependency(const Dependency &dep) {
    if (dependencies.erase(dep) != 0)
        return true;
    itr_dep i = findDepLHS(dep.lhs);
    bool ret = false;
    if (i != dependencies.end()) {
        Dependency d(*i);
        for (const string &str : dep.rhs) {
            ret = d.removeRhs(str) && !ret ? true : ret;
        }
        if (ret) {
            dependencies.erase(i);
            ret = true;
            if (!d.rhs.empty())
                addDependency(d);
        }
    }
    //    std::cout << "\nRel: " << *this << std::endl;
    return ret;
}

/**
 * 
 * @param str a constant string representing the single attribute to be added into
 * the attribute set of the relation object..
 * @return true if the new attribute is inserted, false otherwise.
 * @details The parameter str will be inserted if it is no already present in the
 * attribute set.
 */
bool Relation::addAtributte(const string &str) {
    if (!str.empty())
        return (attributes.insert(str).second);
    return false;
}

/**
 * 
 * @param as is set_str object represent the attribute set to be added to the 
 * attribute set of the relation object.
 * @return true at least one attribute from parameter set is inserted in the 
 * relation object attribute set, false otherwise.
 */
unsigned int Relation::addAtributtes(const set_str &as) {
    return count_if(as.begin(), as.end(), [&] (const string & str) {
        return (this->attributes.insert(str).second);
    });
}

/**
 * 
 * @param str a constant string representing the single attribute to be removed 
 * from the attribute set of the relation object.
 * @return true if attribute is removed from the set, false otherwise.
 * @details If the attribute is not found in the attribute set of the relation
 * object then no attribute will be removed. If it is found in the relation then
 * the attribute will be removed. The dependency set will be searched to find out 
 * dependencies which contains the removed attribute. If the attribute present in
 * lhs part of the dependency the entire dependency will be removed from dependency
 * set. If the attribute is found only in rhs set of the dependency, then the attribute
 * will be removed from rhs as well.
 */
bool Relation::removeAtributte(const string &str) {
    set_dep temp;
    for (itr_dep i = dependencies.begin(); i != dependencies.end();) {
        if (i->isPresent(str)) {
            if (!i->isPresentLhs(str)) {
                Dependency d(*i);
                d.removeRhs(str);
                if (!d.rhs.empty())
                    temp.insert(d);
            }
            dependencies.erase(i++);
        } else {
            ++i;
        }
    }

    if (!temp.empty()) {
        this->addDependencies(temp, false);
    }

    return (attributes.erase(str) != 0);
}

/**
 * 
 * @param details a boolean parameter with default value false. If true the steps
 * involved in the decomposition will be printed on standard output stream cout.
 * @return set_rel object representing the set of decomposed sub-relations.
 * @details The method will use the FD-preserving decomposition algorithm to 
 * decompose the relation into the sub-relations and returns the set of such relations.
 * The decomposed sub relation will have all the dependencies which can preserve 
 * the original dependency set. It will also ensures that each sub-relation is in
 * at least 3NF.
 */
set_rel Relation::decomposePreserving(bool details) const {
    set_rel ret;
    set_dep mc = getMinimalCover(details);
    unsigned int i = 0;
    set_key keys = getCandidatekey();
    itr_dep found = find_if(mc.begin(), mc.end(), [&] (const Dependency d) {
        return testSet(keys, d.getAttribs(), true);
    });

    if (mc.end() == found) {
        Relation r((this->name + std::to_string(++i)), *keys.begin());
        r.addDependencies(mc, false);
        ret.insert(r);
        if (details)
            std::cout << std::setw(WIDTH) << std::right << "" << "Sub-Relation Added" << r << std::endl;
    }
    for (const Dependency d : mc) {

        unsigned int c = (count_if(ret.begin(), ret.end(),
                [&] (const Relation & temp) {
                    return isSubset(temp.attributes, d.getAttribs());
                }));

        if (c < 1) {

            Relation r(("R" + std::to_string(++i)), d.getAttribs());
            r.addDependencies(mc, false);

            ret.insert(r);
            if (details) {

                std::cout << std::setw(WIDTH) << std::right << "" << "Sub-Relation Added" << r << std::endl;
            }
        }

    }
    if (ret.empty())
        ret.insert(*this);

    return ret;
}

/**
 * 
 * @param details a boolean parameter with default value false. If true the steps
 * involved in the decomposition will be printed on standard output stream cout.
 * @return set_rel object representing the set of decomposed sub-relations.
 * @details The method will use the FD-preserving decomposition algorithm to 
 * decompose the relation into the sub-relations and returns the set of such relations.
 * All the decomposed sub relation will be in BCNF but it will not guarantees that
 * all the original dependencies are preserved from dependencies found in all 
 * sub-relations. It uses the private static method Relation::decompose to perform
 * the operation using recursive method.
 */
set_rel Relation::decomposeNotPreserving(bool details)const {
    set_rel res;
    Relation::decompose(res, *this, details);

    return res;
}

/**
 * 
 * @param lhs is the set_str object that represents the set of attributes on
 * which closure operation is to be performed.
 * @return the set_str object containing all the attribute which are result of 
 * the closure operation.
 * @detaisl The method will find out all the possible attributes which can be derived 
 * by the parameter lhs using dependency set of the relation.
 */
set_str Relation::getClosure(const set_str &lhs) const {
    set_str ret(lhs);
    bool flag;
    do {
        flag = false;
        for (const Dependency & d : this->dependencies) {
            if (isSubset(ret, d.lhs)) {
                unsigned int size = ret.size();
                ret.insert(d.rhs.begin(), d.rhs.end());
                if (size < ret.size())
                    flag = true;
            }
        };
    } while (flag);
    return ret;
}

/**
 * 
 * @param form represents the normal form from one of the Relation::Normal value.
 * @return set of dependency from dependencies of the relation object which violates 
 * the condition for the given normal form indicated by the parameter form. 
 * @details It uses the functor object of Violation as predicate to find out the
 * return value.
 */
set_dep Relation::getViolation(const Relation::Normal &form) const {
    set_dep dep;
    Violation v(*this, form);
    itr_dep res = dependencies.begin();
    do {
        res = find_if(res, dependencies.end(), v);
        if (res != dependencies.end()) {
            dep.insert(*res);
            ++res;
        }
    } while (res != dependencies.end());

    return dep;
}

/**
 * @details This method will clear all the dependency set of the relation object.
 */
void Relation::clearDependencies() {

    dependencies.clear();
}

/**
 * @details This method will clear all the attribute set and dependency set of 
 * the relation object.
 */
void Relation::clearAttributes() {

    dependencies.clear();
    attributes.clear();
}

/**
 * 
 * @param dependencies is a set of dependencies which will replace the current 
 * dependency set of the relation object.
 */
void Relation::setDependencies(const set_dep &dependencies) {

    this->clearDependencies();
    this->addDependencies(dependencies);
}

/**
 * 
 * @param attributes is a set of attributes which will replace the current 
 * attribute set of the relation object.
 * @details The dependencies will be modified so the dependency which have 
 * attributes from new attribute set will be preserved. All other dependencies 
 * will be removed from dependency set of the relation.
 */
void Relation::setAttributes(const set_str attributes) {

    set_dep temp = dependencies;
    this->clearAttributes();
    this->attributes = attributes;
    this->clearDependencies();
    this->addDependencies(temp, false);
}

/**
 * 
 * @param d Dependency on which the reduction of the lhs is to be performed.
 * @return true if the dependency lhs is reduced, otherwise false.
 * @details This method will use current dependency set of the relation to 
 * reduce the lhs attributes if possible.
 */
bool Relation::processLHS(const Dependency &d) {
    bool change;
    unsigned int size = d.lhs.size();
    set_str temp(d.lhs);
    do {
        //        std::cout << "Vector - " << temp << std::endl;
        vector<string> v(temp.begin(), temp.end());
        change = false;
        if (temp.size() > 1) {
            for (unsigned int i = 0; i < v.size(); ++i) {
                //                std::cout << "Trying to remove - " << v[i] << std::endl;
                //	      if (!(temp.size() > 1))
                //      break;
                itr_dep itrd = this->findDepLHS(temp);
                temp.erase(v[i]);
                set_str clr1 = getClosure(temp);
                if (!clr1.empty() && isSubset(clr1, itrd->rhs)) {
                    Dependency mod(temp, itrd->rhs);
                    this->removeDependency(*itrd);
                    this->addDependency(mod);
                    //                    std::cout << "Removed. Dependency LHS - " << itrd->lhs << std::endl;
                    change = true;
                    break;
                }
                temp.insert(v[i]);
            }
        }
    } while (change);

    return (size != d.lhs.size());
}

/**
 * @param details a boolean parameter with default value false. If true the steps
 * involved in the finding minimal cover will be printed on standard output stream cout.
 * @return Returns the set of dependency representing the minimal form of current 
 * functional dependencies of the relation object.
 * @details The method will use three different steps reduce lhs, reduce rhs and
 * reduce rules by using private methods of the relation to get the minimal cover.
 */
set_dep Relation::getMinimalCover(bool details) const {
    set_dep min;
    min = reduceRHS(this->dependencies);
    if (details)
        std::cout << std::setw(WIDTH) << std::right << "" << "Reduced RHS - " << min << std::endl;
    min = reduceLHS(min);
    if (details)
        std::cout << std::setw(WIDTH) << std::right << "" << "Reduced LHS - " << min << std::endl;
    min = reduceRules(min);
    if (details)
        std::cout << std::setw(WIDTH) << std::right << "" << "Reduced Rules - " << min << std::endl;
    Relation temp("a");
    temp.addDependencies(min);
    temp.reducedDependencies();

    return temp.dependencies;
}

/**
 * 
 * @param dep represents the set of dependencies which should be converted into 
 * reduced RHS form.
 * @return dependency set representing the reduced RHS for parameter dep.
 * @details The dependency will be in the reduced RHS form if the rhs conrains 
 * only one attribute.
 */
set_dep Relation::reduceRHS(const set_dep &dep) {
    set_dep ret;
    for (itr_dep i = dep.begin(); i != dep.end(); ++i) {
        if (i->rhs.size() > 1) {
            for_each(i->rhs.begin(), i->rhs.end(),
                    [&] (const string & str) {
                        ret.insert(Dependency(i->lhs, {
                            str
                        }));
                    });
        } else {

            ret.insert(*i);
        }
    }
    return ret;
}

/**
 * 
 * @param dep represents the set of dependencies which should be converted into 
 * reduced LHS form.
 * @return dependency set representing the reduced LHS form for parameter dep.
 * @details The dependency will be in the reduced LHS by identifying minimum set 
 * of LHS attribute which can preserve original dependency.
 */
set_dep Relation::reduceLHS(const set_dep &dep) {
    Relation temp("temp");
    temp.setDependencies(dep);
    for_each(dep.begin(), dep.end(),
            [&] (const Dependency & d) {
                if (d.lhs.size() > 1)
                    temp.processLHS(d);
            });

    return reduceRHS(temp.dependencies);
}

/**
 * 
 * @param dep represents the set of dependencies which should be converted into 
 * reduced rules form.
 * @return dependency set representing the reduced rules form for parameter dep.
 * @details The dependency will be in the reduced LHS by removing the dependency
 * if it can be preserved by the other dependency in the dependency set.
 */
set_dep Relation::reduceRules(const set_dep &dep) {
    Relation temp("temp");
    temp.addDependencies(dep);
    for (itr_dep i = dep.begin(); i != dep.end(); ++i) {
        temp.removeDependency(*i);
        //        std::cout << "Trying to remove " << *i << std::endl;
        //        std::cout << i->lhs << "* = " << s << std::endl;
        if (!(isSubset(temp.getClosure(i->lhs), i->rhs))) {

            temp.addDependency(*i);
        }
    }
    return temp.dependencies;
}

/**
 * 
 * @param lhs represents the attribute set to find out is supekey or not.
 * @return true if the parameter lhs is the superkey, false otherwise.
 * @details The lhs is considered as the superkey if it is superset of at least
 * one candidate key from candidate key set.
 */
bool Relation::isSuperkey(const set_str &lhs) const {

    return testSet(getCandidatekey(), lhs, true);
}

/**
 * 
 * @param lhs represents the attribute set which is to find out is partial key or not.
 * @return true if the parameter lhs is the partial, false otherwise.
 * @details The lhs is considered as the partial key if it is subset of at least
 * one candidate key from candidate key set.
 */
bool Relation::isPartialkey(const set_str& lhs) const {

    return testSet(getCandidatekey(), lhs) && !testSet(getCandidatekey(), lhs, true);
}

/**
 * 
 * @param str represents the attribute set which is to find out is prime or not.
 * @return true if the parameter str is the subset of prime attributes, false otherwise.
 * @details The attribute is considered as prime attribute if it belongs to any
 * one of the candidate key. If parameter is sub set of all the prime attribute
 * then true value is returned.
 */
bool Relation::isPrime(const set_str& str) const {
    set_key ck = getCandidatekey();
    for (itr_key i = ck.begin(); i != ck.end(); ++i) {
        if (isSubset(*i, str))

            return true;
    }
    return false;
}



/**
 * 
 * @return set of keys object containing all the possible candidate keys for the 
 * relation.
 * @details The method will calculate all the possible candidate key for the 
 * relation object using current functional dependencies and the attributes. The
 * single key can be considered as set of attributes which can derive all the 
 * attributes of the relation uisng the dependency set of the relation.
 */
set_key Relation::getCandidatekey(void) const {
    set_str ss = attributes;
    set_key working;
    for (itr_str j = ss.begin(); j != ss.end(); ++j) {
        for (itr_dep i = dependencies.begin(); i != dependencies.end(); ++i) {
            if (i->isPresentRhs(*j)) {
                ss.erase(*j);
            }
        }
    }
    ss = ss.empty() ? attributes : ss;
    for_each(ss.begin(), ss.end(), [&] (const string & s) {
        working.insert({s});
    });
    set_key keys;
    do {
        for_each(working.begin(), working.end(), [&] (const set_str & s) {
            if (isSubset(getClosure(s), attributes) && !testSet(keys, s, true)) {
                keys.insert(s);
            }
        });

        getNextIteration(working, attributes);
        working -= keys;
    } while (!working.empty());

    return keys;

}

/**
 * 
 * @param form is a Relation::Normal value represents the normal form for which 
 * the relation is to be tested.
 * @return true if the relation is in the normal form provided by the parameter,
 * false otherwise.
 * @details The method will use the functor object of Violation class to find the
 * any violation for the normal form for every dependency from dependency set. No
 * violation means the relation is in given normal form.
 */
bool Relation::isNormal(const Relation::Normal &form) const {
    Violation v(*this, form);
    itr_dep res = find_if(dependencies.begin(), dependencies.end(), v);

    return (res == dependencies.end());
}

/**
 * 
 * @param dep set of dependencies to be added into the relation.
 * @param update boolean parameter with default value false to indicate that
 * whether to add the attribute if dependency contains the attribute which is not
 * already present in the attribute set of the relation.
 * @details Foe every dependency object from the parameter dep, the method
 * Relation::addDependency will be called.
 */
unsigned int Relation::addDependencies(const set_dep&dep, bool update) {
    return count_if(dep.begin(), dep.end(), [&] (const Dependency & d) {
        return (addDependency(d, update) != this->dependencies.end());
    });
}

/**
 * @param right the rhs relation object for the comparison operation.
 * @return true if current relation object is logically lesser than the parameter
 * right, false otherwise.
 * @details The relation will use the attribute set size and dependency set size
 * to determine the logical lesser relation object. In case of equal attribute 
 * set and dependency set the name will be used to determine the result. In case
 * of equal attribute size and but the not equal attribute set, the 
 * setstr_compare::less function will be used to compare the attribute sets.
 * In case of the equal dependency set size but not equal dependency set, the
 * overloaded Dependency::operator < will be used to determine the lesser 
 * dependency set between two relation objects.
 */
bool Relation::operator<(const Relation& right) const {
    if (*this != right) {
        if (this->attributes.size() < right.attributes.size())
            return true;
        if (isEqual(this->attributes, right.attributes)) {
            if (this->dependencies.size() < right.dependencies.size())
                return true;
            if (isEqual(this->dependencies, right.dependencies))
                return this->name < right.name;
            return this->dependencies < right.dependencies;
        }
        if (setstr_compare::less(this->attributes, right.attributes)) {

            return true;
        }
        return this->name < right.name;
    }

    return false;
}

/**
 * 
 * @param right the rhs relation object for the comparison operation.
 * @return true if both relation are equla, false otherwise.
 * @details The relation objects will be considered equal if the name of both 
 * relation is equal and the attribute set & dependency set are equal.
 */
bool Relation::operator==(const Relation& right) const {

    return (this == &right
            || (this->name == right.name
            && isEqual(this->dependencies, right.dependencies)
            && isEqual(this->attributes, right.attributes)));
}

/**
 * 
 * @param right the rhs relation object for the comparison operation.
 * @return true if current relation object is logically lesser than the parameter
 * right, false otherwise.
 * @details This method reuses the Relation::operator <.
 */
bool Relation::operator>(const Relation& right) const {

    return right < *this;
}

/**
 * 
 * @param right the rhs relation object for the comparison operation.
 * @return true if current relation object is not equal to the parameter
 * right, false otherwise.
 * @details This method reuses the Relation::operator !=.
 */
bool Relation::operator!=(const Relation& right) const {
    bool result = !(*this == right); // Reuse equals operator

    return result;
}

/**
 * 
 * @param right the rhs relation object for the comparison operation.
 * @return true if current relation object is logically lesser than or equal to
 * the parameter right, false otherwise.
 * @details This method reuses the Relation::operator < and Relation::operator =.
 */
bool Relation::operator<=(const Relation& right) const {

    return !(*this > right); // Reuse greater than operator
}

/**
 * 
 * @param right the rhs relation object for the comparison operation.
 * @return true if current relation object is logically greater than or equal to
 * the parameter right, false otherwise.
 * @details This method reuses the Relation::operator > and Relation::operator =.
 */
bool Relation::operator>=(const Relation& right) const {
    return !(right > * this); // Reuse greater than operator
}
