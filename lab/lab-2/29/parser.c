/* parser.c -- without the optimizations */

#include "global.h"

int lookahead;

void match(int);
void start(), list(), assignment(), expr(), moreterms(), term(), morefactors(), exponential(), moreexponential(), factor();

void parse()  /*  parses and translates expression list  */
{
    lookahead = lexan();
    start();
}

void start ()
{
    /* Just one production for start, so we don't need to check lookahead */
    list(); match(DONE);
}

void list()
{
    if (lookahead == ID) {
        assignment(); match(';'); list();
    }
    else {
        /* Empty */
    }
}

void assignment()
{
    if (lookahead == ID) {
        int id_number = token_value;
        match(ID); emit(ID, id_number);
        match('=');
        expr();
        emit('=', token_value);
    } else {
        error ("syntax error in assignment");
    }
}

void expr ()
{
    /* Just one production for expr, so we don't need to check lookahead */
    term(); moreterms();
}

void moreterms()
{
    if (lookahead == '+') {
        match('+'); term(); emit('+', token_value); moreterms();
    }
    else if (lookahead == '-') {
        match('-'); term(); emit('-', token_value); moreterms();
    }
    else {
        /* Empty */
    }
}

void term ()
{
    /* Just one production for term, so we don't need to check lookahead */
    exponential(); morefactors();
}

void morefactors ()
{
    if (lookahead == '*') {
        match('*'); exponential(); emit('*', token_value); morefactors();
    }
    else if (lookahead == '/') {
        match('/'); exponential(); emit('/', token_value); morefactors();
    }
    else if (lookahead == DIV) {
        match(DIV); exponential(); emit(DIV, token_value); morefactors();
    }
    else if (lookahead == MOD) {
        match(MOD); exponential(); emit(MOD, token_value); morefactors();
    }
    else {
        /* Empty */
    }
}

void exponential()
{
    factor(); moreexponential();    
}

void moreexponential()
{
    if (lookahead == '^') {
        match('^');
        factor();
        emit('^', token_value);
        moreexponential();
    } else {
    }
}

void factor ()
{
    // printf("error incoming");
    // if (lookahead == '^') {
    //     match('^'); factor(); emit('^', token_value);
    // }
    // else 
    if (lookahead == '(') {
        match('('); expr(); match(')');
    }
    else if (lookahead == ID) {
        int id_number = token_value;
        match(ID);
        emit(ID, id_number);
    }
    else if (lookahead == NUM) {
        int num_value = token_value;
        match(NUM);
        emit(NUM, num_value);
    }
    else
        error("syntax error in factor");
}

void match(int t)
{
    if (lookahead == t)
        lookahead = lexan();
    else {
        printf("%d", t);
        error ("syntax error in match");
    }
}
