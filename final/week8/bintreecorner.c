#include <stdio.h>
#include <stdlib.h>
#include <week8.h>
#ifndef __bin_tree__
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t tree_t;
#endif
// Write your code here
// ** Note that the attach() function has
// been implemented already and included
// in the week8.h header

int depth (node_t *t) {
  if (t == NULL) return 0;
  int hl = depth(t->left);
  int hr = depth(t->right);
  if (hl>hr) return hl+1;
  else return hr+1;

}

void print_level(node_t *t, int level){
  if (t==NULL) return;
  if (level == 1) printf("%d ", t->data);
  else {
    print_level(t->left, level-1);
    print_level(t->right, level-1);
  }
}

void print_right(node_t *t, int level) {
  if(t==NULL) return;
  if(level == 1) printf("%d ", t->data);
  else {
    print_right(t->right, level-1);
    print_right(t->left, level-1);
    }
  }

void printCornerNodes(node_t *t){
  int h = depth(t);
  for (int i = 1; i<=h;i++){
    print_level(t, i);
    if (i>1) {
      print_right(t, i);
      }
    printf("\n");

  }

}










int main(void) {
tree_t *t = NULL;
int n, i;
int parent, child;
int branch; // 0 root, 1 left, 2 right
scanf("%d", &n);
for (i=0; i<n; i++) {
scanf("%d %d %d", &parent, &child,
&branch);
t = attach(t, parent, child, branch);
}
printCornerNodes(t);
return 0;
}
