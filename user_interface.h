/*! 
 * \file user_interface.h
 * 
 * \brief Includes declaration for the class UserInterface and its members.
 *  
 * \details
 * This file declares the definition of the class UserInterface along with its 
 * subsequent data members and the member functions prototype.
 * 
 */
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <iomanip>

#include <vector>

#include "declaration.h"
#include "relation.h"

class UserInterface;

/*!
 * \class UserInterface
 * \brief The UserInterface class that represents the interface class which 
 * interacts with the user using command line interface and performs the actions
 * accordingly.
 * \details The UserInterface class follows the singleton design pattern and instance 
 * of the this class can be retrieve by the UserInterface::instance method. It hides
 * all the other detailed methods that handles the user input, validation of input
 * and performs the actions accordingly. The interface will be 'started' by using the 
 * run method of the class.
 * 
 */

class UserInterface {
public:

    /*!
     * @breif This method will starts the user interface programs and handles user 
     * interaction using menu driven command line options
     */
    void run();

    /*!
     * @breif This is static method which provide the reference of the single 
     * UserInterface object.
     * @return It returns the reference of the is already existing UserInterface 
     * object.
     * @details The method will provide the single access point to the shared 
     * UserInterface object. This will ensures the singleton design pattern 
     * allowing only single instance of the class at any time.
     * 
     */
    static UserInterface& instance() {
        if (!s_instance)
            s_instance = new UserInterface();
        return *s_instance;
    }

    /*!
     * @breif The destructor for UserInterface class 
     */
    ~UserInterface() {
        if (rel != 0)
            delete rel;
    }

private:
    static const string DEFAULT_ERROR; /*!< The constant string representing the default error message*/
    static const string DEFAULT_MSG; /*!< The constant string representing the default input message*/
    static const string NAME_ERROR; /*!< The constant string representing the default error message for the attributes or relation name*/
    static UserInterface *s_instance; /*<The static instance pointer of UserInterface */

    Relation *rel; /*< The relation object pointer to perfomr the operation*/

    /*
     * @breif Split the string token for parameter string with given delimiter.
     */
    static std::vector<std::string> split(const std::string &s, const string &delim = "");
    /*
     * @breif Split the string into the and validating the tokens.
     */
    static std::vector<std::string> validSplit(const std::string &s,
            const string &delim = "", bool(*isValid)(const string &) = 0);
    /*
     * @breif Removes the spaces at start and end of the string.
     */
    static string removeWhiteSpace(const string &str);
    /*
     * @breif Validates the string vector
     */
    static std::vector<string> validateVec(const std::vector<string> &v,
            bool(*isValid)(const string &) = 0);

    /*
     * @breif Accepts the valid input from the user.
     */
    template <class any>
    static any getValidInput(const string msg = DEFAULT_MSG,
            const string error = DEFAULT_ERROR,
            bool(*isValid)(const any &) = 0);

    /*
     * @breif Predicate function to check parameter is valid main choice.
     */
    static bool isValidMainChoice(const char &ch);
    
    /*
     * @breif Predicate function to check parameter is valid edit choice.
     */
    static bool isValidEditChoice(const char &ch);
    
    /*
     * @breif Predicate function to check parameter is normal form main choice.
     */
    static bool isValidNormalChoice(const char &ch);
    
    /*
     * @breif Predicate function to check parameter is valid name for Relation or 
     * attribute.
     */
    static bool isValidName(const string &str);
    
    /*
     * @breif Predicate function to check parameter is valid dependency.
     */
    static bool isValidDependnecy(const string &str);

    /*
     * @breif A method to accept valid boolean choice for the details option.
     */
    static bool getDetail();

    /*
     * @breif A method to print the Main Menu.
     */
    void printMainMenu()const;
    /*
     * @breif A method to print the Edit Menu.
     */
    void printEditMenu()const;
    /*
     * @breif A method to process the Test Normal option.
     */
    void processNormal()const;
    /*
     * @breif A method to process the Decompose option.
     */
    void processDecompose()const;

    /*
     * @breif A method to process the Edit Relation option.
     */
    void processEdit();
    
    /*
     * @breif A method to process the Add Attribute option.
     */
    void processAddAttributes();
    
    /*
     * @breif A method to process the Add Dependency option.
     */
    bool processAddDepedencies();
    
    /*
     * @breif A method to process the Remove Dependency option.
     */
    bool processRemoveDependency();
    
    /*
     * @breif A method to process the Remove Attribute option.
     */
    bool processRemoveAttribute();
    
    /*
     * @breif A method to extract the dependency from the string input;
     */
    bool extractDependency(const string &dep, set_str &, set_str &);

    /*
     * @breif A method to retrieve multiple attribute tokens from input string.
     */
    std::vector<string> getAttributes() const;

    /*
     * @breif A method to retrieve multiple dependency tokens from input string.
     */
    std::vector<string> getDependencies() const;

    /*
     * @breif A method to initialize the new relation object.
     */
    void createRelation();

    /*
     * @breif A private constructor for UserInterface.
     */
    UserInterface() {
        rel = 0;
    }
    ///To prevent the use of copy constructor.
    UserInterface& operator=(const UserInterface& right);

};


#endif /* USERINTERFACE_H */

