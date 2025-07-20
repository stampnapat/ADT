#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  int item[n];
  int arr[n];
  int index_good = 0, index_bad = 0;
  for (int i = 0; i < n; i++) {
    scanf("%d", &item[i]);
  }
  for (int i = 0; i < n; i++) {
    if (item[i] > 0) {
      arr[index_good++] = item[i];
    }
  }
  for (int i = 0; i < n; i++) {
    if (item[i] == -1 || item[i] == -2) {
      arr[index_good + index_bad] = item[i];
      index_bad++;
    }
  }
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}

