
CC	=	g++
CFLAGS	=	-std=c++11 -Werror
LINK	=	g++
LOADLIB	=	-lcppunit
TEST1	=	setstr_compare_test.o setstr_compare_test_runner.o
TEST2	=	utility_test.o utility_test_runner.o
TEST3	=	dependency_test.o dependency_test_runner.o
TEST4	=	relation_test.o relation_test_runner.o
OBJECT	=	../setstr_compare.o ../utility.o ../dependency.o ../relation.o ../user_interface.o
TESTEXE	=	test_setstr_compare test_utility test_dependency test_relation 

default : source $(TESTEXE)

test_setstr_compare : $(TEST1)
	$(LINK) $(CFLAGS) $(TEST1) $(OBJECT) $(LOADLIB) -o $@

test_utility : $(TEST2)
	$(LINK) $(CFLAGS) $(TEST2) $(OBJECT) $(LOADLIB) -o $@

test_dependency : $(TEST3)
	$(LINK) $(CFLAGS) $(TEST3) $(OBJECT) $(LOADLIB) -o $@ 

test_relation : $(TEST4)
	$(LINK) $(CFLAGS) $(TEST4) $(OBJECT) $(LOADLIB) -o $@

clean:
	rm -f $(TESTEXE) *.o *~

%.o : %.cc
	$(CC) -c $(CFLAGS) -c $< -o $@

test: source $(TESTEXE)  
	@echo 'Running test for setstr_compare class';
	@./test_setstr_compare;
	@echo 'Running test for utility functions';
	@./test_utility;
	@echo 'Running test for Dependency class';
	@./test_dependency;
	@echo 'Running test for Relation class';
	@./test_relation;

source: 
	@cd ..;	make clean -s; 	make;	cd tests;
