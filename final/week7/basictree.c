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
  struct node *parent;
  struct node *next_sibling;
  struct node *first_child;
};

typedef node tree_t;

tree_t* create_node(int data) {
    tree_t *new_node = (tree_t*)malloc(sizeof(tree_t));
  if new_node == NULL return NULL;

  new_node->data = data;
  new_node->parent = NULL;
  new_node->first_child = NULL;
  new_node->next_sibling = NULL;
  return new_node;
}

tree_t* attach(tree_t *t, int parent, int child) {
  tree_t *child_node = create_node(child);
    if (parent == -1) {
      if ( t != NULL) return child_node;
  }

  tree_t *parent_node = find_node(t, parent);
  if (parent_node == NULL) return t


  child_node->parent = parent_node;
  if (parent_node->first_child == NULL) parent_node->first_child = child_node;
  else {
    tree_t *first_child = parent_node->fisrt_child;
    while (fisrt_child->next_sibling != NULL) {
        first_child = first_child->next_sibling;
    }first_child->next_sibling = child_node;
    
  }
  return t;
  }


 tree_t* detach(tree_t *t, int data) {
    

}

int search(tree_t* t, int data) {
  if (find_node(t, data) != NULL) return 1;
  return 0;

}



tree_t* find_node(tree_t* t, int data) {
  if (t == NULL ) return NULL;
  if (t->data == data) return t;

  tree_t *find = find_node(t->first_child, data);
  if (find != NULL) return find;

  else return find_node(t->next_sibling, data) ;

}

int degree(tree_t *t, int data) {
  int count = 0;
  tree_t *node = find(t, data);
  if (node == NULL) return 0;

  tree_t *current_child = node->first_child;

  while (current_child != NULL){
    count++;
    current_child = current_child->next_sibling;
  }
 return count;
}

int is_root(tree_t *t, int data) {
  if (t == NULL) return 0;
  if (t->data == data) return 1;
  else return 0;

}

int is_leaf(tree_t *t, int data) {
  tree_t *leaf = search(t, data);
  if (leaf == NULL) return 0;
  if (leaf->first_child == NULL) return 1;
  else return 0;

}

void siblings(tree_t *t, int data) {
    tree_t *current_node = find_node(t, data);

    if (current_node == NULL) {
        printf("\n");
        return;
    }
    tree_t *parent = current_node->parent;
    if (parent == NULL) {
        printf("\n");
        return;
    }
    tree_t *child = parent->first_child;
    int print_before = 0;

    while (child != NULL) {
        if (child != current_node) {
            if (print_before == 1) {
                printf(" ");
            }
            printf("%d", child->data);
            print_before = 1;
        }
        child = child->next_sibling;
    }
    printf("\n");


}

// int find_depht(tree_t *t, int data, int level) {
//   if (t == NULL) return 0;
//   if (t->data == data) return level;
//
//   int find = find_depht(t->first_child, data, level+1);
//   if (find != -1) return find;
//   return find_depth(t->next_sibling, data, level);
//
// }

int depth(tree_t *t, int data) {
  tree_t *node = find_node(t, data);
  if (node == NULL) return -1;
  int count = 0;
  while (node->parent != NULL) {
    count++;
    node = node->parent;
  }
  return count; 

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
