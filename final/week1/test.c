#include <stdio.h>
#include <stdlib.h>

// --- Data Structures ---

// โครงสร้างของโหนดในต้นไม้
// เพิ่ม parent pointer เพื่อให้ง่ายต่อการทำงานของฟังก์ชันอื่นๆ
typedef struct node {
    int data;                 // ข้อมูลของโหนด
    struct node *parent;      // ตัวชี้ไปยังโหนดพ่อแม่
    struct node *firstChild;  // ตัวชี้ไปยังโหนดลูกตัวแรก
    struct node *nextSibling; // ตัวชี้ไปยังโหนดพี่น้องตัวถัดไป
} node_t;

// กำหนดให้ tree_t เป็นตัวชี้ไปยังรากของต้นไม้
typedef node_t tree_t;

// โครงสร้างของโหนดในคิว (สำหรับ BFS)
typedef struct q_node {
    node_t *tree_node;
    struct q_node *next;
} q_node_t;

// โครงสร้างของคิว (สำหรับ BFS)
typedef struct queue {
    q_node_t *front;
    q_node_t *rear;
} queue_t;


// --- Queue Helper Functions ---

// สร้างคิวใหม่
queue_t* create_queue() {
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    q->front = q->rear = NULL;
    return q;
}

// เพิ่มโหนดเข้าคิว
void enqueue(queue_t *q, node_t *node) {
    q_node_t *new_q_node = (q_node_t*)malloc(sizeof(q_node_t));
    new_q_node->tree_node = node;
    new_q_node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = new_q_node;
        return;
    }
    q->rear->next = new_q_node;
    q->rear = new_q_node;
}

// นำโหนดออกจากคิว
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

// ตรวจสอบว่าคิวว่างหรือไม่
int is_empty(queue_t *q) {
    return q->front == NULL;
}


// --- Tree Helper Functions ---

// ฟังก์ชันสร้างโหนดใหม่
node_t* create_node(int data) {
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) return NULL;

    new_node->data = data;
    new_node->parent = NULL;
    new_node->firstChild = NULL;
    new_node->nextSibling = NULL;
    return new_node;
}

// ฟังก์ชันช่วยค้นหาโหนดที่มีค่าที่ต้องการ (ใช้การท่องแบบ pre-order/DFS)
node_t* find_node(tree_t *t, int value) {
    if (t == NULL) {
        return NULL;
    }
    if (t->data == value) {
        return t;
    }
    // ค้นหาในต้นไม้ย่อยของลูกตัวแรก
    node_t *found = find_node(t->firstChild, value);
    if (found != NULL) {
        return found;
    }
    // ค้นหาในหมู่พี่น้อง
    return find_node(t->nextSibling, value);
}

// ฟังก์ชันช่วยลบโหนดและทายาททั้งหมด (ใช้การท่องแบบ post-order)
void free_subtree(node_t *node) {
    if (node == NULL) {
        return;
    }
    node_t *child = node->firstChild;
    while (child != NULL) {
        node_t *next = child->nextSibling;
        free_subtree(child);
        child = next;
    }
    free(node);
}


// --- Main Function Implementations ---

// 1. attach: เพิ่มโหนดใหม่เข้าสู่ต้นไม้
tree_t* attach(tree_t *t, int parent_val, int child_val) {
    node_t *child_node = create_node(child_val);

    // กรณีสร้างโหนดราก
    if (parent_val == -1) {
        if (t != NULL) free_subtree(t); // ลบต้นไม้เก่า (ถ้ามี)
        return child_node;
    }

    node_t *parent_node = find_node(t, parent_val);
    if (parent_node == NULL) {
        free(child_node); // ไม่พบโหนดแม่, ลบโหนดลูกที่สร้างขึ้น
        return t;
    }
    
    child_node->parent = parent_node;
    // ถ้าโหนดแม่ยังไม่มีลูก
    if (parent_node->firstChild == NULL) {
        parent_node->firstChild = child_node;
    } else {
        // หาโหนดลูกคนสุดท้ายเพื่อต่อโหนดใหม่
        node_t *sibling = parent_node->firstChild;
        while (sibling->nextSibling != NULL) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = child_node;
    }
    return t;
}

// 2. detach: นำโหนดและต้นไม้ย่อยออกจากต้นไม้หลัก
tree_t* detach(tree_t *t, int node_val) {
    node_t *node_to_detach = find_node(t, node_val);
    if (node_to_detach == NULL) {
        return t;
    }

    // กรณีนำโหนดรากออก
    if (node_to_detach == t) {
        free_subtree(t);
        return NULL;
    }

    node_t *parent = node_to_detach->parent;
    // นำโหนดออกจากรายการลูกของโหนดแม่
    if (parent->firstChild == node_to_detach) {
        parent->firstChild = node_to_detach->nextSibling;
    } else {
        node_t *prev_sibling = parent->firstChild;
        while (prev_sibling->nextSibling != node_to_detach) {
            prev_sibling = prev_sibling->nextSibling;
        }
        prev_sibling->nextSibling = node_to_detach->nextSibling;
    }
    
    free_subtree(node_to_detach);
    return t;
}

// 3. search: ค้นหาโหนดในต้นไม้ (คืนค่า 1 หรือ 0)
int search(tree_t *t, int node_val) {
    return find_node(t, node_val) != NULL;
}

// 4. degree: คืนค่าจำนวนลูกของโหนด
int degree(tree_t *t, int node_val) {
    node_t *node = find_node(t, node_val);
    if (node == NULL) {
        return 0;
    }
    int count = 0;
    node_t *child = node->firstChild;
    while (child != NULL) {
        count++;
        child = child->nextSibling;
    }
    return count;
}

// 5. is_root: ตรวจสอบว่าเป็นโหนดรากหรือไม่
int is_root(tree_t *t, int node_val) {
    if (t == NULL) {
        return 0;
    }
    return t->data == node_val;
}

// 6. is_leaf: ตรวจสอบว่าเป็นโหนดใบหรือไม่
int is_leaf(tree_t *t, int node_val) {
    node_t *node = find_node(t, node_val);
    if (node == NULL) {
        return 0;
    }
    return node->firstChild == NULL;
}

// 7. siblings: แสดงโหนดพี่น้องทั้งหมด
void siblings(tree_t *t, int node_val) {
    node_t *node = find_node(t, node_val);
    if (node == NULL || node->parent == NULL) {
        printf("\n");
        return;
    }
    node_t *parent = node->parent;
    node_t *child = parent->firstChild;
    int first = 1;
    while (child != NULL) {
        if (child->data != node_val) {
            if (!first) {
                printf(" ");
            }
            printf("%d", child->data);
            first = 0;
        }
        child = child->nextSibling;
    }
    printf("\n");
}

// 8. depth: คืนค่าความลึกของโหนด
int depth(tree_t *t, int node_val) {
    node_t *node = find_node(t, node_val);
    if (node == NULL) {
        return -1; // หรือค่าที่บ่งบอกว่าไม่พบ
    }
    int d = 0;
    while (node->parent != NULL) {
        d++;
        node = node->parent;
    }
    return d;
}

// 9. print_path: แสดงเส้นทางจากโหนดเริ่มต้นไปยังปลายทาง
void print_path(tree_t *t, int start_val, int end_val) {
    node_t *end_node = find_node(t, end_val);
    if (end_node == NULL) {
        printf("\n");
        return;
    }

    int path_arr[1000]; // สมมติว่าความลึกสูงสุดไม่เกิน 1000
    int i = 0;
    node_t *current = end_node;
    while (current != NULL) {
        path_arr[i++] = current->data;
        if (current->data == start_val) {
            break;
        }
        current = current->parent;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", path_arr[j]);
        if (j > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

// 10. path_length: คืนค่าความยาวของเส้นทาง
int path_length(tree_t *t, int start_val, int end_val) {
    node_t *end_node = find_node(t, end_val);
    if (end_node == NULL) {
        return 0;
    }
    int len = 0;
    node_t *current = end_node;
    while (current != NULL) {
        len++;
        if (current->data == start_val) {
            break;
        }
        current = current->parent;
    }
    return len;
}

// 11. ancestor: แสดงบรรพบุรุษทั้งหมด
void ancestor(tree_t *t, int node_val) {
    node_t *node = find_node(t, node_val);
    if (node == NULL) {
        printf("\n");
        return;
    }
    
    int path_arr[1000];
    int i = 0;
    node_t *current = node;
    while (current != NULL) {
        path_arr[i++] = current->data;
        current = current->parent;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", path_arr[j]);
        if (j > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

// 12. descendant: แสดงทายาททั้งหมด (ใช้ BFS)
void descendant(tree_t *t, int node_val) {
    node_t *start_node = find_node(t, node_val);
    if (start_node == NULL) {
        printf("\n");
        return;
    }
    
    queue_t *q = create_queue();
    enqueue(q, start_node);
    int first = 1;
    
    while (!is_empty(q)) {
        node_t *current = dequeue(q);
        if (!first) {
            printf(" ");
        }
        printf("%d", current->data);
        first = 0;
        
        node_t *child = current->firstChild;
        while (child != NULL) {
            enqueue(q, child);
            child = child->nextSibling;
        }
    }
    free(q);
    printf("\n");
}

// 13. bfs: แสดงโหนดทั้งหมดแบบ Breadth First Search
void bfs(tree_t *t) {
    if (t == NULL) {
        printf("\n");
        return;
    }
    
    queue_t *q = create_queue();
    enqueue(q, t);
    int first = 1;
    
    while (!is_empty(q)) {
        node_t *current = dequeue(q);
        if (!first) {
            printf(" ");
        }
        printf("%d", current->data);
        first = 0;
        
        node_t *child = current->firstChild;
        while (child != NULL) {
            enqueue(q, child);
            child = child->nextSibling;
        }
    }
    free(q);
    printf("\n");
}

// ฟังก์ชันช่วยสำหรับ dfs (pre-order)
void dfs_recursive(node_t *node, int *first) {
    if (node == NULL) {
        return;
    }
    
    if (!(*first)) {
        printf(" ");
    }
    printf("%d", node->data);
    *first = 0;
    
    node_t *child = node->firstChild;
    while (child != NULL) {
        dfs_recursive(child, first);
        child = child->nextSibling;
    }
}

// 14. dfs: แสดงโหนดทั้งหมดแบบ Depth First Search
void dfs(tree_t *t) {
    int first = 1;
    dfs_recursive(t, &first);
    printf("\n");
}

// ฟังก์ชันช่วยสำหรับ print_tree
void print_tree_recursive(node_t *node, int level) {
    if (node == NULL) {
        return;
    }
    
    for (int i = 0; i < level * 4; i++) {
        printf(" ");
    }
    printf("%d\n", node->data);
    
    node_t *child = node->firstChild;
    while (child != NULL) {
        print_tree_recursive(child, level + 1);
        child = child->nextSibling;
    }
}

// 15. print_tree: แสดงโครงสร้างต้นไม้
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

