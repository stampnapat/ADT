#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE 100001

int toDecimal(char arr[],int m);
void base(int total,int n);

int main() {
  int m, n;
  char arr[SIZE];

  scanf("%d %d", &m, &n);
  scanf("%s", arr);
  //printf("%d\n", toDecimal(arr, m));
  //printf("%d",base(toDecimal(arr, m), n));
  base(toDecimal(arr,m),n);

  return 0;
}

int toDecimal(char arr[],int m){
  int size = strlen(arr);
  int total = 0, s=0;

  for (int i = size-1; i>=0; i--){
      int str = 0;
      if (arr[i] >= '0' && arr[i] <= '9'){
        str = arr[i]-'0';
        str = arr[i]-'0';
        total += str*pow(m,s);
      }
      else {
        str = arr[i]-'A'+10;
        total += str*pow(m,s);
      }
      s += 1;
  }
  return total;

}

void base(int total,int n){
  int sum = 0;
  int s = 1;
  int index = 0;
  char temp[SIZE];

  while (total>0){
    int digit = total % n;
   if (digit<10) temp[index++] = digit + '0';
   else temp[index++] = digit - 10 + 'A';
   total /=n;
  }

  for (int i=index-1; i>=0; i--){
    printf("%c", temp[i]);

  }
}

