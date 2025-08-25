#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *parent;
    struct node *first_child;
    struct node *next_sibling;
} node_t;

typedef node_t tree_t;

typedef struct q_node {
    node_t *tree_node;
    struct q_node *next;
} q_node_t;

typedef struct queue {
    q_node_t *front;
    q_node_t *rear;
} queue_t;

queue_t* create_queue() {
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

void enqueue(queue_t *q, node_t *node) {
    q_node_t *new_node = (q_node_t*)malloc(sizeof(q_node_t));
    new_node->tree_node = node;
    new_node->next = NULL;
    if (q->rear == NULL) {
        q->front = new_node;
        q->rear = new_node;
    } else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

node_t* dequeue(queue_t *q) {
    if (q->front == NULL) {
        return NULL;
    }
    q_node_t *temp = q->front;
    node_t *tree_node = temp->tree_node;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return tree_node;
}

int is_empty(queue_t *q) {
    if(q->front == NULL) {
        return 1;
    }
    return 0;
}

node_t* create_node(int data) {
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->parent = NULL;
    new_node->first_child = NULL;
    new_node->next_sibling = NULL;
    return new_node;
}

node_t* find_node(tree_t* t, int data) {
    if (t == NULL) {
        return NULL;
    }
    if (t->data == data) {
        return t;
    }

    node_t *found = find_node(t->first_child, data);
    if (found != NULL) {
        return found;
    }

    return find_node(t->next_sibling, data);
}

void free_subtree(node_t *node) {
    if (node == NULL) {
        return;
    }
    node_t *child = node->first_child;
    while (child != NULL) {
        node_t *next = child->next_sibling;
        free_subtree(child);
        child = next;
    }
    free(node);
}

tree_t* attach(tree_t *t, int parent, int child) {
    tree_t *child_node = create_node(child);
    if (parent == -1) {
        if (t != NULL) {
            free_subtree(t);
        }
        return child_node;
    }
    tree_t *parent_node = find_node(t, parent);
    if (parent_node == NULL) {
        free(child_node);
        return t;
    }
    child_node->parent = parent_node;
    if (parent_node->first_child == NULL) {
        parent_node->first_child = child_node;
    } else {
        tree_t *curr = parent_node->first_child;
        while (curr->next_sibling != NULL) {
            curr = curr->next_sibling;
        }
        curr->next_sibling = child_node;
    }
    return t;
}

tree_t* detach(tree_t *t, int data) {
    node_t *target = find_node(t, data);
    if (target == NULL) {
        return t;
    }
    if (target == t) {
        free_subtree(t);
        return NULL;
    }
    node_t *p = target->parent;
    if (p->first_child == target) {
        p->first_child = target->next_sibling;
    } else {
        node_t *prev = p->first_child;
        while (prev->next_sibling != target) {
            prev = prev->next_sibling;
        }
        prev->next_sibling = target->next_sibling;
    }
    free_subtree(target);
    return t;
}

int search(tree_t* t, int data) {
    if (find_node(t, data) != NULL) {
        return 1;
    } else {
        return 0;
    }
}

int degree(tree_t *t, int data) {
    int count = 0;
    tree_t *node = find_node(t, data);
    if (node == NULL) {
        return 0;
    }
    tree_t *curr = node->first_child;
    while (curr != NULL) {
        count++;
        curr = curr->next_sibling;
    }
    return count;
}

int is_root(tree_t *t, int data) {
    if (t == NULL) {
        return 0;
    }
    if (t->data == data) {
        return 1;
    }
    return 0;
}

int is_leaf(tree_t *t, int data) {
    tree_t *node = find_node(t, data);
    if (node == NULL) {
        return 0;
    }
    if (node->first_child == NULL) {
        return 1;
    }
    return 0;
}

void siblings(tree_t *t, int data) {
    tree_t *node = find_node(t, data);
    if (node == NULL || node->parent == NULL) {
        printf("\n");
        return;
    }
    tree_t *p = node->parent;
    tree_t *child = p->first_child;
    int flag = 0;
    while (child != NULL) {
        if (child != node) {
            if (flag == 1) {
                printf(" ");
            }
            printf("%d", child->data);
            flag = 1;
        }
        child = child->next_sibling;
    }
    printf("\n");
}

int depth(tree_t *t, int data) {
    tree_t *node = find_node(t, data);
    if (node == NULL) {
        return -1;
    }
    int d = 0;
    while (node->parent != NULL) {
        d++;
        node = node->parent;
    }
    return d;
}

void print_path(tree_t *t, int start, int end) {
    node_t *end_node = find_node(t, end);
    if (end_node == NULL) {
        printf("\n");
        return;
    }
    int path[1000];
    int i = 0;
    node_t *curr = end_node;
    while (curr != NULL) {
        path[i] = curr->data;
        i++;
        if (curr->data == start) {
            break;
        }
        curr = curr->parent;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", path[j]);
        if (j > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int path_length(tree_t *t, int start, int end) {
    node_t *end_node = find_node(t, end);
    if (end_node == NULL) {
        return 0;
    }
    int length = 0;
    node_t *curr = end_node;
    while (curr != NULL) {
        length++;
        if (curr->data == start) {
            break;
        }
        curr = curr->parent;
    }
    return length;
}

void ancestor(tree_t *t, int node) {
    node_t *start_node = find_node(t, node);
    if (start_node == NULL) {
        printf("\n");
        return;
    }
    int path[1000];
    int i = 0;
    node_t *curr = start_node;
    while (curr != NULL) {
        path[i] = curr->data;
        i++;
        curr = curr->parent;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", path[j]);
        if (j > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void descendant(tree_t *t, int node) {
    node_t *start_node = find_node(t, node);
    if (start_node == NULL) {
        printf("\n");
        return;
    }
    queue_t *q = create_queue();
    enqueue(q, start_node);
    int first = 1;
    while (!is_empty(q)) {
        node_t *curr = dequeue(q);
        if (first == 0) {
            printf(" ");
        }
        printf("%d", curr->data);
        first = 0;
        node_t *child = curr->first_child;
        while (child != NULL) {
            enqueue(q, child);
            child = child->next_sibling;
        }
    }
    free(q);
    printf("\n");
}

void bfs(tree_t *t) {
    if (t == NULL) {
        printf("\n");
        return;
    }
    queue_t *q = create_queue();
    enqueue(q, t);
    int first = 1;
    while (!is_empty(q)) {
        node_t *curr = dequeue(q);
        if (first == 0) {
            printf(" ");
        }
        printf("%d", curr->data);
        first = 0;
        node_t *child = curr->first_child;
        while (child != NULL) {
            enqueue(q, child);
            child = child->next_sibling;
        }
    }
    free(q);
    printf("\n");
}

void dfs_recursive(node_t *node, int *first) {
    if (node == NULL) {
        return;
    }
    if (*first == 0) {
        printf(" ");
    }
    printf("%d", node->data);
    *first = 0;
    node_t *child = node->first_child;
    while (child != NULL) {
        dfs_recursive(child, first);
        child = child->next_sibling;
    }
}

void dfs(tree_t *t) {
    int first = 1;
    dfs_recursive(t, &first);
    printf("\n");
}

void print_tree_recursive(node_t *node, int level) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < level * 4; i++) {
        printf(" ");
    }
    printf("%d\n", node->data);
    node_t *child = node->first_child;
    while (child != NULL) {
        print_tree_recursive(child, level + 1);
        child = child->next_sibling;
    }
}

void print_tree(tree_t *t) {
    print_tree_recursive(t, 0);
}

int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d %d", &parent, &child);
                t = attach(t, parent, child);
                break;
            case 2:
                scanf("%d", &node);
                t = detach(t, node);
                break;
            case 3:
                scanf("%d", &node);
                printf("%d\n", search(t, node));
                break;
            case 4:
                scanf("%d", &node);
                printf("%d\n", degree(t, node));
                break;
            case 5:
                scanf("%d", &node);
                printf("%d\n", is_root(t, node));
                break;
            case 6:
                scanf("%d", &node);
                printf("%d\n", is_leaf(t, node));
                break;
            case 7:
                scanf("%d", &node);
                siblings(t, node);
                break;
            case 8:
                scanf("%d", &node);
                printf("%d\n", depth(t, node));
                break;
            case 9:
                scanf("%d %d", &start, &end);
                print_path(t, start, end);
                break;
            case 10:
                scanf("%d %d", &start, &end);
                printf("%d\n", path_length(t, start, end));
                break;
            case 11:
                scanf("%d", &node);
                ancestor(t, node);
                break;
            case 12:
                scanf("%d", &node);
                descendant(t, node);
                break;
            case 13:
                bfs(t);
                break;
            case 14:
                dfs(t);
                break;
            case 15:
                print_tree(t);
                break;
        }
    }
    return 0;
}
