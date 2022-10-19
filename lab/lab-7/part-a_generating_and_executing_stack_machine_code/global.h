/* global.h */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /* ... and for some standard routines, such as exit */
#include <string.h> /* ... and for string routines */
#include <math.h>
#include <vector>
#include <map>

#include "parser.tab.hpp"

#define MAX_ID_LENGTH  128  /* for the buffer size */
#define N 1000 /* stack size */

extern int token_value;   /*  value of token attribute */
extern int lineno;

struct symentry {  /*  form of symbol table entry  */
    char *lexeme;
    int  token_type;
    int value;
};

extern struct symentry symtable[];  /* symbol table  */

extern void error(char* message);  /*  generates all error messages  */
extern int insert(char *s, int token_type);    /*  returns position of entry for s */
extern int lookup(char *s);         /* returns position of entry for s, or -1 if not found */