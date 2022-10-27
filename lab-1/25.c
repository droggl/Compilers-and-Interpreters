/* The program from Aho, Sethi, Ullman section 2.5 */
/* Without the optimizations on page 52-53 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int lookahead;

void error() {
  printf("syntax error\n");
  exit(EXIT_FAILURE);
}

void match(int t) {
  if (lookahead == t)
    lookahead = getchar();
  else
    error();
}

void term () {
  if (isdigit(lookahead)) {
    putchar(lookahead);
    match(lookahead);
  }
  else
    error();
}

void rest() {
  if (lookahead == '+') {
    match('+'); term(); putchar('+'); rest();
  }
  else if (lookahead == '-') {
    match('-'); term(); putchar('-'); rest();
  }
  else
    ;
}

void expr() {
  term(); rest();
}

int main(void) {
  lookahead = getchar();
  expr();
  putchar('\n');
  return EXIT_SUCCESS;
}
