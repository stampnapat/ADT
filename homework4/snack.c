#include <stdio.h>

int find_max(int price[], int m) {
  int max_p = 0;
  int index = 0;
  for (int i = 0; i < m; i++) {
    if (price[i] > max_p) {
      index = i;
      max_p = price[i];
    }
  }
  price[index] = 0;
  return max_p;
}

int main() {
  int m, v;
  scanf("%d", &m);
  int price[m];
  int count = 0, piece = 0;
  for (int i = 0; i < m; i++) {
    scanf("%d", &price[i]);
  }
  scanf("%d", &v);
  while (count++ < m && v > 0) {
    int value_max = find_max(price, m);
    if (value_max == 0) break;
    while (v >= value_max && value_max > 0) {
      v -= value_max;
      piece++;
    }
  }
  printf("%d", piece);
  return 0;
}

