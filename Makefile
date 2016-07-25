
CC	=	g++
CFLAGS	=	-std=c++11 -Werror
LINK	=	g++
LFLAGS	=	${CFLAGS}
OBJECTS =	setstr_compare.o utility.o dependency.o relation.o user_interface.o
SOURCE	=	setstr_compare.cc utility.cc dependency.cc relation.cc user_interface.cc
EXEC	=	Decomposer

default: $(OBJECTS)

run: $(EXEC)
	@./$(EXEC)

clean:
	rm -f $(EXEC) *.o *~

%.o : %.cc
	$(CC) -c $(CFLAGS) -c $< -o $@

$(EXEC) : $(OBJECTS) main.o
	$(LINK) $(CFLAGS) main.o $(OBJECTS) -o $@


main.cc : user_interface.h

user_interface.cc : user_interface.h

relation.cc: relation.h dependency.h utility.h violation.h

dependency.cc : dependency.h utility.h

utility.cc: utility.h dependency.h relation.h

setstr_compare.cc : declaration.h

violation.h : declaration.h dependency.h relation.h

user_interface.h : declaration.h utility.h

relation.h : declaration.h dependency.h

dependency.h : declaration.h utility.h

utility.h : declaration.h template_def.h

declaration.h : typedef.h
