/* example.y */

%{
    #include <stdio.h>
    #include <math.h>
    #include "global.h"

    extern int yyerror(char const *msg);
    extern int yylex();
%}

%token DONE ID NUM MOD LPAREN RPAREN PLUS MINUS STAR CIRC DIV EQUALS NEWLINE SEMICOL AMPERSAND BITOR SMALLER GREATER QUESTION COLON

%%

start: list DONE
        ;
list: assignment SEMICOL list
        | comparison SEMICOL list
        | /* empty */
        ;
assignment : ID EQUALS comparison    { $$ = $3; symtable[$1].value = $3; printf("%s\n=\n%d\n", symtable[$1].lexeme, $3); }
        ;
comparison : expr AMPERSAND expr      { $$ = $1 & $3; printf("&\n"); }
    | expr BITOR expr             { $$ = $1 | $3; printf("|\n"); }
    | expr SMALLER expr             { $$ = $1 < $3; printf("<\n"); }
    | expr GREATER expr             { $$ = $1 > $3; printf(">\n"); }
    | expr QUESTION expr COLON expr    { $$ = $1 ? $3 : $5; printf("?\n"); } 
    | expr
    ;
expr : expr PLUS term    { $$ = $1 + $3; printf("+\n"); }
    | expr MINUS term     { $$ = $1 - $3; printf("-\n"); }
    | term
    ;
term : term STAR factor     { $$ = $1 * $3; printf("*\n"); }
    | term DIV factor      { $$ = $1 / $3; printf("/\n"); }
    | term MOD factor      { $$ = $1 % $3; printf("%%\n"); } 
    | factor
    ;
factor : factor CIRC exponential    { $$ = pow($1, $3); printf("^\n"); }
    | exponential
    ;
exponential : LPAREN comparison RPAREN    { $$ = $2;}
    | ID                    { $$ = symtable[$1].value; printf("%d\n", symtable[$1].value); }
    | NUM                   { printf("%d\n", $1); }
    ;

%%

int yyerror(char const *msg) {
    printf("Error: %s\n", msg);
    return 0;
}

int main() {
    yyparse();
    exit(0);
}
