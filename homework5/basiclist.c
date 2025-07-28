#include <stdio.h>
#include <stdlib.h>
typedef struct node {
  int data;
  struct node *next;
} node_t;


node_t* append(node_t *head){
  int value;
  scanf("%d", &value);

  node_t *newNode = malloc(sizeof(node_t));
  if (newNode == NULL) return head;

  newNode->data = value;
  newNode->next = NULL;

  if (head == NULL) return newNode;

  node_t *current_head = head;
  while (current_head->next != NULL) {
    current_head = current_head->next;
  }
  current_head->next = newNode;

  return head;
}


void get(node_t *head) {
  int index;
  scanf("%d", &index);

  node_t *current_head = head;
  int count = 0;

  while (current_head != NULL) {
    if (count == index) {
      printf("%d\n", current_head->data);
      break;
    }
    count++;
    current_head = current_head->next;
  }

}

void show(node_t *head) {
  node_t *current_head = head;

  while (current_head != NULL) {
      printf("%d ", current_head->data);
      current_head = current_head->next;
  }
  printf("\n");


}

node_t* reverse(node_t *head) {
  node_t *last = NULL;
  node_t *current_head = head;
  node_t *next  ;

  while (current_head != NULL) {
    next = current_head->next;
    current_head->next = last;
    last = current_head;
    current_head = next;

 }

  return last;
}

node_t* cut(node_t *head) {
  int a, b;
  scanf("%d %d", &a, &b);

  if (head == NULL || a > b) return NULL;

  int index = 0;
  node_t *current = head;
  node_t *start = NULL;
  node_t *end = NULL;
  node_t *prev = NULL;

  while (current != NULL && index < a) {
    prev = current;
    current = current->next;
    index++;
  }

  if (current == NULL) return NULL;

  start = current;

  while (current != NULL && index < b) {
    current = current->next;
    index++;
  }

  if (current == NULL) return NULL;

  end = current;
  node_t *after_b = end->next;
  end->next = NULL;

  if (a == 0) {
    return start;
  } else {
    current = head;
    while (current != start) {
      node_t *next = current->next;
      free(current);
      current = next;
    }
    return start;
  }
}


int main(void) {
  node_t *startNode;
  int n,i;
  char command;
  startNode = NULL;
  scanf("%d", &n);
  for (i=0; i<n; i++) {
  scanf(" %c", &command);
  switch (command) {
   case 'A':
    startNode = append(startNode);
    break;
   case 'G':
    get(startNode);
    break;
    case 'S':
    show(startNode);
    break;
    case 'R':
    startNode = reverse(startNode);
    break;
    case 'C':
    startNode = cut(startNode);
    break;
    default:
    break;
    }
    }
return 0;
}
