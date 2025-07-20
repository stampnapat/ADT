#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);
  int arr[20001] = {0};
  int boolean = 0;

  for (int i = 0; i < n; i++) {
    int temp;
    scanf("%d", &temp);
    if (arr[temp + 10000] == 1) boolean = 1;
    arr[temp + 10000] = 1;
  }
  printf("%d", boolean);
  return 0;
}

