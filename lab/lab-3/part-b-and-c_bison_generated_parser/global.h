/* global.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */
#include <math.h>

#include "parser.tab.h"

#define MAX_ID_LENGTH  128  /* for the buffer size */
#define N 1000 /* stack size */

#define NONE   -1
#define EOS    '\0'

// #define NUM    255 //yytokentype.NUM
// #define STAR   256 // yytokentype.STAR
// #define DIV    257
//     DONE = 258,
//     ID = 259,
//     NUM = 260
// #define MOD    258
// #define ID     259
// #define DONE   260

typedef int bool;
enum { false, true };

extern int token_value;   /*  value of token attribute */  
extern int lineno;

struct symentry {  /*  form of symbol table entry  */
    char *lexeme; 
    int  token_type;
    int value;
    bool value_initialized;
};

extern struct symentry symtable[];  /* symbol table  */

extern void init();  /*  loads keywords into symtable  */
extern void error(char* message);  /*  generates all error messages  */
extern int lexan();  /*  lexical analyzer  */
extern void parse();  /*  parses and translates expression list  */
extern int insert(char *s, int token_type);    /*  returns position of entry for s */
extern int lookup(char *s);         /* returns position of entry for s, or -1 if not found */
extern void emit (int token_type, int token_value);  /*  generates output  */
extern void calc (int token_type, int token_value);