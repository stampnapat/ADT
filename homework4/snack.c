#include <stdio.h>
#define MAX 1e7
#define MIN(a,b) (a) < (b) ? (a) : (b)

int main() {
    int m;
    scanf("%d", &m);
    int price[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &price[i]);
    }

    int v;
    scanf("%d", &v);
    int dp[v + 1];

    for (int i = 0; i <= v; i++) {
        dp[i] = MAX;
    }
    dp[0] = 0;

    for (int i = 0; i < m; i++) {
        int p = price[i];
        for (int j = p; j <= v; j++) {
            if (dp[j - p] != MAX) {
                dp[j] = MIN(dp[j], dp[j - p] + 1);
            }
        }
    }

    for (int i = v; i >= 0; i--) {
        if (dp[i] != MAX) {
            printf("%d", dp[i]);
            break;
        }
    }

    return 0;
}

