
/*! \file utility.h
    \brief Defines the prototypes for the global non-member functions.
  
    \details
    Declaration of the prototypes for the global non-member functions, 
    overloaded operators and template functions. Also includes the file 
    template_def.h which includes the definition of the template functions.
  
    \author Ashish D. Kharde
 */
#ifndef UTILITY_H
#define UTILITY_H

#include "declaration.h"

#include <algorithm>
#include <iostream>
using std::istream;
using std::ostream;

#include <set>
using std::set;

/*! \enum Parenthesis
 *  The global enumerator used for representing the types of the brackets used 
 *  while producing the output for different sets. 
 */
enum Parenthesis {
    BRAC_ROUND, /*!< Represents round brackets */
    BRAC_SQUARE, /*!< Represents square/box brackets */
    BRAC_CURLY, /*!< Represents curly brackets */
    BRAC_ANGEL, /*!< Represents angel brackets */
    NO_BRAC /*!< Represents no brackets */
};

/**
 * @brief Insert Dependency object into stream
 */
ostream& operator<<(ostream &, const Dependency &);

/**
 * @brief Insert Relation object into stream.
 */
ostream& operator<<(ostream &, const Relation &);

/**
 * @brief Insert set_key object into stream.
 */
ostream& operator<<(ostream &, const set_key &);

/**
 * @brief Insert set_rel objects into stream.
 */
ostream& operator<<(ostream &, const set_rel &);

/**
 * @brief Insert set_str objects into stream.
 */
ostream& operator<<(ostream &, const set_str &);

/**
 * @brief Insert set_dep objects into stream.
 */
ostream& operator<<(ostream &, const set_dep &);


/**
 * @brief Subtract and assign the set_key objects
 */
set_key& operator-=(set_key &, const set_key &);

/**
 * @brief Subtract and assign the  set_str objects
 */
set_str& operator-=(set_str &, const set_str &);

/**
 * @brief Checks whether the set_str object is superset or subset for any set_str 
 * object of the set_key
 */
bool testSet(const set_key& lhs, const set_str& rhs, bool super = false);


/**
 * @brief Retrieves the string representing the corresponding parenthesis. 
 * @param sap a constant Parenthesis enumeration object value to represent the 
 * type of braces.
 * @param close a boolean parameter to determine the closing or opening brace.
 * The true value indicates the closing brace and false value indicates the 
 * opening brace.
 * @return The string representing the equivalent value of the parenthesis. 
 * The default value will be the empty string.
 */
inline string getBrac(const Parenthesis &sap, bool close) {
    switch (sap) {
        case BRAC_ROUND:
            return close ? ")" : "(";
        case BRAC_SQUARE:
            return close ? "]" : "[";
        case BRAC_CURLY:
            return close ? "}" : "{";
        case BRAC_ANGEL:
            return close ? ">" : "<";
        default: return "";
    }
}

/**
 * @brief Checks whether the set_str object is present in the set_key.
 * @param list A constant set of string sets to check from.
 * @param val A constant string set representing the search value.
 * @return true for successful find false otherwise.
 * @details A alternate version of the template function contains for set of string set with
 * different comparator i.e. setstr_compare.
 * 
 */
inline bool contains(const set_key& list, const set_str& val) {
    return (list.find(val) != list.end());
}



/*********Template Functions*********/

/**
 * @brief Template function to insert the set of any type in the output stream 
 * using specified parenthesis.
 */
template <typename T >
ostream & printSet(ostream &, const set<T> &, const Parenthesis &sap = NO_BRAC);

/**
 * @brief Template function to check the equality of two sets of any datatype.
 */
template <typename T>
inline bool isEqual(const set<T>& lhs, const set<T>& rhs);

/**
 * @brief Template function to check whether the second parameter is subset of first
 * of any datatype.
 */
template <typename T>
inline bool isSubset(const set<T>& lhs, const set<T>& rhs);

/**
 * @brief Template function to check whether the second parameter value is present in 
 * the set object represented by the first parameter.
 */
template <typename T>
inline bool contains(const set<T>& lhs, const T & val);



#include "template_def.h"


#endif /* UTILITY_H */

