#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  scanf("%d", &n);

  int *arr = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  int max_area = 0;
  int i = 0;
  int *stack = (int *)malloc(n * sizeof(int));
  int top = -1;

  while (i < n) {
    if (top == -1 || arr[i] >= arr[stack[top]]) {
      stack[++top] = i++;
    } else {
      int pop = stack[top--];
      int width = (top == -1) ? i : i - stack[top] - 1;
      int area = arr[pop] * width;
      if (area > max_area) max_area = area;
    }
  }

  while (top != -1) {
    int pop = stack[top--];
    int width = (top == -1) ? i : i - stack[top] - 1;
    int area = arr[pop] * width;
    if (area > max_area) max_area = area;
  }
  printf("%d\n", max_area);

}
