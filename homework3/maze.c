#include <stdio.h>

int traverseMaze(int n, char arr[n][n], int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n) return 0;
    if (arr[x][y] == 'G') return 1;
    if (arr[x][y] == '#' || arr[x][y] == '.') return 0;

    if (arr[x][y] != 'S' && arr[x][y] != 'G') arr[x][y] = '.';

    if (traverseMaze(n, arr, x + 1, y)) return 1;
    if (traverseMaze(n, arr, x - 1, y)) return 1;
    if (traverseMaze(n, arr, x, y + 1)) return 1;
    if (traverseMaze(n, arr, x, y - 1)) return 1;

    if (arr[x][y] == '.' && arr[x][y] != 'S' && arr[x][y] != 'G') arr[x][y] = ' ';
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();
    char arr[n][n];
    int x, y;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%c", &arr[i][j]);
            if (arr[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
        getchar();
    }

    traverseMaze(n, arr, x, y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}

