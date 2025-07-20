#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  int arr[n];
  int boolean = 1, first_index = 0, last_index = n - 1;
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }
  while (first_index < last_index) {
    if (arr[first_index] != arr[last_index]) {
      boolean = 0;
      break;
    }
    first_index++;
    last_index--;
  }
  printf("%d", boolean);
  return 0;
}

