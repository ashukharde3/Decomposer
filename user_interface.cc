/*! \file user_interface.cc
 * 
 * \brief Includes definitions of the UserInterface class members defined in the 
 * user_interface.h file
 *  
 * \details
 * This file contains definition of the undefined member functions of the class
 * UserInterface.
 * 
 */
#include "user_interface.h"
#include <iostream>
using std::endl;
using std::cin;

#include <regex>
#include <vector>
#include <sstream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <cstdlib>

/*!
  \def PRINT
  Defines the global output format using overloaded output with standard ostream
  object cout.
 */
#define PRINT std::cout<<std::setw(WIDTH) <<std::right<< ""

UserInterface *UserInterface::s_instance = 0;

const string UserInterface::DEFAULT_ERROR = "Error : Invalid input";
const string UserInterface::DEFAULT_MSG = "Please re-enter the value: ";
const string UserInterface::NAME_ERROR = "should contains only alpha numeric values starting from alphabet and must not empty!";

string getText(Relation::Normal n) {
    switch (n) {
        case Relation::_3NF: return "Third Normal Form";
        case Relation::_BCNF: return "Boyce-Codd Normal Form";
        default: return "Second Normal Form";
    }
}

void print(std::vector<string> &vec) {
    PRINT << "Vector is: ";
    bool first = true;
    for (const string &str : vec) {
        std::cout << (first ? "" : " | ");
        first = false;
        std::cout << str;
    }
    std::cout << std::endl;
}

template <class any>
any UserInterface::getValidInput(const string msg,
        const string error, bool(*isValid)(const any &)) {

    using namespace std;
    any a;
    string input = "";
    do {
        getline(cin, input);
        stringstream myStream(input);
        if (myStream >> a) {
            if (isValid != 0 && !isValid(a)) {
                PRINT << error << endl << endl;
                PRINT << msg;
                continue;
            }
            break;
        }
        if (cin) {
            PRINT << error << endl << endl;
            PRINT << msg;
        } else
            PRINT << endl;
    } while (cin);
    return a;
}

template <>
string UserInterface::getValidInput(const string msg,
        const string error, bool(*isValid)(const string &)) {

    using namespace std;
    string input = "";
    do {
        getline(cin, input);
        input = removeWhiteSpace(input);
        if (isValid != 0 && !isValid(input)) {
            PRINT << error << endl << endl;
            PRINT << msg;
            continue;
        }
        break;
        PRINT << endl;
    } while (cin);
    return input;
}

bool UserInterface::isValidDependnecy(const string &str) {

    string rs = removeWhiteSpace(str);
    return (!rs.empty() && !std::regex_search(rs, std::regex("[^\\w-> ,;]")));
}

bool UserInterface::isValidMainChoice(const char &ch) {
    return ((ch >= '1' && ch <= '6')
            || (ch == 'q' || ch == 'Q'));
}

bool UserInterface::isValidEditChoice(const char &ch) {
    return ((ch >= '1' && ch <= '8')
            || (ch == 'c' || ch == 'C'));
}

bool UserInterface::isValidNormalChoice(const char &ch) {
    return ((ch >= '1' && ch <= '3') || ch == 'c' || ch == 'C');
}

bool UserInterface::isValidName(const string &str) {
    string rs = removeWhiteSpace(str);
    return (!rs.empty() && std::regex_search(rs, std::regex("^([[:alpha:]]|_)(\\w*)$")));
}

void UserInterface::printMainMenu() const {

    PRINT << endl;
    PRINT << "Main Menu" << endl;
    PRINT << "1. Edit Relation" << endl;
    PRINT << "2. Print Relation" << endl;
    PRINT << "3. Print Candidate Key" << endl;
    PRINT << "4. Test Normal From" << endl;
    PRINT << "5. Minimal Cover" << endl;
    PRINT << "6. Decompose Relation" << endl;
    PRINT << "[Enter q to quit]" << endl << endl;
    PRINT << "Please enter your choice : ";
}

void UserInterface::run() {

    PRINT << "Starting the application" << endl;

    createRelation();

    char ch = 'q';
    do {
        if (rel != 0) {
            printMainMenu();

            ch = getValidInput("Please re-enter your choice: ", "Error: Invalid choice!", &isValidMainChoice);
            switch (ch - '0') {
                case 1:
                {
                    processEdit();
                    break;
                }
                case 2:
                {
                    PRINT << *rel << endl;
                    break;
                }
                case 3:
                {
                    PRINT << "Candidate key: " << rel->getCandidatekey() << endl;
                    break;
                }
                case 4:
                {
                    processNormal();
                    break;
                }
                case 5:
                {
                    if (!rel->getDependencies().empty()) {
                        PRINT << "Original dependencies: " << rel->getDependencies() << endl;
                        bool opt = getDetail();
                        set_dep mc = rel->getMinimalCover(opt);
                        if (opt)
                            PRINT << endl;
                        PRINT << "Minimal cover: " << mc << endl;
                    } else {
                        PRINT << "The functional dependency set is empty" << endl;
                    }
                    break;
                }
                case 6:
                {
                    if (!rel->getAttributes().empty()) {
                        processDecompose();
                    } else {
                        PRINT << "The attribute set is empty" << endl;
                    }
                    break;
                }
            }
        } else {
            ch = '\0';
            PRINT << "The relation is not initialized yet" << endl;
            createRelation();
        }
    } while (ch != 'q' && ch != 'Q' && cin);
    PRINT << "Terminating the application" << endl;
}

void UserInterface::printEditMenu() const {

    PRINT << endl;
    PRINT << "Relation: " << *rel << endl << endl;
    PRINT << "Edit Relation Menu" << endl;
    PRINT << "1. Add Attributes" << endl;
    PRINT << "2. Add Functional Dependencies" << endl;
    PRINT << "3. Rename Relation" << endl;
    PRINT << "4. Remove Functional Dependency" << endl;
    PRINT << "5. Remove Attributes" << endl;
    PRINT << "6. Clear all Attributes (Note: clears all functional dependencies)" << endl;
    PRINT << "7. Clear all functional dependencies" << endl;
    PRINT << "8. Re-enter Relation" << endl;
    PRINT << "[Enter c to cancel]" << endl << endl;
    PRINT << "Please enter your choice : ";
}

void UserInterface::processEdit() {

    char ch;
    do {
        printEditMenu();
        ch = getValidInput("Please re-enter your choice: ", "Error: Invalid choice!", &isValidEditChoice);
        //PRINT << "Choice " << ch;

        switch (ch - '0') {
            case 1:
            {
                processAddAttributes();
                PRINT << endl;
                break;
            }
            case 2:
            {
                processAddDepedencies();
                PRINT << endl;
                break;
            }
            case 3:
            {
                string name;
                PRINT << "Enter the relation name: ";

                name = getValidInput<string>("Please re-enter the relation name: ",
                        "Error: Relation name should contains only alpha numeric values starting from alphabet and must not empty!",
                        &isValidName);
                rel->setName(name);
                PRINT << "Relation name changed" << endl;
                break;
            }
            case 4:
            {
                if (!rel->getDependencies().empty()) {
                    processRemoveDependency();
                } else {
                    PRINT << "Dependency set is empty" << endl;
                }
                PRINT << endl;
                break;
            }
            case 5:
            {
                if (!rel->getDependencies().empty()) {
                    processRemoveAttribute();
                } else {
                    PRINT << "Attribute set is empty" << endl;
                }
                PRINT << endl;
                break;
            }
            case 6:
            {
                if (!rel->getAttributes().empty()) {
                    PRINT << "You are about to delete all the attributes."
                            << "(all the functional dependencies will lost)" << endl;
                    PRINT << "Are you sure you want to remove all the attributes?[0-no | 1-yes]: ";
                    if (getValidInput<bool>("Please re-enter your option [0-no | 1-yes]:")) {
                        rel->clearAttributes();
                    }
                } else {
                    PRINT << "Attribute set is empty" << endl;
                }
                PRINT << endl;
                break;
            }
            case 7:
            {
                if (!rel->getDependencies().empty()) {
                    PRINT << "Are you sure you want to remove all the dependencies?[0-no | 1-yes]: ";
                    if (getValidInput<bool>("Please re-enter your option [0-no | 1-yes]:")) {
                        rel->clearDependencies();
                    }
                } else {
                    PRINT << "Dependency set is empty" << endl;
                }
                PRINT << endl;
                break;
            }
            case 8:
            {
                PRINT << "Are you sure you want to remove current relation?[0-no | 1-yes]: ";
                if (getValidInput<bool>("Please re-enter your option [0-no | 1-yes]:")) {
                    createRelation();
                }
                PRINT << endl;
                break;
            }
        }
    } while (ch != 'c' && ch != 'C' && cin);
}

void UserInterface::processAddAttributes() {
    std::vector<string> att = getAttributes();
    set_str atr(att.begin(), att.end());
    if (rel->addAtributtes(atr))
        PRINT << "Attribute set updated" << endl;
    else
        PRINT << "No new attribute inserted, attributes already present in the relation" << endl;
    if (rel->getAttributes().size())
        PRINT << "Attributes: " << rel->getAttributes() << endl;
}

bool UserInterface::processAddDepedencies() {

    bool add = false, retry;

    do {
        retry = false;
        std::vector<string> att = getDependencies();
        for (const string & str : att) {
            set_str lhs;
            set_str rhs;
            if (extractDependency(str, lhs, rhs)) {
                bool ch = true;
                if (!isSubset(rel->getAttributes(), rhs) || !isSubset(rel->getAttributes(), lhs)) {
                    PRINT << "All the attributes are not present in the relation for functional dependency "
                            << "\'" << lhs << " -> " << rhs << "\', " << endl;
                    PRINT << "Do you still want to add this dependency?[0-no | 1-yes]: ";
                    ch = UserInterface::getValidInput<bool>("Please re-enter your option [0-no | 1-yes]: ");
                }
                if (ch) {
                    add = true;
                    itr_dep d = rel->addDependency(lhs, rhs, ch);
                    if (d != rel->getDependencies().end())
                        PRINT << "Dependency \'" << *d << "\' added to the relation" << endl;
                    else
                        PRINT << "Dependency \'" << lhs << " -> " << rhs << "\' already present in the relation" << endl;
                    //rel->reducedDependencies();
                }
            }
        }
        if (add)
            PRINT << "Functional dependencies: " << rel->getDependencies() << endl;
        else {
            PRINT << "No valid dependencies found in the input" << endl;
            PRINT << "Do you want to retry?[0-No, 1-Yes]: ";
            retry = getValidInput<bool>("Please re-enter the option[0-No, 1-Yes]: ");
            PRINT << endl;
        }
    } while (retry && cin);
    return add;
}

std::vector<string> UserInterface::getAttributes() const {
    string input;
    PRINT << endl;
    PRINT << "Add Attributes. Note - " << endl;
    PRINT << "1.Attribute can only start with alphabet" << endl;
    PRINT << "2.Multiple attributes can be entered, separated by \',\'" << endl;
    PRINT << "3.Any invalid attributes will be ignored" << endl;
    PRINT << "Example- A,B, Cust_Name, PhoneNo1" << endl << endl;
    std::vector<std::string> aset;
    bool retry = false;
    do {
        PRINT << "Enter the attributes: ";
        getline(cin, input);
        aset = UserInterface::validSplit(input, ",", &isValidName);

        if (aset.empty()) {
            PRINT << "No valid attributes found in the input" << endl;
            PRINT << "Do you want to retry?[0-No, 1-Yes]: ";
            retry = getValidInput<bool>("Please re-enter the option[0-No, 1-Yes]: ");
            PRINT << endl;
        }
    } while (retry && cin);
    return aset;
}

std::vector<string> UserInterface::getDependencies() const {
    string input;
    PRINT << endl;
    PRINT << "Add Dependency. Note - " << endl;
    PRINT << "1.Attribute can only start with alphabet" << endl;
    PRINT << "2.Multiple attributes can be entered, separated by \',\'" << endl;
    PRINT << "3.The LHS and RHS of functional dependencies should be separated by \'->\''" << endl;
    PRINT << "4.Multiple Functional Dependencies can be entered, separated by \';\'" << endl;
    PRINT << "5.Any invalid attributes or dependencies will be ignored" << endl;
    PRINT << "Example- A,B -> C; Cust_No -> Cust_Name, Cust_Phn1" << endl << endl;
    std::vector<std::string> aset;
    bool retry = false;
    do {
        PRINT << "Enter the dependencies: ";
        getline(cin, input);
        aset = UserInterface::validSplit(input, ";");

    } while (retry && cin);
    return aset;
}

bool UserInterface::extractDependency(const string & str, set_str &lhs, set_str &rhs) {
    std::vector<std::string> dep;
    //std::cout << "Testing: " << str << endl;
    dep = UserInterface::validSplit(str, "->");
    string err_msg = "is invalid functional dependency\n";
    if (dep.empty() || dep.size() != 2) {
        std::cerr << "\n\'" << str << "\'" << err_msg << endl;
        return false;
    }
    bool first = true;
    for (const string &str : dep) {

        std::vector<std::string> side = validSplit(str, ",", &isValidName);
        if (side.empty()) {
            std::cerr << "\n\'" << dep[0] << " -> " << dep[1] << "\'" << err_msg << endl;
            return false;
        }
        if (first) {
            lhs.insert(side.begin(), side.end());
            first = false;
        } else {
            rhs.insert(side.begin(), side.end());
        }
    }

    return (!lhs.empty() && !rhs.empty());
}

void UserInterface::createRelation() {
    if (rel != 0)
        delete rel;
    PRINT << endl;
    PRINT << "Initialize the relation" << endl << endl;
    PRINT << "Enter the relation name: ";
    string name = getValidInput("Please re-enter the relation name: ",
            "Error: Invalid relation name. Relation name should not be empty and must start with an alphabet",
            &isValidName);
    if (!cin.good()) {
        std::cerr << "Initialization of the relation failed" << std::endl;
        std::cerr << "Aborting the application" << std::endl;
        exit(EXIT_FAILURE);
    }
    rel = new Relation(name);
    PRINT << endl;
    PRINT << "Do you want to add attributes to the relation[0-no | 1-yes]: ";
    if (getValidInput<bool>("Please re-enter your option [0-no | 1-yes]:")) {
        processAddAttributes();
        PRINT << endl;
    }
    PRINT << "Do you want to add dependencies [0-no | 1-yes]: ";
    if (getValidInput<bool>("Please re-enter your option [0-no | 1-yes]:")) {
        processAddDepedencies();
        PRINT << endl;
    }
}

std::vector<std::string> UserInterface::validSplit(const std::string &s,
        const string &delim, bool(*isValid)(const string &)) {
    std::vector<string> vec = split(s, delim);
    //long unsigned int size = vec.size();
    vec = validateVec(vec, isValid);
    /*    if (size != vec.size()) {
            std::cerr << "\n" << size - vec.size() << " invalid strings ignored\n" << std::endl;
        }
     */
    return vec;
}

std::vector<string> UserInterface::validateVec(const std::vector<string> &v,
        bool(*isValid)(const string &)) {

    std::vector<string> ret;
    for (const string &str : v) {
        string val_str = removeWhiteSpace(str);
        if (!val_str.empty()
                && (isValid == 0 || (isValid != 0 && isValid(val_str))))
            ret.push_back(val_str);
    }
    return ret;
}

std::vector<std::string> UserInterface::split(const string& input, const string & regex) {
    // passing -1 as the submatch index parameter performs splitting
    std::regex re(regex);
    std::sregex_token_iterator
    first{input.begin(), input.end(), re, -1},
    last;
    return
    {
        first, last
    };
}

string UserInterface::removeWhiteSpace(const string & str) {
    string item = str;
    if (std::regex_search(item, std::regex("\t+")))
        item = std::regex_replace(item, std::regex("\t+"), "");
    if (std::regex_search(item, std::regex("^ +")))
        item = std::regex_replace(item, std::regex("^ +"), "");
    if (std::regex_search(item, std::regex(" +$")))
        item = std::regex_replace(item, std::regex(" +$"), "");
    return item;
}

bool UserInterface::processRemoveDependency() {
    if (!rel->getDependencies().empty()) {
        PRINT << "Functional dependencies: " << rel->getDependencies() << endl;
        PRINT << "Enter the dependency that you want to remove: ";
        string str = getValidInput<string>("Re-enter the dependency(Enter any other character to stop): ",
                "Error: Invalid dependency", &isValidDependnecy);
        if (!str.empty() && cin) {
            set_str lhs;
            set_str rhs;
            if (extractDependency(str, lhs, rhs)) {
                bool erase = rel->removeDependency(lhs, rhs);
                if (erase)
                    PRINT << "Dependency removed form the relation" << endl;
                else
                    PRINT << "Dependency not found in the relation" << endl;
                return erase;
            }
        } else {
            std::cerr << "Error occurred during extracting the dependency" << endl;
        }
    } else {
        PRINT << "The functional dependency set is empty" << endl;
    }
    return false;
}

bool UserInterface::processRemoveAttribute() {
    if (!rel->getAttributes().empty()) {
        PRINT << "Attributes: { " << rel->getAttributes() << " }" << endl;
        PRINT << "Enter the attribute to remove: ";
        string str = getValidInput<string>("Please re-enter the attribute: ",
                "Error: Invalid attribute!", &isValidName);
        bool remove = rel->removeAtributte(str);
        if (remove)
            PRINT << "Attribute removed form the relation" << endl;
        else
            PRINT << "Attribute not found in the relation" << endl;
        return remove;
    } else {
        PRINT << "The attribute set is empty" << endl;
    }
    return false;
}

void UserInterface::processDecompose() const {
    PRINT << "Decompose Relationship" << endl;
    PRINT << "0. Not FD Preserving Loss Less Decomposition (Guarantees BCNF)" << endl;
    PRINT << "1. FD Preserving Loss Less Decomposition (Guarantees at least 3NF)" << endl;
    PRINT << "Please enter your choice: ";
    bool ch = getValidInput<bool>("Please re-enter your option [0-FD PReserving, 1-FD Not Preserving]: ", "Error: Invalid choice!");
    bool detail = getDetail();
    PRINT << endl;
    set_rel decompose = ch ? rel->decomposePreserving(detail) : rel->decomposeNotPreserving(detail);
    if (detail)
        PRINT << endl;

    if ((ch && !rel->isNormal(Relation::_3NF))
            || (!ch && !rel->isNormal(Relation::_BCNF))) {
        PRINT << "Decomposed relations are" << endl;
        PRINT << decompose << endl;
    } else {
        PRINT << "No need to decompose the relation. Already satisfies the normal form requirement" << endl;
        PRINT << *rel << endl;
    }
}

void UserInterface::processNormal() const {
    char ch = 'c';
    do {
        PRINT << "Test Normal Form" << endl;
        PRINT << "1. " << getText(Relation::_2NF) << endl;
        PRINT << "2. " << getText(Relation::_3NF) << endl;
        PRINT << "3. " << getText(Relation::_BCNF) << endl;
        PRINT << "[Enter c for cancel]" << endl;
        PRINT << "Please enter your choice: ";
        ch = getValidInput("Please re-enter your choice: ", "Error: Invalid choice!", &isValidNormalChoice);
        Relation::Normal n = ch == '1' ? Relation::_2NF :
                ch == '2' ? Relation::_3NF : Relation::_BCNF;
        PRINT << endl;
        PRINT << "Candidate key: " << rel->getCandidatekey() << endl;
        PRINT << "Testing for " << getText(n) << endl;
        if (rel->isNormal(n)) {
            PRINT << "Relation is in " << getText(n) << endl;
        } else {
            PRINT << "Relation is not in " << getText(n) << endl;
            PRINT << "Dependencies that violate the normal form are: "
                    << rel->getViolation(n) << endl;
        }
        PRINT << endl;
    } while (ch != 'c' && ch != 'C' && cin);
}

bool UserInterface::getDetail() {
    PRINT << "Do you want step-by-step output of this process? [0-No, 1-Yes]: ";
    return getValidInput<bool>("Please re-enter your option [0-No, 1-Yes]: ", "Error: Invalid choice!");
}

#undef PRINT
