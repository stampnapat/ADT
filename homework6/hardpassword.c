int main() {
    char *password = (char*)malloc(sizeof(char) * 1000);
    scanf("%s", password);

    int size = strlen(password);

    if (password[size - 1] != 'y') {
        printf("0\n");
        free(password);
        return 0;
    }

    int x_pos = -1;
    for (int i = 0; i < size; i++) {
        if (password[i] == 'x') {
            x_pos = i;
            break;
        }
    }

    if (x_pos == -1 || x_pos >= size - 2) {
        printf("0\n");
        return 0;
    }

    int a_len = x_pos;
    int b_len = size - x_pos - 2;

    char *A = (char*)malloc(sizeof(char) * (a_len + 1));
    char *B = (char*)malloc(sizeof(char) * (b_len + 1));

    strncpy(A, password, a_len);
    A[a_len] = '\0';

    strncpy(B, password + x_pos + 1, b_len);
    B[b_len] = '\0';

    for (int i = 0; i < a_len; i++) {
        if (A[i] == 'x' || A[i] == 'y') {
            printf("0\n");
           return 0;
        }
    }
    for (int i = 0; i < b_len; i++) {
        if (B[i] == 'x' || B[i] == 'y') {
            printf("0\n");
           return 0;
        }
    }

    int is_reverse = 1;
    for (int i = 0; i < a_len; i++) {
        if (A[i] != B[b_len - 1 - i]) {
            is_reverse = 0;
            break;
        }
    }

    printf("%d\n", is_reverse);

    return 0;
}
