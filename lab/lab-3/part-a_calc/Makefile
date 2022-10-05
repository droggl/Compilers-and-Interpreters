CC = gcc
CFLAGS += -Wall -std=c99 -g

calc: calc.tab.o calc.tab.h lex.yy.o
	gcc $(CFLAGS) -o calc calc.tab.o lex.yy.o

calc.tab.c calc.tab.h: calc.y
	bison -d calc.y

lex.yy.c: calc.l
	flex calc.l

clean:
	$(RM) calc calc.tab.o calc.tab.c calc.tab.h lex.yy.o lex.yy.c
