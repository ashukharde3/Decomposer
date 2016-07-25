Decomposer
Check out complete documentation at: https://ashukharde3.github.io/Decomposer
Decomposer is a relational decomposition tool that uses the functional dependencies of the relation to identifying normal form and generate the sub-relations.

It uses the either one of two algorithms - Functional Dependencies Preserving Lossless decomposition or the Non-Functional Dependencies Preserving Lossless decomposition. The FD Preserving algorithm guarantees that the sub-relations are at least in third normal form and all the original FDs are preserved. The non-FD preserving may not preserve all the original FDs but it guarantees that all the sub-relations are in BC Normal Form.

This is a command line tool built by using GCC the GNU compiler collection on Linux platform. Using command line interface, the user can provide the information about the functional dependencies and the attributes of the relations. The user then can perform decomposition of the relation or find out about the analysis of the relation.

The 'relation' in this tool represents the entity which has the identifying name, a set of attributes and a set of functional dependencies among these attributes. The 'attribute' represents characteristics of the relational entity. The dependencies define the deterministic relation between a set of attributes.

For example, R(a,b,c,d,e) {a->b , ab->de} In above example the relation name is R, the set of attributes is {a,b,c,d,e} and functional dependencies are {a} -> {b} and {a,b} -> {d,e}

Along with decomposition, the user can choose a different operation to be performed on the relation which includes finding minimal cover for dependency set, finding the candidate key for the relation, testing normal form of the relation and getting the dependencies that violate the particular normal form.

A command line based interactive menu driven user interface will be used by the application to accept user input and perform the corresponding action. The Makefile can be used to compile the source code create the executable. make run command can be used to compile and run the executable.

The testing for application is performed by using the CPPunit library. The unit tests are performed on various class methods and global functions.

The application can be started by using make run command or the executable program Decomposer can be used to start the application. The Relation object will be initialized first by providing details about relation name, attribute set and dependency set. The user can modify or reinitialize the Relation object as required. The user can select the different operation to be performed on this object using menu choice. Note: It is assumed that the input relation object is in at least first normal form, meaning the application currently do not support the multivalued attributes.


