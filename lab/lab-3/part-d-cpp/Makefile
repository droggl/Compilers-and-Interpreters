OBJECTS = lexer.o parser.tab.o emitter.o symbol.o init.o error.o main.o
SOURCES = lexer.cpp parser.tab.cpp emitter.cpp symbol.cpp init.cpp error.cpp main.cpp
EXE = infix2postfix
CFLAGS += -Wall -g

$(EXE):	$(OBJECTS)
	gcc $(CFLAGS) -o $(EXE) $(OBJECTS) -lm

main.o: 	main.cpp global.h parser.tab.hpp
	gcc $(CFLAGS) -c main.cpp

parser.tab.o: 	parser.tab.cpp global.h parser.tab.hpp
	gcc $(CFLAGS) -c parser.tab.cpp

lexer.o: 	lexer.cpp global.h parser.tab.hpp
	gcc $(CFLAGS) -c lexer.cpp

emitter.o: 	emitter.cpp global.h
	gcc $(CFLAGS) -c emitter.cpp

symbol.o: 	symbol.cpp global.h
	gcc $(CFLAGS) -c symbol.cpp

init.o: 	init.cpp global.h
	gcc $(CFLAGS) -c init.cpp

error.o: 	error.cpp global.h
	gcc $(CFLAGS) -c error.cpp

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

clean:
	rm -f $(EXE) $(OBJECTS) parser.tab.hpp parser.tab.cpp 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
