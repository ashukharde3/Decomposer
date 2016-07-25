/*! \file utility.cc
    \brief Specifies the definitions for the global non-member functions defined 
    in utility.h header file.
  
    \details
    Definition of the all the non-member and non-template global functions defined
    in the header file utility.h
  
    \author Ashish D. Kharde
 */

#include "utility.h"
#include "dependency.h"
#include "relation.h"
#include <iomanip>

/**
 * @param ostream object where set_key objects are inserted.
 * @param set_key object to insert.
 * @return The same parameter of ostream.
 * @details Inserts the all the set_str objects from the dispSet parameter into the stream 
 * with proper formatting, separating each set_str objects within the parenthesis 
 * and putting all the sets in the curly braces. The empty set_key object is 
 * indicated by { 0 }.
 */

ostream& operator<<(ostream &out, const set_key &dispSet) {
    out << "{ ";
    if (dispSet.empty()) {
        out << " 0 ";
    } else {
        for (itr_key i = dispSet.begin(); i != dispSet.end();) {
            out << "( " << *i << " )";
            if (++i != dispSet.end())
                out << ", ";
        }
    }
    out << " }";
    return out;
}

/* 
 * @param ostream object where set_rel objects are inserted.
 * @param set_rel object to insert.
 * @return The same parameter of ostream.
 * @details Inserts all the Relation objects from the dispSet parameter into the stream
 * with proper formatting. Puts each Relation object in separate line and also 
 * lists the candidate key for each relation. The empty set_rel object is 
 * indicated by { 0 }.
 */
ostream& operator<<(ostream &out, const set_rel &dispSet) {
    if (!dispSet.empty()) {
        unsigned int count = 0;
        for (itr_rel i = dispSet.begin(); i != dispSet.end(); ++i) {
            out << *i << std::endl << std::setw(WIDTH) << std::right << ""
                    << "Candidate Keys: " << i->getCandidatekey()
                    << std::endl << std::setw(WIDTH) << std::right << "";
            if (++count < dispSet.size())
                out << std::endl << std::setw(WIDTH) << std::right << "";
        }
    } else {
        out << "{ 0 }" << std::endl << std::setw(WIDTH) << std::right << "";
    }
    return out;
}

/*
 * @param ostream object where set_dep objects are inserted.
 * @param set_dep object to insert.
 * @return The same parameter of ostream.
 * @details Inserts all the Dependency objects from the dispSet parameter into the stream
 * with proper formatting. Puts all Dependency objects in  the curly braces. The
 * empty set_dep object is indicated by { 0 }. Uses the template method printSet
 * with square braces to list out the Dependency set objects.
 */
ostream& operator<<(ostream &out, const set_dep & dispSet) {
    out << "{ ";
    printSet(out, dispSet, Parenthesis::BRAC_SQUARE) << "}";
    return out;
}

/*
 * @param ostream object where set_str objects are inserted.
 * @param set_str object to insert.
 * @return The same parameter of ostream.
 * @details Inserts all the strings from the dispSet parameter into the stream with proper 
 * formatting. All strings in the set will be separated by ',' and empty set_str
 * object is indicated by { 0 }. Uses the template method printSet with no braces
 * to list out the string.
 */
ostream& operator<<(ostream &out, const set_str & dispSet) {
    return printSet(out, dispSet, Parenthesis::NO_BRAC);
}


/*
 * @param ostream object where Dependency data is inserted.
 * @param Dependency object to insert.
 * @return The same parameter of ostream. 
 * @details Inserts the Dependency d into the stream. The dependency object will be inserted 
 * in format lhs -> rhs. The attributes in the lhs and rhs will be separated by the
 * ','. 
 */
ostream& operator<<(ostream &out, const Dependency & d) {
    out << d.lhs << " -> " << d.rhs;
    return out;
}

/*
 * @param ostream object where Relation data are inserted.
 * @param Relation object to insert.
 * @return The same parameter of ostream.
 * @details Inserts the Relation rel into the stream. The relation name will be inserted 
 * first. Followed by the arguments if the argument set is not empty. Then the 
 * dependency set, if it is not empty.
 */
ostream& operator<<(ostream &out, const Relation & rel) {
    out << rel.name;
    rel.attributes.empty() ? out << "" : out << "(" << rel.attributes << ")";
    rel.dependencies.empty() ? out << "" :
            (out << std::endl << std::setw(WIDTH) << std::right << ""
            << "Functional Dependencies - "
            << rel.dependencies);
    return out;
}

/* 
 * @param lhs The set_key object from which the set_str objects to be removed.
 * @param rhs The set_key object from which the set_str objects are to be excluded
 * from lhs.
 * @return The modified parameter lhs
 * @details Checks if lhs set contains the string from rhs set. If lhs set contains the 
 * string from rhs, it will be then removed from lhs set.
 */
set_key& operator-=(set_key &lhs, const set_key & rhs) {

    for (const set_str &s : rhs) {
        if (contains(lhs, s))
            lhs.erase(s);
    }
    return lhs;
}

/*
 * @param The set_str object from which the strings to be removed.
 * @param The set_str object from which the strings are to be excluded from lhs.
 * @return The modified parameter lhs
 * @details Checks if lhs set contains the set_str from rhs set. If lhs set contains the 
 * set_str from rhs, it will be then removed from lhs set.
 */
set_str& operator-=(set_str &lhs, const set_str & rhs) {
    for (const string & s : rhs) {
        if (contains(lhs, s))
            lhs.erase(s);
    }
    return lhs;
}
/**
 * 
 * @param lhs The set_key 
 * @param rhs
 * @param super To determine the type of check either superset true or the subset
 * false. Default value is false for subset.
 * @return true if the second parameter is subset or superset of the any of first 
 * parameter object, false otherwise.
 * @details It checks whether the rhs set_str object is the super set or the subset 
 * of the any of set_str object. If it is subset or superset then the it return the
 * true value. The check for either superset or the subset will be determined by 
 * the parameter super.
 */
bool testSet(const set_key& lhs, const set_str& rhs, bool super) {
    return (lhs.end() != find_if(lhs.begin(), lhs.end(),
            [&](const set_str & val) {
                return ((!super && isSubset(val, rhs))
                        || (super && isSubset(rhs, val)));
            }));
}

