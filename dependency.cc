/*! \file dependency.cc
 * 
 * \brief Includes definitions of the Dependency class members defined in the 
 * dependency.h file
 *  
 * \details
 * This file contains definition of the undefined member functions of the class
 * Dependency.
 * 
 */
#include "dependency.h"
#include "utility.h"
#include <iostream>
#include <algorithm>

/**
 * 
 * @param lhs parameter is set_str object represents the left-hand side of the 
 * dependency.
 * @param rhs parameter is set_str object represents the right-hand side of the 
 * dependency.
 * @details The constructor initializes the lhs and rhs data members of the class.
 */
Dependency::Dependency(const set_str &lhs, const set_str &rhs) :
lhs(lhs), rhs(rhs) {
}

/**
 * 
 * @param orig is the Dependency object which to be copied to the newly 
 * constructed object
 * @details The copy constructor initializes the lhs and rhs data members of the 
 * class from the corresponding data members of the parameter object.
 */
Dependency::Dependency(const Dependency& orig) :
lhs(orig.lhs), rhs(orig.rhs) {
}

/**
 * 
 * @details The destructor clears the string objects from the both lhs and rhs 
 * data member attributes sets.
 */
Dependency::~Dependency() {
    lhs.clear();
    rhs.clear();
}

/**
 * 
 * @param str the constant string reference object to represent the attribute to add.
 * @return true if the new string is inserted in the lhs set, false otherwise -
 * meaning that the attribute is already present in the lhs set.
 * @details The string will be added to the lhs data member of the class.
 */
bool Dependency::addLhs(const string& str) {
    return lhs.insert(str).second;
}

/**
 * 
 * @param str the constant string reference object to represent the attribute to add.
 * @return true if the new string is inserted in the rhs set, false otherwise -
 * meaning that the attribute is already present in the rhs set.
 * @details The string will be added to the rhs data member of the class.
 */
bool Dependency::addRhs(const string& str) {
    return rhs.insert(str).second;
}

/**
 * 
 * @param str the constant string reference object to represent the attribute to remove.
 * @return true if the attribute string is removed from the lhs set, false otherwise -
 * meaning that the attribute string is not present in the lhs set.
 * @details The string will be removed from the lhs data member, if it is present in the 
 * lhs.
 */

bool Dependency::removeLhs(const string& str) {
    return lhs.erase(str) != 0;
}

/**
 * 
 * @param str the constant string reference object to represent the attribute to remove.
 * @return true if the attribute string is removed from the rhs set, false otherwise -
 * meaning that the attribute string is not present in the rhs set.
 * @details The string will be removed from the rhs data member, if it is present in the 
 * rhs.
 */
bool Dependency::removeRhs(const string& str) {
    return rhs.erase(str) != 0;
}

/**
 * 
 * @param str parameter represents the attribute string to search from the lhs
 * @return true if the attribute string is present in the lhs, false otherwise.
 */
bool Dependency::isPresentLhs(const string& str) const {
    return (contains(lhs, str));
}

/**
 * 
 * @param str parameter represents the attribute string to search from the rhs
 * @return true if the attribute string is present in the rhs, false otherwise.
 */
bool Dependency::isPresentRhs(const string& str) const {
    return (contains(rhs, str));
}

/**
 * 
 * @param str parameter represents the attribute string to search from either in 
 * the lhs or in the rhs.
 * @return true if the attribute string is present either in lhs or in rhs, false 
 * otherwise.
 */
bool Dependency::isPresent(const string& str) const {
    return contains(lhs, str) || contains(rhs, str);
}

/**
 * 
 * @return the unsigned integer representing the combined size of the attributes 
 * from the lhs and rhs set.
 */
unsigned int Dependency::size(void) const {
    return (lhs.size() + rhs.size());
}

/**
 * 
 * @param right parameter represents the the rhs dependency object in the inequality
 * check.
 * @return true if both objects are not equal, false otherwise.
 * @details Reuses the equal operator to determine the result.
 */
bool Dependency::operator!=(const Dependency& right) const {
    return !(*this == right); // Reuse equals operator
}

/**
 * 
 * @param right parameter to represent the rhs dependency object to test less inequality.
 * @return true if the lhs dependency object is logical lesser than right dependency 
 * object, false otherwise.
 * @details The overloaded operator will test the lhs set size first to determine the 
 * result. If the both objects have same size of the lhs set then it will check whether 
 * both lhs sets are equla or not. If they are not equal then the static setstr_compare::less
 * function is used to determine the 'less' equality of the lhs set of both objects. In case
 * of the equal lhs set, the same operation will be performed with rhs set of the both
 * parameter objects.
 * 
 */
bool Dependency::operator<(const Dependency& right) const {
    bool val;
    if (this->lhs.size() < right.lhs.size()
            || (!isEqual(this->lhs, right.lhs) && setstr_compare::less(this->lhs, right.lhs))
            || (!setstr_compare::less(right.lhs, this->lhs)
            && setstr_compare::less(this->rhs, right.rhs)))
        val = true;
    else val = false;
    return val;
}

/**
 * 
 * @param right parameter to represent the rhs dependency object to test equality.
 * @return true if the both dependency objects are equal, false otherwise.
 * @details Dependencies will be equal if their data members i.e. lhs attribute set 
 * and rhs attribute set are identical to each other.
 */
bool Dependency::operator==(const Dependency& right) const {
    return isEqual(this->lhs, right.lhs) && isEqual(this->rhs, right.rhs);
}

/**
 * 
 * @param right parameter to represent the rhs dependency object to test greater inequality.
 * @return true if the lhs dependency object is logical greater than right dependency 
 * object, false otherwise.
 * @details It reuses the less operator to determine the result.
 */
bool Dependency::operator>(const Dependency& right) const {
    return right < *this;
}

/**
 * 
 * @param right The rhs dependency object parameter from which attributes are to 
 * be added to the lhs dependency object parameter.
 * @return The reference of the lhs dependency object parameter.
 * @details It adds all the of attributes from the rhs attribute set of the right 
 * parameter if the lhs attribute set of both of the dependency object is equal.
 */
Dependency& Dependency::operator+=(const Dependency& right) {
    if (&right != this && isEqual(this->lhs, right.lhs)) {
        this->rhs.insert(right.rhs.begin(), right.rhs.end());
    }
    return *this;
}

/**
 * 
 * @return A set of all unique attributes presents in both lhs attribute set and 
 * rhs attribute set of the current Dependency object.
 */
set_str Dependency::getAttribs() const {
    set_str ret;
    ret.insert(lhs.begin(), lhs.end());
    ret.insert(rhs.begin(), rhs.end());
    return ret;
}
