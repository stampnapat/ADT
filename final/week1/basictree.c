#include <stdio.h>
#include <stdlib.h>
// You can define your own (one or more)
// structures here. However, we eventually
// need the data type "tree_t".
// For example:
// typedef struct node {
// ...
// } node_t;
// typedef node_t tree_t;
// Write your code here
// ...
//
typedef struct node {
  int data;
  struct node *next_sibling;
  struct node *first_child;
}tree_t;

tree_t* create_node(int data) {
    *tree_t new_node = (tree_t*)malloc(sizeof(tree_t));
  if new_node == NULL return 0;

  new_node->data = data;
  new_node->first_child = NULL;
  new_node->next_silbling = NULL;
  return new_node;
}

tree_t* attach(tree_t, int parent, int child) {

}

tree_t* detach(tree_t, int data) {

}

tree_t* search(tree_t* t, int data) {
  if (t == NULl ) return NULL;
  if (t->data == data) return t;

  tree_t *find = search(t->first_child, data);
  if (find != NULL) return find;
  else search(t->next_sibling, data);

}

int degree(tree_t, int data) {
  return ;
}

int is_root(tree_t, int data) {
  return 
}

int is_leaf(tree_t, int data) {
  return
}

void siblings(tree_t, int data) {

}

int depth(tree_t, int data) {
  return 
}

void print_path(*frist_node,*last_node){

}

int path_length(*frist_node, *last_node) {

}

void ancestor(*node) {

}

void descendat(*node) {

}

void bfs(*tree) {

}

void dfs(*tree) {

}

void print_tree(*tree) {

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
printf("%d\n",
path_length(t, start, end));
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
