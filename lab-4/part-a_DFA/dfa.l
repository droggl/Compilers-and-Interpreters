/* dfa.lex */

%{
    #include <stdio.h>

    extern void switch_state();
    int state = 1;
    typedef enum {A, B, ELSE} letter;
%}

%option noyywrap

%%

[ \t]+    { /* ignore whitespace */ }
\n        { printf("%d\n", state); }
a         { switch_state(A); }
b         { switch_state(B);}
.         { switch_state(ELSE); } // val = atoi(yytext);

%%

void switch_state(letter x) {
    if (state == 1) {
        switch (x) {
        case A:
            state = 2;
            break;
        default:
            state = 4;
        break;
        }
    } else if (state == 2) {
        switch(x) {
        case A:
            state = 3;
            break;
        case B:
            state = 1;
            break;
        default:
            state = 3;
        }
    }
}

int main() {
    yylex();
    return 0;
}