#include <stdio.h>
#include <stdlib.h>

#ifndef __bin_tree__
#define __bin_tree__
typedef struct node{
  int         data;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t tree_t;
#endif

node_t *createNode(int data) {
  node_t *tmp = (node_t*)malloc(sizeof(node_t));
  tmp->data = data;
  tmp->left = NULL;
  tmp->right = NULL;
  return tmp;
}

node_t *searchNode(tree_t *root, int data) {
  node_t *result;

  if (root == NULL)
    return NULL;
  if (root->data == data)
    return root;

  result = searchNode(root->left, data);
  if (result != NULL)
    return result;

  return searchNode(root->right, data);
}

void add(tree_t *parent, node_t *newNode, int branch) {
  if (branch == 1)
    parent->left = newNode;
  else if (branch == 2)
    parent->right = newNode;
}

tree_t *attach(tree_t *root, int parentData, int childData, int branch) {
  node_t *tmpNode;

  if (parentData == -1)
    return createNode(childData);

  tmpNode = searchNode(root, parentData);
  add(tmpNode, createNode(childData), branch);

  return root;
}
