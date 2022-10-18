OBJECTS = lex.yy.o parser.tab.o syntax_tree.o symbol.o
SOURCES = lex.yy.c parser.tab.cpp syntax_tree.cpp symbol.cpp
EXE = infix2postfix
CFLAGS += -Wall -g

$(EXE):	$(OBJECTS)
	g++ $(CFLAGS) -o $(EXE) $(OBJECTS) -lm

symbol.o: 	symbol.cpp global.h
	g++ $(CFLAGS) -c symbol.cpp

syntax_tree.o: syntax_tree.cpp global.h
	g++ $(CFLAGS) -c syntax_tree.cpp

lex.yy.o:	lex.yy.c global.h parser.tab.hpp
	g++ $(CFLAGS) -c lex.yy.c

lex.yy.c: scanner.l parser.tab.hpp
	flex scanner.l

parser.tab.o: 	parser.tab.cpp global.h parser.tab.hpp
	gcc $(CFLAGS) -c parser.tab.cpp

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp


clean:
	rm -f $(EXE) $(OBJECTS) lex.yy.c parser.tab.cpp parser.tab.hpp 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
