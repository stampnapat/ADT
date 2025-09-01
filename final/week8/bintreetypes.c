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
// ...

int is_full(node_t *t) {
  if (t==NULL) return 1;

  if (t->left == NULL && t->right == NULL) return 1;
  
  if (t->left != NULL && t->right != NULL) 
    return (is_full(t->left)&&is_full(t->right));
 
  return 0;

}

int find_depth(node_t *t){
  int depth = 0;
  node_t *tmp = t;
  while (tmp!=0){
    depth++;
    tmp = tmp->left;
  }
  return depth;

  }

int perfect_recur(node_t *t, int depth, int level){
  if (t == NULL) return 1;
  if (t->left == NULL && t->right == NULL) return (depth == level +1);
  if (t->left ==NULL || t->right == NULL) return 0;
  
  return perfect_recur(t->left, depth, level+1) && perfect_recur(t->right, depth, level+1);


}

int is_perfect(node_t *t) {
  int depth = find_depth(t);
  return perfect_recur(t, depth, 0);
}

int nodes(node_t *t){
  if (t == NULL) return 0;
  return 1 + nodes(t->right) + nodes(t->left);
}

int complete_recur(node_t *t, int index, int nodes) {
  if (t==NULL) return 1;

  if (index >= nodes) return 0;

  return complete_recur(t->left, 2*index+1, nodes) && complete_recur(t->right, 2*index+2,nodes);
}

int is_complete(node_t *t){
  int total_node = nodes(t);
  
  return complete_recur(t, 0, total_nodes);

}

int is_degenerate(node_t *t) {
  if (t==NULL) return 1;

  if (t->left != NULL && t->right != NULL) return 0;

  return is_degenerate(t->left) && is_degenerate(t->right);
}

int is_right_skew(node_t *t){
  if (t==NULL) return 1;
  if (t->left != NULL) return 0;

  return is_right_skew(t->right);
}

int is_left_skew(node_t *t){
  if (t==NULL) return 1;
  if (t->right != NULL) return 0;

  return is_left_skew(t->left);
}

int is_skewed(node_t *t){
  return is_left_skew(t) || is_right_skew(t);
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
printf("%d %d %d %d %d\n", is_full(t),
is_perfect(t), is_complete(t),
is_degenerate(t), is_skewed(t));
return 0;
}
