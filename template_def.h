/*! \file template_def.h
    \brief Contains the definition for various utility template functions.
  
    \details
    Definition of different template method declared in the utility.h file. This 
    file is to be included in the utility.h file.
  
    \author Ashish D. Kharde
 */
#ifndef TEMPLATE_DEF_H
#define TEMPLATE_DEF_H

#include "declaration.h"
#include "relation.h"

/**
 * 
 * @param list Represents the set of any data-type.
 * @param val Represents the value that need to be search from the parameter set
 * object.
 * @return true if the val parameter is found in the set parameter list, 
 * false otherwise.
 */
template <typename T>
inline bool contains(const set<T>& list, const T& val) {
    return (list.find(val) != list.end());
}

/**
 * @param lhs is the set object that represents first parameter.
 * @param rhs is the set object that represents second parameter
 * @return true if both sets are equal, false otherwise.
 * @details The function uses the subset method to determine the equality of the 
 * two parameter set objects. If lhs is subset of the rhs and rhs is subset of the
 * lhs means both sets are equal.
 */
template <typename T>
inline bool isEqual(const set<T>& lhs, const set<T>& rhs) {
    return (lhs.size() == rhs.size())
            && (isSubset(lhs, rhs)
            && isSubset(rhs, lhs));
}

/**
 * 
 * @param lhs is the first parameter represents the set object from which second 
 * parameter is to be look up.
 * @param rhs is the second parameter represents the set object which is to be
 * tested as subset of the first parameter.
 * @return true if the rhs is subset of the lhs, false otherwise.
 * @details The function checks whether every objects from the parameter rhs is 
 * present in the parameter lhs.
 */
template <typename T>
inline bool isSubset(const set<T>& lhs, const set<T>& rhs) {
    return includes(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/**
 * 
 * @param out is the output stream object where the set data is to be inserted.
 * @param dispSet is the set objects of any data type T.
 * @param par is the enumeration object of Parenthesis representing the type of 
 * parenthesis to be used when formating the set objects in output stream. Default
 * value is NO_BRAC in which case no parenthesis will be used to separate set 
 * objects.
 * @return The reference of the out parameter.
 * @details This function will insert all the set objects to output stream 
 * separated by the parenthesis if necessary. The output operator << should be overloaded for the
 * datatype of the object to insert its content in the output stream.
 */

template <typename T>
ostream& printSet(ostream &out, const set<T> &pSet, const Parenthesis &par) {

    if (!pSet.empty()) {
        for (auto i = pSet.begin(); i != pSet.end();) {
            out << getBrac(par, false) << *i << getBrac(par, true);
            if (++i != pSet.end())
                out << ", ";
        }
    } else {
        out << getBrac(par, false) << " 0 " << getBrac(par, true);
    }
    return out;
}


#endif /* TEMPLATE_DEF_H */

