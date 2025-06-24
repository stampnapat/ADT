#include <stdio.h>

int main() {
  int x, y, day, hour;
  scanf("%d %d", &x, &y);
  day = (x + y) / 24;
  hour = (x + y) % 24;
  printf("%d %d", day ,hour);
  


}
