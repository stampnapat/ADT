#include <stdio.h>
#include <string.h>
#define SIZE 100001

int main() {
    char words[SIZE];
    scanf("%[^\n]%*c", words);

    int size = strlen(words);
    char new_arr[30000][50];
    int word_index = 0;
    int char_index = 0;

    for (int i = 0; i <= size; i++) {
        if (words[i] != ' ' && words[i] != '\0') {
            new_arr[word_index][char_index++] = words[i];
        } else {
            new_arr[word_index][char_index] = '\0';  // ปิดคำ
            word_index++;
            char_index = 0;
        }
    }

    // พิมพ์คำย้อนลำดับ
    for (int j = word_index - 1; j >= 0; j--) {
        printf("%s ", new_arr[j]);
    }
    printf("\n");
    return 0;
}

