#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void findSD(int n,int *nums, double *r) {
  float sum = 0, mean = 0, sigma = 0;
  for (int i = 0; i<n; i++){
    mean += nums[i];
  }
  mean = mean/n;

  for (int i = 0; i<n; i++){
    sigma += (nums[i] - mean)* (nums[i] - mean);
  }

  *r   = sqrt(sigma/n);

}

int main() {
  int n, i;
  double sigma;
  int *nums;

  scanf("%d", &n);
  nums = (int *)malloc(sizeof(int) *n);
  for (i=0; i<n; i++)
    scanf("%d", nums+i);
  findSD(n, nums, &sigma);
  printf("%.2f", sigma);
  //for (i=0; i<n; i++) printf("index %d = %d\n", i, nums[i]);


  return 0;
}

