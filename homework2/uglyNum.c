#include <stdio.h>
#include <math.h>

int ugly(unsigned int a) {
    if (a == 0) return 0;
    if (a == 1) return 1;
    while (1) {
        if (a%2 == 0) a /= 2;
        else if (a%3 == 0) a /= 3;
        else if (a%5 == 0) a /= 5;
        else break;
    }
    if (a == 1) return 1;
    else return 0;
}

int main() {
    unsigned int n;
    scanf("%u", &n);
    printf("%d", ugly(n));
    return 0;
}
