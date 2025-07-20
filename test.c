#include <stdio.h>

int main() {
  char str[] = "hellos\0123";
  printf("%s\n", str);
  return 0;
}
