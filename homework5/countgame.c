#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct player {
    int id;
    int limit;
    int drink_count;
} player;

bool should_drink(int number, int k) {
    if (number % k == 0) {
        return true;
    }
    int temp_num = number;
    while (temp_num > 0) {
        if (temp_num % 10 == k) {
            return true;
        }
        temp_num /= 10;
    }
    return false;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int *score = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &score[i]);
    }

    player *players = malloc(sizeof(player) * n);
    for (int i = 0; i < n; i++) {
        players[i].id = i + 1;
        players[i].limit = score[i];
        players[i].drink_count = 0;
    }

    int player_count = n;
    int count = 0;
    int index = 0;

    while (player_count > 1) {
        count++;

        if (should_drink(count, k)) {
            players[index].drink_count++;

            if (players[index].drink_count > players[index].limit) {
                for (int j = index; j < player_count - 1; j++) {
                    players[j] = players[j + 1];
                }
                player_count--;

                if (index >= player_count) {
                    index = 0;
                }
                continue;
            }
        }

        index++;
        if (index >= player_count) {
            index = 0;
        }
    }

    if (player_count > 0) {
        printf("%d\n", players[0].id);
    }

}
