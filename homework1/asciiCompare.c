#include <stdio.h>
#include <stdlib.h>

int main() {
  char a, b;
  scanf("%c %c", &a, &b);
  int ascii_a = (int) a;
  int ascii_b = (int) b;

  printf("%d", abs(ascii_a - ascii_b));
    return 0;

}
