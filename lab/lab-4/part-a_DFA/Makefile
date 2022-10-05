CC = gcc
CFLAGS += -Wall -std=c99 -g

dfa: lex.yy.c
	gcc $(CFLAGS) lex.yy.c -o dfa

lex.yy.c: dfa.l
	flex dfa.l

clean:
	$(RM) dfa lex.yy.o lex.yy.c
