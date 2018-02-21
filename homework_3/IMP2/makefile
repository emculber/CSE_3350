
CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

imp: y.tab.o lex.yy.o imp.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o imp.o -o imp 

imp.o: imp.cpp imp.h
	${CCC} -c imp.cpp
y.tab.o: imp.yacc
	${YACC} ${YFLAGS} imp.yacc
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: imp.lex
	${LEX} $(LFLAGS) imp.lex
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o imp
