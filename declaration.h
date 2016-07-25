/*! \file declaration.h
 * 
 *  \brief Includes declaration of classes and definition of comparator class
 *  
 *  \details
 *  This includes the forward declaration of classes from the file typedef.h.
 *  It declares the comparator class for set of set of string. It also
 *  declares the global type alias for set of the set of string.
 * 
 *  \author Ashish D. Kharde
 * 
 */
#ifndef DECLARATION_H
#define DECLARATION_H

#include "typedef.h"

/*! \class setstr_compare
 *  \brief The function object class for less-than inequality comparison
 *  of the set of string. 
 */
class setstr_compare {
public:

    /**
     * @breif Performs the less comparison between set_str objects.
     * @param lhs Argument to left hand side of the operation. 
     * @param rhs Argument to right hand side of the operation
     * @return true if the lhs object is less than rhs, and false otherwise
     */
    static bool less(const set_str &lhs, const set_str &rhs);

    /**
     * 
     * @breif The overloaded operator () to use the function object as a predicate.
     * @param lhs Argument to left hand side of the operation. 
     * @param rhs Argument to right hand side of the operation. 
     * @return The result from member function less - true if the lhs object is 
     * less than rhs, and false otherwise
     * @details The function object operator () for returning whether the first 
     * argument compares less than second. Uses the static member function 
     * setstr_compare::less to determine the result.
     */
    bool operator()(const set_str &lhs, const set_str &rhs) const;
};

/*! \var typedef set<set_str, setstr_compare> set_key
    \brief A type definition for a set of set of string with set_str with the 
    custom compare class setstr_compare.
 */
typedef set<set_str, setstr_compare> set_key;

/*! \var typedef set_key::iterator itr_key
    \brief A type definition for a iterator for set_key.
 */
typedef set_key::iterator itr_key;

#endif /* DECLARATION_H */