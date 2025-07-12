#include <stdio.h>
#include <string.h>
#define SIZE 100001

int main() {
    char arr[SIZE];
    scanf("%s", arr);
    int len = strlen(arr);
    char store[len];
    int start_index, last_index = 0;

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            int left_side = i;
            int right_side = j;
            int duplicate = 1;

            while (right_side > left_side) {
                if (arr[right_side] != arr[left_side]) {
                    duplicate = 0;
                    break;
                }
                left_side++;
                right_side--;
            }

            if (duplicate) {
                if (last_index < (j - i + 1)) {
                    start_index = i;
                    last_index = j - i + 1;
                }
            }
        }
    }

    for (int i = start_index; i < start_index + last_index; i++) {
        printf("%c", arr[i]);
    }
    printf("\n");

    return 0;
}

