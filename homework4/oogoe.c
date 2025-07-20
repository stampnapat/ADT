#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  long long o = 3, g = 1, e = 1;
  for (int i = 2; i <= n; i++) {
    long new_o = o * o;
    long long new_g = g * o + g;
    o = new_o % 10000;
    g = new_g % 10000;
  }
  printf("%lld", g % 10000);
  return 0;
}

