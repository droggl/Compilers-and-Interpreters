// + --- Topics --- #
// Decorated parse tree
// Syntax-directed translation
// Yacc/Bison


Grammar:
expr -> number | expr + expr | expr / expr

ex. input: 
2 / 3 + 5 

// # --- Decorated parse tree --- #
                         expr
                         5.667
                         float
                         23/5+
                       /   |   \
                      /     \   \
                    expr     \   \
                   0.667      \   \
                   float       \   \
                    23/        |   |
                  /  |  \      |   |
               expr  | expr    |  expr           // three attributes: value, type, postfix
                2        3          5
               int   |  int    |   int
                2        3         5
                |    |   |     |   |
Token stream: number / number  + number
                2        3        5 <- lexical values
               int      int      int
 



Two types of syntax-directed translation

1. Syntax-directed definition
   Syntax-directed translation scheme

Production              |    Semantic rule                                          A syntax directed translation scheme:
------------------------|----------------------------------------                   expr -> number {print(number.value)} <- semantic action
expr -> number          |    expr.value = number.value                              expr -> expr + expr {print("+")}
                        |    expr.type = int                                        expr -> expr / expr {print("/")}
------------------------|----------------------------------------                   // for example 2/3+5 : 23/5+
expr1 -> expr2 / expr3  |   expr1.value = expr2.value / expr3.value                 
                        |   expr1.type = float                                      
------------------------|----------------------------------------                   
expr1 -> expr2 + expr3  |   expr1.value = expr2.value + expr3.value                 
                        |   if expr2.type == float or expr3.type == float           
                        |       expr1.type = float                                  
                        |   else                                                    
                        |       expr1.type = int                                    
-----------------------------------------------------------------                   



// # --- Yacc / Bison --- #
                                                                      foo.java
                                                                         |
java.y = grammar                                                         v
expr: expr  '+' expr;   -> bison     -> java.tab.c      -> gcc      -> javac
                                \                                        |
                                java.tab.h <- #define NUM 710            v 
                                                                      foo.class

java.y
_____________________________________________________________________
Declarations                %{                          |
%%                            #include <stdio.h>        |
Productions       =>          #include "global.h"       | c declarations
%%                            extern int tokenval;      |
c code                      %}                          |

                            %token ID NUM IF ELSE ...                             |
                             ...                                                  |
                            %%                                                    |
                            start : list DONE ;     // start -> list DONE         |
                            list : expr ';' list    // list -> expr; list | E     |
                                 | %empty                                         | bison
                                 ;                                                |
                            expr : expr '+' term {prinf("+");}                    |
                                 | term                                           |
                                 ;                                                |
                            ...                                                   |
                            %%                                                    |
____________________________________________________________________


// A calculator
2 + 3 * 4 + 5 
            = 19
2 + (3 - 4) * 5

Bison input file:
_______________________________
%{
    #include <stdio.h>
    #include <ctype.h>
%}
%token DIGIT

%%
//$$    $1   $2
line : expr '\n' { printf("%d\n", $1); }
     ;
expr : expr '+' term { $$ = $1 + $3; }
    | term { $$ = $1 } // <- default
    ;
term : term '*' term { $$ = $1 * $3; }
    | factor
    ;
factor : DIGIT { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
    ;

%%

int yylex(void) {
  int c;
  c = getchar();
  if (isdigit(c)) {
    yylval = c - '0';
    return DIGIT;
  }
  return c;
}

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}

int main() {
  yyparse();
  return 0;
}

______________________________________


// Ambigous grammar

____________________
%left '+' '-'         | higher priority
%left '*' '/'         v
%right UMINUS
%nonassoc '<'
%%

...

expr :   expr '+' expr { $$ = $1 + $3; }
       | expr '-' expr { $$ = $1 - $3; }
       | expr '*' expr { $$ = $1 * $3; }
       | expr '/' expr { $$ = $1 * $3; }
       | '(' expr ')' { $$ = $2; }
       | '-' expr %prec UMINUS { $$ = -$2; }
___________________________                 









