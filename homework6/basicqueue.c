#include <stdio.h>
#include <stdlib.h>
typedef struct node {
int data;
struct node *next;
} node_t;
typedef node_t queue_t;

queue_t* enqueue(queue_t *t, int value){
  queue_t *new_node = (queue_t*)malloc(sizeof(queue_t));

  new_node->data = value;
  new_node->next = NULL;

  if (t==NULL) return new_node;


  queue_t *temp = t;
  while (temp->next != NULL){
      temp = temp->next;
  }
  temp->next = new_node;

 return t  ;

}

queue_t* dequeue(queue_t *t){
  if (t==NULL) {
      printf("Queue is empty.\n");
      return NULL;
  }
  queue_t *tmp = t;
  printf("%d\n",t->data);
  t = t->next;
  free(tmp);

  return t;
}

void show(queue_t *t) {
  if (t == NULL) {
  printf("Queue is empty.\n");
    return;
  }
  while (t !=NULL) {
    printf("%d ",t->data);
    t = t->next;
  }
  printf("\n");

}

void empty(queue_t *t){
  if (t==NULL) printf("Queue is empty.\n");
  else printf("Queue is not empty.\n");
}

void size(queue_t *t){
  int count = 0;
  while (t!= NULL) {
    count++;
    t = t->next;
  }
  printf("%d\n", count);

}



int main(void) {
queue_t *q = NULL;
int n, i, command, value;
scanf("%d", &n);
for (i=0; i<n; i++) {
scanf("%d", &command);
switch(command) {
case 1:
scanf("%d", &value);
q = enqueue(q, value);
break;
case 2:
q = dequeue(q);
break;
case 3:
show(q);
break;
case 4:
empty(q);
break;
case 5:
size(q);
break;
}
}
return 0;
}
