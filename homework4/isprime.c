#include <stdio.h>
#include <math.h>

int isPrime(int n) {
  if (n == 1) return 0;
  if (n == 2 || n == 3) return 1;
  if (n % 2 == 0) return 0;
  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

int main() {
  int n;
  scanf("%d", &n);
  printf("%d", isPrime(n));
  return 0;
}

