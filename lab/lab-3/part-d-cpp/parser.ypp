/* example.y */

%{
    #include <stdio.h>
    #include <math.h>
    #include "global.h"

    extern int yyerror(char const *msg);
    extern int token_value;
    extern int yylex();
%}

%token DONE ID NUM


%%

start: list DONE
        ;
list: assignment ';' list
        | comparison ';' list
        | /* empty */
        ;
assignment : ID '=' comparison    { $$ = $3; symtable[$1].value = $3; printf("%s\n=\n%d\n", symtable[$1].lexeme, $3); }
        ;
comparison : expr '&' expr      { $$ = $1 & $3; printf("&\n"); }
    | expr '|' expr             { $$ = $1 | $3; printf("|\n"); }
    | expr '<' expr             { $$ = $1 < $3; printf("<\n"); }
    | expr '>' expr             { $$ = $1 > $3; printf(">\n"); }
    | expr '?' expr ':' expr    { $$ = $1 ? $3 : $5; printf("?\n"); } 
    | expr
    ;
expr : expr '+' term    { $$ = $1 + $3; printf("+\n"); }
    | expr '-' term     { $$ = $1 - $3; printf("-\n"); }
    | term
    ;
term : term '*' factor     { $$ = $1 * $3; printf("*\n"); }
    | term '/' factor      { $$ = $1 / $3; printf("/\n"); }
    | term '%' factor      { $$ = $1 % $3; printf("%%\n"); } 
    | factor
    ;
factor : factor '^' exponential    { $$ = pow($1, $3); printf("^\n"); }
    | exponential
    ;
exponential : '(' comparison ')'    { $$ = $2;}
    | ID                    { $$ = symtable[$1].value; printf("%d\n", symtable[$1].value); }
    | NUM                   { printf("%d\n", $1); }
    ;

%%

int yyerror(char const *msg) {
    printf("Error: %s\n", msg);
    return 0;
}

int yylex() {
    int c = lexan();
    yylval = token_value;
    return c;
}

void parse() {
  yyparse();
}
