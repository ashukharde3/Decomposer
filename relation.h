/*! \file relation.h
 * 
 * \brief Includes declaration for the class Relation and its members.
 *  
 * \details
 * This file declares the definition of the class Relation along with its 
 * subsequent data members and the member functions prototype.
 * 
 * \author Ashish D. Kharde
 * 
 */
#ifndef RELATION_H
#define RELATION_H

#include "declaration.h"
#include "dependency.h"

#include <set>
using std::set;

#include <string>
using std::string;

/*!
 * \class Relation
 * \brief The Relation class that represents the relation entity.
 * \details The Relation class contains the data member that represents the 
 * name of the Relation, the attribute set of the relation and a set of the 
 * functional dependency. The relation name will be represented by the string 
 * data member name. The attribute set will be represented by data member 
 * attributes - an object of set of string (set_str). The functional dependency
 * set will represented by the data member dependencies - an object of set of 
 * Dependency objects (set_dep). The class also contains a enumeration data type
 * Normal to identify the different normal form. It provides variety of the 
 * public method interface to modify the relation object and perform different 
 * operation on it. The class provides private read only access to the overloaded 
 * output operator << for the output of the Relation object in the output stream.
 * 
 */
class Relation {
    friend ostream& operator<<(ostream &, const Relation &);
    friend class relation_test;
    friend class relation_test;
public:

    /*!
     * \enum Normal
     * \breif The enumeration to identify different normal form.
     */
    enum Normal {
        _2NF, /*!< Represnts the Second Normal form*/
        _3NF, /*!< Represnts the Thirde Normal form*/
        _BCNF /*!< Represnts the Boyce-Codd Normal form*/
    };


    /*!
     * @breif The parameterized Relation constructor with default values for 
     * attribute set and dependencies set.
     */
    Relation(const string &, const set_str &temp = *(new set_str()),
            const set_dep &t2 = *(new set_dep()));
    /*!
     * @breif The copy constructor for the Relation class.
     */
    Relation(const Relation& orig);

    /*!
     * @breif The destructor for the Relation class.
     */
    virtual ~Relation();

    /*!
     * @breif A method to add a single attribute to the attribute set.
     */
    bool addAtributte(const string &);

    /*!
     * @breif A method to add multiple attributes to the attribute set.
     */
    unsigned int addAtributtes(const set_str &);

    /*!
     * @breif A method to remove a single attribute from the attribute set.
     */
    bool removeAtributte(const string &);

    /*!
     * @breif A method to remove a single dependency from the dependency set
     * by providing separate set_str to represent the custom lhs and rhs of the
     * dependency.
     */
    bool removeDependency(const set_str &, const set_str &);

    /*!
     * @breif A method to remove a single dependency from the dependency set
     * by providing constant reference to the dependency object.
     */
    bool removeDependency(const Dependency &);

    /*!
     * @breif A method to add multiple attributes to the attribute set.
     */
    unsigned int addDependencies(const set_dep&, bool update = true);

    /*!
     * @breif A method to add a single dependency with explicitly specified lhs 
     * and rhs to the dependency set.
     */
    itr_dep addDependency(const set_str &, const set_str &, bool update = true);

    /*!
     * @breif Find dependency by specifying the lhs.
     */
    itr_dep findDepLHS(const set_str &) const;

    /*!
     * @breif A method to test normal form of the current Relation object.
     */
    bool isNormal(const Relation::Normal&) const;

    /*!
     * @breif A method to check if all the attributes of the parameter dependency 
     * present in the attribute set of the relation object.
     */
    bool isDepAttribPresent(const Dependency &)const;

    /*!
     * @breif A method to test if the given string set is the super-key to the 
     * relation.
     */
    bool isSuperkey(const set_str &)const;

    /*!
     * @breif A method to test if the given string set is the partial-key to the 
     * relation.
     */
    bool isPartialkey(const set_str&)const;

    /*!
     * @breif A method to test if the given string set is belong to the prime 
     * attribute set of the relation.
     */
    bool isPrime(const set_str &)const;

    /*!
     * @breif A method to get the closure of the given attribute set using 
     * functional dependency set of the Relation.
     */
    set_str getClosure(const set_str &) const;

    /*!
     * @breif A method to get all the candidate key set for the relation.
     */
    set_key getCandidatekey(void) const;

    /*!
     * @breif A method to get dependency set that violates given normal form 
     * conditions.
     */
    set_dep getViolation(const Relation::Normal &) const;

    /*!
     * @breif A method to get the minimal cover dependency set for the all 
     * dependencies that belongs to the relation.
     */
    set_dep getMinimalCover(bool details = false) const;

    /*!
     * @breif A method to get the sub-relation set for the given relation object 
     * by using FD preserving algorithm.
     */
    set_rel decomposePreserving(bool details = false) const;

    /*!
     * @breif A method to get the sub-relation set for the given relation object 
     * by using non FD preserving algorithm.
     */
    set_rel decomposeNotPreserving(bool details = false)const;

    /*!
     * @breif A overloaded relational operator to check inequality between two 
     * relation objects.
     */
    bool operator!=(const Relation& right) const;

    /*!
     * @breif A overloaded relational operator to check equality between two 
     * relation objects.
     */
    bool operator==(const Relation& right) const;

    /*!
     * @breif A overloaded relational operator to check less than or equal to 
     * inequality between two relation objects.
     */
    bool operator<=(const Relation& right) const;

    /*!
     * @breif A overloaded relational operator to check greater than or equal to 
     * inequality between two relation objects.
     */
    bool operator>=(const Relation& right) const;

    /*!
     * @breif A overloaded relational operator to check greater than or inequality 
     * between two relation objects.
     */
    bool operator>(const Relation& right) const;

    /*!
     * @breif A overloaded relational operator to check less than or inequality 
     * between two relation objects.
     */
    bool operator<(const Relation& right) const;

    /*!
     * @breif A method to clear the dependency set of the relation.
     */
    void clearDependencies();
    /*!
     * @breif A method to clear the attribute set of the relation.
     */
    void clearAttributes();

    /*!
     * @breif A getter method to retrieve the attribute set of the relation. 
     * @return The constant reference of the set_str object that represents the 
     * attribute set of the relation object.
     */
    const set_str& getAttributes() const {
        return attributes;
    }

    /*!
     * @breif A getter method to retrieve the dependency set of the relation. 
     * @return The constant reference of the set_dep object that represents the 
     * dependency set of the relation object.
     */
    const set_dep& getDependencies() const {
        return dependencies;
    }

    /*!
     * @breif A getter method to retrieve the name of the relation. 
     * @return The string representing the name of the relation.
     * attribute set of the relation object.
     */
    string getName() const {
        return name;
    }

    /*!
     * @breif A setter method to set the name of the relation. 
     * @param name a string parameter indicates the new name of the relation.
     */
    void setName(const string name) {
        this->name = name;
    }

    /*!
     * @breif A method to add single dependency object to the dependency set.
     */
    itr_dep addDependency(const Dependency &, bool update = true);



private:

    string name; /*!< string data member represents the name of the relation*/
    set_str attributes; /*!< set_str object represents the attribute set of the relation*/
    set_dep dependencies; /*!< set_dep object represents the dependency set of the relation*/


    /*!
     * @breif A recursive static method of the relation to decompose the parameter 
     * relation object into the BCNF form using the non FD preserving algorithm.
     */
    static void decompose(set_rel &rset, const Relation &r, bool details = false);

    /*!
     * @breif A static method to get next possible iteration set for calculating 
     * the candidate key using existing key and the attribute set parameter.
     */
    static void getNextIteration(set_key& key, const set_str& attributes);

    /*!
     * @breif A static method to reduce the RHS of all the parameter dependencies.
     */
    static set_dep reduceRHS(const set_dep &);

    /*!
     * @breif A static method to reduce the LHS of all the parameter dependencies.
     */
    static set_dep reduceLHS(const set_dep &);

    /*!
     * @breif A static method to reduce the rules of all the parameter dependencies.
     */
    static set_dep reduceRules(const set_dep &);

    /*!
     * @breif A predicate method used to process the LHS to find its the reduced 
     * form for a dependency. 
     */
    bool processLHS(const Dependency &);

    /*!
     * @breif A method to combine the dependencies from the dependency set of the 
     * relation which shares the same LHS.
     */
    void reducedDependencies(void);

    /*!
     * @breif A setter method to set the new dependency set for the relation.
     */
    void setDependencies(const set_dep &dependencies);

    /*!
     * @breif A setter method to set the new attribute set for the relation.
     */
    void setAttributes(const set_str attributes);


};




#endif /* RELATION_H */

