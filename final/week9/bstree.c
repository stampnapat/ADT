#include <stdio.h>
#include <stdlib.h>
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t bst_t;


bst_t *insert(bst_t *t, int data) {
  if (t == NULL) {
    bst_t *new_node = malloc(sizeof(bst_t));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;

  }if (data < t->data) {
    t->left = insert(t->left, data);
  }else if (data > t->data) {
    t->right = insert(t->right, data);
  }
  return t;

}

bst_t *delete(bst_t *t, int data) {
  if (t==NULL) return NULL;

  if (data < t->data){
    t->left = delete(t->left, data);
  }else if ( data > t->data){
    t->right = delete(t->right, data);
  }else {
    if (t->left == NULL && t->right == NULL) {
      free(t);
      return NULL;
    }else if (t->right ==NULL){
       bst_t *temp = t->left;
        free(t);
      return temp;
      }
    else if (t->left ==NULL){
       bst_t *temp = t->right;
        free(t);
      return temp;
    }

  else {
      bst_t *current = t->right;
      while (current&&current->left != NULL) current= current->left;
      t->data = current->data;
      t->right = delete(t->right, current->data);


    }
  }
 return t;
}


int find(bst_t *t, int target){
  if (t==NULL) return 0;
  if (t->data == target) return 1;
  if (target > t->data) return find(t->right, target);
  if (target < t->data) return find(t->left, target);

}

bst_t *fmin(bst_t *t){
  if (t==NULL) return NULL;
  if (t->left == NULL) return t;
  return fmin(t->left);
}

int find_min(bst_t *t){
  bst_t *Min = fmin(t);
  return Min->data;

}



bst_t *fmax(bst_t *t){
  if (t=NULL) return NULL;
  if (t->right == NULL) return t;
  return fmax(t->right);
}


int find_max(bst_t *t){
  bst_t *Max = fmax(t);
  return Max->data;
}

int find_k_th(bst_t *t, int k) {
    if (t == NULL) return -1;
    int left_size = 0;
    if (t->left != NULL) {
      bst_t *stack[1000];
      int top = 0;
      stack[top++] = t->left;
     while (top > 0) {
            bst_t *cur = stack[--top];
            left_size++;
            if (cur->left) stack[top++] = cur->left;
            if (cur->right) stack[top++] = cur->right;
        }

    }
    if (k == left_size + 1) return t->data;
    else if (k <= left_size) return find_k_th(t->left, k);
    else return find_k_th(t->right, k - left_size - 1);
}



int main(void) {
bst_t *t = NULL;
int n, i;
int command, data, k;
scanf("%d", &n);
for (i=0; i<n; i++) {
scanf("%d", &command);
switch (command) {
case 1:
scanf("%d", &data);
t = insert(t, data);
break;
case 2:
scanf("%d", &data);
t = delete(t, data);
break;
case 3:
scanf("%d", &data);
printf("%d\n", find(t, data));
break;
case 4:
printf("%d\n", find_min(t));
break;
case 5:
printf("%d\n", find_max(t));
break;
case 6:
scanf("%d", &k);
printf("%d\n", find_k_th(t, k));
break;
}
}
return 0;
}
