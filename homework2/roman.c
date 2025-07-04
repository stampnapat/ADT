#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  for (int i=0; i<n;i++){
    int number;
    int count=0;
    scanf("%d", &number);
    int base = number;
    while ( base != 0){
      base /= 10;
      count +=1 ;
    }
    for (int j=count; j>0;j--){
      if (j==4){
        int four = number/1000;
        if (four == 3) printf("MMM");
        else if (four == 2) printf("MM");
        else if (four == 1) printf("M");
      }else if (j==3){
        int three = number/100%10;
        if (three==1) printf("C");
        else if (three==2) printf("CC");
        else if (three==3) printf("CCC");
        else if (three==4) printf("CD");
        else if (three==5) printf("D");
        else if (three==6) printf("DC");
        else if (three==7) printf("DCC");
        else if (three==8) printf("DCCC");
        else if (three==9) printf("CM");
      }else if (j==2){
        int two = number/10%10;
        if (two==1) printf("X");
        else if (two==2) printf("XX");
        else if (two==3) printf("XXX");
        else if (two==4) printf("XL");
        else if (two==5) printf("L");
        else if (two==6) printf("LX");
        else if (two==7) printf("LXX");
        else if (two==8) printf("LXXX");
        else if (two==9) printf("XC");
      }else if (j==1){
        int one = number%10;
        if (one==1) printf("I");
        else if (one==2) printf("II");
        else if (one==3) printf("III");
        else if (one==4) printf("IV");
        else if (one==5) printf("V");
        else if (one==6) printf("VI");
        else if (one==7) printf("VII");
        else if (one==8) printf("VIII");
        else if (one==9) printf("IX");
      }
    }
    printf("\n");
  }
  return 0;
}
