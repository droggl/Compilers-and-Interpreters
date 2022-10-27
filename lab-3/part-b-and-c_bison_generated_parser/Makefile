OBJECTS = lexer.o parser.tab.o emitter.o symbol.o init.o error.o main.o 
SOURCES = lexer.c parser.tab.c emitter.c symbol.c init.c error.c main.c
EXE = infix2postfix
CFLAGS += -Wall -g 

$(EXE):	$(OBJECTS)
	gcc $(CFLAGS) -o $(EXE) $(OBJECTS) -lm

main.o: 	main.c global.h parser.tab.h
	gcc $(CFLAGS) -c main.c

parser.tab.o: 	parser.tab.c global.h parser.tab.h
	gcc $(CFLAGS) -c parser.tab.c

lexer.o: 	lexer.c global.h 
	gcc $(CFLAGS) -c lexer.c

emitter.o: 	emitter.c global.h
	gcc $(CFLAGS) -c emitter.c

symbol.o: 	symbol.c global.h
	gcc $(CFLAGS) -c symbol.c

init.o: 	init.c global.h
	gcc $(CFLAGS) -c init.c

error.o: 	error.c global.h
	gcc $(CFLAGS) -c error.c

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

clean: 
	rm -f $(EXE) $(OBJECTS) parser.tab.h parser.tab.c 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
