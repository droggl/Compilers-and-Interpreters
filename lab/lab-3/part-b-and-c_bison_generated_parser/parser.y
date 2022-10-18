/* parser.y */

%{
    #include <stdio.h>
    #include <math.h>
    #include "global.h"

    extern int yyerror(char const *msg);
    extern int token_value;
    extern int yylex();
%}

%token DONE ID NUM
%left '&' '|' '<' '>' '?' ':'
%left '+' '-'
%left '*'
%left '/' '%'
%left '^'

%%

start: list DONE
        ;
list: assignment ';' list
        | expr ';' list
        | /* empty */
        ;
assignment : ID '=' expr    { $$ = $3; symtable[$1].value = $3; printf("%s\n=\n%d\n", symtable[$1].lexeme, $3); }
        ;
expr : NUM                  { printf("%d\n", $1); }
    | ID                    { $$ = symtable[$1].value; printf("%d\n", symtable[$1].value); }
    | expr '+' expr         { $$ = $1 + $3; printf("+\n"); }
    | expr '-' expr         { $$ = $1 - $3; printf("-\n"); }
    | expr '*' expr         { $$ = $1 * $3; printf("*\n"); }
    | expr '/' expr         { $$ = $1 / $3; printf("/\n"); }
    | expr '%' expr         { $$ = $1 % $3; printf("%%\n"); }
    | expr '^' expr         { $$ = pow($1, $3); printf("^\n"); }
    | '(' expr ')'    { $$ = $2; }
    | expr '&' expr      { $$ = $1 & $3; printf("&\n"); }
    | expr '|' expr             { $$ = $1 | $3; printf("|\n"); }
    | expr '<' expr             { $$ = $1 < $3; printf("<\n"); }
    | expr '>' expr             { $$ = $1 > $3; printf(">\n"); }
    | expr '?' expr ':' expr    { $$ = $1 ? $3 : $5; printf("?\n"); }
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
