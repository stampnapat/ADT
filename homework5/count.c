#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int gd;  // good deed value
    int personal_count;
} Player;

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int *good_deeds = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &good_deeds[i]);
    }

    // สร้างผู้เล่น
    Player *players = (Player *)malloc(sizeof(Player) * n);
    int player_count = n;
    for (int i = 0; i < n; i++) {
        players[i].id = i + 1;
        players[i].gd = good_deeds[i];
        players[i].personal_count = 0;
    }

    int global_count = 0;
    int current_index = 0;

    while (player_count > 1) {
        global_count++;
        current_index = (current_index - 1 + player_count) % player_count;

        Player *current = &players[current_index];

        if (global_count % current->gd == 0) {
            current->personal_count++;

            if (current->personal_count == k) {
                // ลบผู้เล่นออก
                for (int j = current_index; j < player_count - 1; j++) {
                    players[j] = players[j + 1];
                }
                player_count--;
                // current_index ไม่เปลี่ยนเพราะตำแหน่งถัดไปเลื่อนมาแทน
                continue;
            }
        }
    }

    printf("%d\n", players[0].id);

    free(players);
    free(good_deeds);
    return 0;
}

