/* example.lex */

%{
#include <stdio.h>
#include "global.h"
%}

%option noyywrap
%option nounput
%option noinput

%%

[ \t\n]+      { /* ignore whitespace */ }
    /* numbers */
[0-9]+          {
                    yylval = atoi(yytext);
                    return NUM; }
    /* variable */
[a-zA-Z]+       {
                    yylval = lookup(yytext);
                    if (yylval == -1)
                        yylval = insert(yytext, ID);
                    return ID;
                }
    /* operators */
[-+()*/%=;&|<>?:^]         { return *yytext; }
    /* anything else is invalid */
.           printf("Ignoring invalid character '%s'\n", yytext);


%%
