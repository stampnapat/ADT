#include <stdio.h>
#include <stdlib.h>

// โครงสร้างของโหนด (เหมือนเดิม)
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// --- ฟังก์ชันทั้งหมดของ AVL Tree (เหมือนเดิม) ---
int max(int a, int b) { return (a > b) ? a : b; }
int height(struct Node *n) { return (n == NULL) ? 0 : n->height; }

struct Node* newNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(struct Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return(newNode(key));
    if (key < node->key) node->left = insert(node->left, key);
    else if (key > node->key) node->right = insert(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void preOrder(struct Node *root) {
    if(root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
// --- สิ้นสุดส่วนฟังก์ชันของ AVL Tree ---


// ✅ ส่วนโปรแกรมหลักที่ปรับปรุงใหม่
int main() {
    struct Node *root = NULL;
    int num;

    printf("โปรแกรม AVL Tree: ป้อนตัวเลขเพื่อเพิ่มลงในต้นไม้\n");
    printf("=============================================\n");

    // วนรับค่าไปเรื่อยๆ จนกว่าจะเจอ -1
    while (1) {
        printf("ป้อนตัวเลข (ใส่ -1 เพื่อสิ้นสุด): ");
        scanf("%d", &num);

        // ถ้าผู้ใช้ป้อน -1 ให้ออกจาก loop
        if (num == -1) {
            break;
        }

        // เพิ่มค่าที่รับเข้ามาลงใน AVL Tree
        root = insert(root, num);
        printf("  >> เพิ่ม %d ลงในต้นไม้แล้ว | โครงสร้างปัจจุบัน (Preorder): ", num);
        preOrder(root);
        printf("\n");
    }

    printf("\n--- สิ้นสุดการทำงาน ---\n");
    printf("ผลลัพธ์สุดท้ายของต้นไม้ (Preorder Traversal):\n");
    preOrder(root);
    printf("\n");

    return 0;
}
