/*! \file violation.h
 * 
 *  \brief Includes declaration of functor class Violation used to check violation 
 *  of any normal form by the Dependency for a Relation object.
 *  
 *  \details
 *  This file includes the declaration and definition of class Violation and 
 *  its subsequent methods.
 * 
 *  \author Ashish D. Kharde
 * 
 */
#ifndef FUNCTOR_H
#define FUNCTOR_H

#include "declaration.h"
#include "dependency.h"
#include "relation.h"

/*!
  \struct Violation
  \brief A unary functor class used to test the dependency for the normal form violation
  \details The class Violation inherits the unary_function to define the unary predicate 
  with Dependency as parameter object. It uses the data members with constant reference 
  to the Relation and the constant reference to enumeration value of Noraml to 
  represent the normal form. Note that the it have private constructor to restrict 
  the use of this class limited to only friend class Relation.  
*/
struct Violation : public std::unary_function<Dependency, bool> {
    friend class Relation;  /*!< only Relation calss have access to construct the 
                             * object of the Violation struct and to use it.*/
private:
    const Relation &ref; /*!< A constant relation object reference for which the 
                          * violataion are to be determined. */
    const Relation::Normal &form; /*!< A constant normal form reference for which 
                                   * the dependency is to be tested.

  /**
   * @breif Initialize the Violation object with the Relation and Normal Form 
   * values.
   * @param ref is Relation object which is going to refer by the Violation to 
   * determine dependency violations.
   * @param form is a Normal enumarator value representing the Normal form to 
   * test.
   */
    Violation(const Relation& ref, const Relation::Normal& form) :
    ref(ref), form(form) {
    }

    /// Prevents the use of the copy operator.
    Violation& operator=(const Violation&);

public:

    /*!
     * @breif overloaded operator () to be applied as predicate when testing the 
     * dependency for the violation.
     * @param dep is constant reference to the Dependency object for which the 
     * violation is to be tested.
     * @return true value if it violates the normal form, false otherwise.
     * @details The function uses the class member Relation and Normal form 
     * objects to perform the test against the Dependency object parameter. 
     * If the conditions for the particular normal form is violated then the 
     * function return true. The different conditions for the normal form 
     * violation can be given as follows - 
     * - Second normal form violation if
     *      -# lhs of Dependency is partial key
     *      -# and rhs is not prime attribute set
     * - Third normal form violation if
     *      -# lhs of Dependency is not super-key
     *      -# and rhs is not prime attribute set
     * - Boyce-Codd(BC) normal form violation if
     *      -# lhs of Dependency is not super-key
     */

    bool operator()(const Dependency &dep) const {
        switch (form) {
            case Relation::_2NF:
                return (ref.isPartialkey(dep.getLhs()) && !ref.isPrime(dep.getRhs()));
            case Relation::_3NF:
                return (!ref.isSuperkey(dep.getLhs()) && !ref.isPrime(dep.getRhs()));
            case Relation::_BCNF:
                return !(ref.isSuperkey(dep.getLhs()));
            default:
                return false;
        }
    }
};

#endif /* FUNCTOR_H */

