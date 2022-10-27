/* example.lex */

%{
#include <stdio.h>
#include "example.tab.h"
%}

%option noyywrap

%%

[ \t]+    { /* ignore whitespace */ }
"("       { return LPAREN; }
")"       { return RPAREN; }
"+"       { return PLUS; }
"-"       { return MINUS; }
"*"       { return STAR; }
"/"       { return SLASH; }
"="       { return EQUALS; }
\n        { return NEWLINE; }
[0-9]+    { yylval = atoi(yytext); return NUM; }
.         { printf("Ignoring invalid character '%s'\n", yytext); }

%%
