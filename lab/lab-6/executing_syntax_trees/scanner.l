/* example.lex */

%{
#include <stdio.h>
#include "global.h"
%}

%option noyywrap
%option nounput
%option noinput

%%

QQ     return DONE;


    /* numbers */
[0-9]+          {
                    yylval.iValue = atoi(yytext);
                    return NUM; }

    /* operators */
[-+()*/%=;&|<>?:^{}]      return *yytext;

"while"   return WHILE;
"if"      return IF;
"else"    return ELSE;
"print"   return PRINT;
"read"    return READ;


    /* variable */
[a-zA-Z]+       {
                    yylval.iValue = lookup(yytext);
                    if (yylval.iValue == -1)
                        yylval.iValue = insert(yytext, ID);
                    return ID;
                }

[ \t\n]+      { /* ignore whitespace */ }

    /* anything else is invalid */
.   printf("Ignoring invalid character '%s'\n", yytext);


%%
