#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 200005

struct node {
    int to;
    struct node* next;
};

struct node* adj[MAX_NODES];
char present[MAX_NODES];
int state_[MAX_NODES];
int stack_node[MAX_NODES * 2];
int stack_par[MAX_NODES * 2];
char stack_stage[MAX_NODES * 2];

void add_edge(int u, int v) {
    struct node* a = (struct node*)malloc(sizeof(struct node));
    a->to = v; a->next = adj[u]; adj[u] = a;
    struct node* b = (struct node*)malloc(sizeof(struct node));
    b->to = u; b->next = adj[v]; adj[v] = b;
}

int main() {
    int E;
    if (scanf("%d", &E) != 1) return 0;

    for (int i = 0; i < MAX_NODES; i++) {
        adj[i] = NULL;
        present[i] = 0;
        state_[i] = -1;
    }

    int u, v, max_id = 0;
    for (int i = 0; i < E; i++) {
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        present[u] = present[v] = 1;
        if (u > max_id) max_id = u;
        if (v > max_id) max_id = v;
    }

    int towers = 0;

    for (int root = 0; root <= max_id; root++) {
        if (!present[root] || state_[root] != -1) continue;

        int top = 0;
        stack_node[top]   = root;
        stack_par[top]    = -1;
        stack_stage[top]  = 0;
        top++;

        while (top > 0) {
            top--;
            int x = stack_node[top];
            int p = stack_par[top];
            char stg = stack_stage[top];

            if (stg == 0) {
                stack_node[top]   = x;
                stack_par[top]    = p;
                stack_stage[top]  = 1;
                top++;

                struct node* it = adj[x];
                while (it) {
                    int y = it->to;
                    if (y != p) {
                        stack_node[top]   = y;
                        stack_par[top]    = x;
                        stack_stage[top]  = 0;
                        top++;
                    }
                    it = it->next;
                }
            } else {
                int child_has_tower = 0;
                int child_needs_cover = 0;

                struct node* it = adj[x];
                while (it) {
                    int y = it->to;
                    if (y != p) {
                        if (state_[y] == 1) child_has_tower = 1;
                        else if (state_[y] == 0) child_needs_cover = 1;
                    }
                    it = it->next;
                }

                if (child_needs_cover) {
                    state_[x] = 1;
                    towers++;
                } else if (child_has_tower) {
                    state_[x] = 2;
                } else {
                    state_[x] = 0;
                }
            }
        }

        if (state_[root] == 0) {
            towers++;
            state_[root] = 1;
        }
    }

    printf("%d\n", towers);
    return 0;
}

