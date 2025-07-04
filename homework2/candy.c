#include <stdio.h>

int main() {
    int m, p, w;
    int sum, count;

    scanf("%d %d %d", &m, &p, &w);
    count = m / p;
    sum = count;

    while (count >= w) {
        int new_bottles = count / w;
        int remain = count % w;
        sum += new_bottles;
        count = new_bottles + remain;
        printf("count %d\n", count);
    }

    printf("%d", sum);
    return 0;
}
