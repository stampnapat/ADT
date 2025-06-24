#include <stdio.h>

int main() {
  int x, y, time, day, hour;
  scanf("%d %d", &x, &y);
  day = (x + y) / 24;
  hour = day % 24;
  time = 0;
  printf("%d %d", day ,hour);
  


}
