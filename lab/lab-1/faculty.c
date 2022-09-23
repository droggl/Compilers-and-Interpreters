#include <stdio.h>

#define FACTORIAL(n) (n==0 ? 1 : n*FACTORIAL(n-1))

int factorial(int n) {
  if (n == 0)
    return 1;
  else
    return n * factorial(n - 1);
}

int main() {
  int num;
  scanf("%d", &num);
  
  printf("%d", FACTORIAL(3));

  return 0;
}
