#include <stdio.h>
#include <math.h>

int isPrime(int a);

int main() {
    int x, i;
    int sum = 0;
    scanf("%d", &x);
    
    for (i = 2; i <= x; i++) {
        if (isPrime(i)) {
            sum += i;
        }
    }
    
    printf("%d", sum);
    return 0;
}

int isPrime(int a) {
    if (a == 1) return 0;
    if (a == 2 || a == 3) return 1;
    if (a % 2 == 0) return 0;
    
    for (int i = 3; i <= sqrt(a); i += 2) {
        if (a % i == 0) return 0;
    }
    
    return 1;
}
