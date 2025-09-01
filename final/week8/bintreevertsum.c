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


void sum(node_t *t, int index, int arr[]){
  if (t == NULL) return;

  arr[index+500] += t->data;
  sum(t->left, index-1, arr);
  sum(t->right, index+1, arr);
}

void printVerticalSum(node_t *t){
  int arr[1001] = {0};
  sum(t, 0, arr);

  for (int i = 0; i<1001, i++){
    if (arr[i] != 0){
      printf("%d ", arr[i]);
    }
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
printVerticalSum(t);
return 0;
}
