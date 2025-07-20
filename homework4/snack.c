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
  for (int i = 0; i < m-1;i++) {
    for (int j = i+1; j<m;j++) {
        if (price[i] < price[j] ) {
            int temp = price[i];
            price[i] = price[j];
            price[j] = temp;
        }
    }
  }

  for (int i = 0; i < m; i++) {
        while (v >= price[i]) {
            v -= price[i];
            count++;
        }
  }
  printf("%d", piece);
  return 0;
}
