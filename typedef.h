/*! \file typedef.h
    \brief Defines the global type alias for data-types.
    
    \details 
    Declaration of global type alias and the forward declaration of the classes.
  
    \author Ashish D. Kharde
 */

#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <set>
using std::set;

#include <string>
using std::string;

/*! 
    Forward declaration of class \link Relation \endlink
 */
class Relation;

/*! 
    Forward declaration of class \link Dependency \endlink
 */
class Dependency;

/*! 
    Forward declaration of struct \link Violation \endlink
 */
struct Violation;

/*! 
    Forward declaration of class UserInterface
 */
class Dependency;

//Used in NetBeans only.
typedef std::string string;

/*! \var typedef set<Relation> set_rel
    \brief A type definition for a set of Relation.
 */
typedef set<Relation> set_rel;

/*! \var typedef set<Dependency> set_dep
    \brief A type definition for a set of Dependency.
 */
typedef set<Dependency> set_dep;

/*! \var typedef set<string> set_str
    \brief A type definition for a set of strings.
 */
typedef set<string> set_str;

/*! \var typedef set_rel::iterator itr_rel
    \brief A type definition for a iterator of set of Relation.
 */
typedef set_rel::iterator itr_rel;

/*! \var typedef set_dep::iterator itr_dep
    \brief A type definition for a iterator of set of Dependency.
 */
typedef set_dep::iterator itr_dep;

/*! \var typedef set_str::iterator itr_str
    \brief A type definition for a iterator of set of string.
 */
typedef set_str::iterator itr_str;

/*! \var const unsigned short int WIDTH
    \brief A global constant variable to specify the value of width used in 
    formatting the stream output.
 */
const unsigned short int WIDTH = 12;

#endif /* TYPEDEF_H */

