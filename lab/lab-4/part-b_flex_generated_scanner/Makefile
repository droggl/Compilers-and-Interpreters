OBJECTS = lex.yy.o parser.tab.o symbol.o
SOURCES = lex.yy.c parser.tab.c symbol.c
EXE = infix2postfix
CFLAGS += -Wall -g 

$(EXE):	$(OBJECTS)
	gcc $(CFLAGS) -o $(EXE) $(OBJECTS) -lm

parser.tab.o: 	parser.tab.c global.h parser.tab.h
	gcc $(CFLAGS) -c parser.tab.c

symbol.o: 	symbol.c global.h
	gcc $(CFLAGS) -c symbol.c

lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y


clean: 
	rm -f $(EXE) $(OBJECTS) lex.yy.c parser.tab.c parser.tab.h 29.tar.gz 29.zip *~

archives: clean
	cd ..; rm 29.tar 29.zip 29/29.tar 29/29.zip; tar -cvf 29.tar 29; gzip -9 29.tar; zip -r 29.zip 29; mv 29.zip 29/29.zip; mv 29.tar.gz 29/29.tar.gz
