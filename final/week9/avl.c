#include <stdio.h>
#include <stdlib.h>
#define __avl_tree__
#include <week9.h>
#ifndef __avl_tree__
typedef struct node {
int data;
int height;
struct node *left;
struct node *right;
} node_t;
typedef node_t avl_t;
#endif
// Write your code here
// ** Note that the print_tree() function
// has been implemented already and
// included in the week9.h header
// ...

int height (avl_t *t) {
  if (t==NULL) return 0;
  int hl = height(t->left);
  int hr = height(t->right);
  if (hl>hr) return hl+1;
  else return hr+1;

}

int Balance(avl_t *t){
  if (t ==NULL) return 0;
  int hl = height(t->left);
  int hr = height(t->right);
  int sum = hl-hr;
  return sum;

}

int max(int a, int b){
  if (a > b) return a;
  else return b;
}
  

avl_t *right_rotate(avl_t *t){
  avl_t *left = t->left;
  avl_t *temp = left->right;

  left->right = t;
  t->left = temp;

  t->height = max(height(t->left), height(t->right)) + 1;

  left->height = max(height(left->left), height(left->right)) + 1;

  return left;

}

avl_t *left_rotate(avl_t *t){
  avl_t *right = t->right;
  avl_t *temp = right->left;

  right->left = t;
  t->right = temp;

  t->height= max(height(t->left), height(t->right))+1;
  right->height = max(height(right->left), height(right->right))+1;

  return right;
}

avl_t *insert(avl_t *t, int value){
  if (t==NULL) {
    avl_t *new_node = malloc(sizeof(avl_t));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
  }if (value < t->data){
    t->left = insert(t->left, value);
  }else if (value > t->data) {
    t->right = insert(t->right, value);
  }else return t;

  t->height = 1+ max(height(t->left),height(t->right));
  int balance = Balance(t);
  avl_t *left_child = t->left; 
  avl_t *right_child = t->right; 

  if (balance > 1){
    if (value < left_child->data) return right_rotate(t);

    if (value > left_child->data){
        t->left = left_rotate(left_child);
        return right_rotate(t);
    }


  }

  if (balance < -1){
    if (value > right_child->data) return left_rotate(t);

    if (value < right_child->data){
        t->right = right_rotate(right_child);
        return left_rotate(t);
    }

  }
  return t;

    
}

avl_t *min(avl_t *t){
  avl_t *current = t;
  while (current->left!=NULL) {
  current = current->left;
  }
  return current; 

}

avl_t *delete(avl_t *t, int value){
  if (t==NULL) return t;

  if( value < t->data) {
    t->left = delete(t->left, value);
  }else if ( value > t->data) {
    t->right = delete(t->right, value);
  }else {
    if (t->left ==NULL || t->right ==NULL) {
      avl_t *temp = t->left? t->left:t->right;
      if (temp == NULL) {
        temp = t;
        t=NULL;
      }else {
        *t = *temp;
      }
    }else{ 
      avl_t *temp = min(t->right);
      t->data = temp->data;
      t->right = delete(t->right, temp->data);
    
  }

  }
  t->height = 1+ max(height(t->left),height(t->right));
  int balance = Balance(t);
  avl_t *left_child = t->left; 
  avl_t *right_child = t->right; 

  if (balance > 1){
    if (value < left_child->data) return right_rotate(t);

    if (value > left_child->data){
        t->left = left_rotate(left_child);
        return right_rotate(t);
    }


  }

  if (balance < -1){
    if (value > right_child->data) return left_rotate(t);

    if (value < right_child->data){
        t->right = right_rotate(right_child);
        return left_rotate(t);
    }

  }
  return t;



  


}







int main(void) {
avl_t *t = NULL;
int n, i;
int command, data;
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
print_tree(t);
break;
}
}
return 0;
}
