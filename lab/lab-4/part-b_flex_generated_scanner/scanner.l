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
"("         { return LPAREN; }
")"         { return RPAREN; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return STAR; }
"/"         { return DIV; }
"%"         { return MOD; }
"="         { return EQUALS; }
";"         { return SEMICOL; }
"&"         { return AMPERSAND; }
"|"         { return BITOR; }
"<"         { return SMALLER; }
">"         { return GREATER; }
"?"         { return QUESTION; }
":"         { return COLON; }
"^"         { return CIRC; }
[0-9]+      { yylval = atoi(yytext); return NUM; }
[a-zA-Z]+      { yylval = lookup(yytext); if (yylval == -1) yylval = insert(yytext, ID); return ID; }
.           { printf("Ignoring invalid character '%s'\n", yytext); }

%%
