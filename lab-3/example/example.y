/* example.y */

%{
#include <stdio.h>
#include "global.h"
extern int yyerror(char const *msg);
extern int yylex();
%}

%token DONE ID NUM DIV MOD
// %token PLUS MINUS STAR SLASH LPAREN RPAREN NUM NEWLINE EQUALS
%left PLUS MINUS
%left STAR SLASH

%%
line : /* empty */
     | line expr NEWLINE      { printf("%d\n", $2); }
expr : LPAREN expr RPAREN     { $$ = $2; }
     | expr PLUS expr         { $$ = $1 + $3; }
     | expr MINUS expr        { $$ = $1 - $3; }
     | expr STAR expr         { $$ = $1 * $3; }
     | expr SLASH expr        { $$ = $1 / $3; }
     | NUM                    { $$ = $1; }
     ;

%%

int yyerror(char const *msg) {
    printf("Error: %s\n", msg);
    return 0;
}

int yylex() {
    return lexan();
}

void parse() {
    yyparse();
}

int main() {
    printf("%d\n", yyparse());
    return 0;
}
