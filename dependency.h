/*! @file dependency.h
 * 
 * @brief Includes declaration for the class Dependency and its members.
 *  
 * @details
 * This file declares the definition of the class Dependency along with its 
 * subsequent data members and the member functions prototype.
 * 
 */
#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include "declaration.h"
#include "utility.h"

#include <set>
using std::set;

#include <iostream>
using std::istream;
using std::ostream;

/*!
 * \class  Dependency
 * \brief The Dependency class that represents the functional dependency of the 
 * relation using the attribute set.
 * \details The Dependency class contains the data member that represents the 
 * left-hand side and right-hand of the functional dependency. Both lhs and rhs
 * are considered as the set of attributes. Attributes will be represented by the 
 * string representing its name. Note that this class have private constructor which
 * restricts the creation of its object other than its friend member functions and 
 * class. The object of this class can be constructed in the Relation class methods.
 * This is to ensure the fact that dependency belongs to a particular relation and 
 * to identify that unique relation.
 */
class Dependency {
    friend class Relation;
    friend class dependency_test;
    friend class relation_test;

    friend ostream& operator<<(ostream &, const Dependency &);

public:
    /**
     * @breif Destructor of the Dependency class.
     */
    ~Dependency();

    /**
     * @breif The copy constructor of the Dependency class.
     */
    Dependency(const Dependency& orig);

    /**
     * @breif The overloaded less operator for testing inequality the dependency 
     * objects.
     */
    bool operator<(const Dependency&) const;

    /**
     * @breif The getter method for retrieve the left-hand side attribute set.
     */
    set_str getLhs() const {
        return lhs;
    }

    /**
     * @breif The getter method for retrieve the right-hand side attribute set.
     */
    set_str getRhs() const {
        return rhs;
    }

    /**
     * @breif The getter method for retrieve the all the attribute from dependency.
     */
    set_str getAttribs() const;

private:

    set_str lhs; /*!< The string of set or set_str object that reprensents the 
                  * left-hand side of the functional dependency*/
    set_str rhs; /*!< The string of set or set_str object that reprensents the 
                  * right-hand side of the functional dependency*/

    /**
     * @breif The overloaded relational operator != to check inequality between 
     * the two Dependency objects.
     */
    bool operator!=(const Dependency&) const;
    /**
     * @breif The overloaded relational operator ==to check equality between 
     * the two Dependency objects.
     */
    bool operator==(const Dependency&) const;
    /**
     * @breif The overloaded relational operator > to check inequality between 
     * the two Dependency objects.
     */
    bool operator>(const Dependency&) const;
    /**
     * @breif The overloaded operator += to combine the rhs of the two dependency 
     * object if possible.
     */
    Dependency& operator+=(const Dependency&);

    /**
     * @breif Constructor for the Dependency class initializing the data members.
     */
    Dependency(const set_str &lhs, const set_str &rhs);

    /**
     * @breif A member function to add an attribute string to the lhs set.
     */
    bool addLhs(const string &);
    /**
     * @breif A member function to add an attribute string to the rhs set.
     */
    bool addRhs(const string &);
    /**
     * @breif A member function to remove an attribute string from the lhs set.
     */
    bool removeLhs(const string &);
    /**
     * @breif A member function to remove an attribute string from the rhs set.
     */
    bool removeRhs(const string &);

    /**
     * @breif A member function to check is an attribute string is present in lhs set.
     */
    bool isPresentLhs(const string&) const;
    /**
     * @breif A member function to check is an attribute string is present in rhs set.
     */
    bool isPresentRhs(const string&) const;
    /**
     * @breif A member function to check is an attribute string is present in 
     * either lhs set or rhs set.
     */
    bool isPresent(const string&) const;

    /**
     * @breif A member function to calculate total number of attributes present 
     * in the lhs set and rhs set.
     */
    unsigned int size(void) const;

    /**
     * @breif The setter method to reinitialize the left-hand side attribute set.
     */
    void setLhs(const set_str &lhs) {
        this->lhs = lhs;
    }

    /**
     * @breif The setter method to reinitialize the right-hand side attribute set.
     */
    void setRhs(const set_str &rhs) {
        this->rhs = rhs;
    }

    /**
     * @breif The method to clear left-hand side attribute set.
     */
    void clearLhs(void) {
        this->lhs.clear();
    }

    /**
     * @breif The method to clear right-hand side attribute set.
     */
    void clearRhs(void) {
        this->rhs.clear();
    }

    /**
     * @breif The method to clear both lhs and rhs attribute set.
     */
    void clear(void) {
        clearLhs();
        clearRhs();
    }
};

#endif /* DEPENDENCY_H */