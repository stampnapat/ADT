#include <stdio.h>
#include <stdlib.h>
typedef struct heap {
int *data;
int last_index;
} heap_t;

heap_t *init_heap(int value) {
  heap_t *new_node = malloc(sizeof(heap_t));

  new_node->data = (int*)malloc((value+1)*sizeof(int));
  new_node->last_index = 0;
  return new_node;
}

void go_up(heap_t *root, int index){
  while (index>1 && root->data[index] > root->data[index/2]){
  int temp = root->data[index];
  root->data[index] = root->data[index/2];
  root->data[index/2] =  temp;
  index = index/2;
  }
}


void insert(heap_t *root, int value ){
  root->last_index += 1;
  root->data[root->last_index] = value;
  go_up(root, root->last_index);

}

void go_down(heap_t *root, int index){
  int left, right, large;

  while(1){
    left = 2* index;
    right = 2 * index+1;
    large = index;

    if (left <= root->last_index && root->data[left] > root->data[large]) large = left;
    if (right<= root->last_index && root->data[right] > root->data[large]) large = right;
    if (large == index) break;

    int temp = root->data[index];
    root->data[index] = root->data[large];
    root->data[large] = temp;

    index = large;
  }
}

void delete_max(heap_t *root) {
  if (root->last_index == 0)return ;
  root->data[1] = root->data[root->last_index];
  root->last_index -= 1;
  if (root->last_index > 0) go_down(root,1);

}

int find_max(heap_t *root) {
  if (root->last_index == 0) return -1;
  return root->data[1];
}

void update_key(heap_t *h, int old, int new){
  int index = -1;
  for (int i=1 ; i<= h->last_index;i++) {
    if (h->data[i] == old) {
      index = i;
      break;
    }
  }
  if (index != -1){
    h->data[index] = new;
  if (new > old) go_up(h, index);
  else go_down(h, index);
}

}

void bfs(heap_t *max_heap) {
  for (int i = 1; i <= max_heap->last_index; i++) {
     printf("%d", max_heap->data[i]);
       if (i < max_heap->last_index) {
          printf(" ");
       }
   }
    printf("\n");
}


// Write your code here
// ...
int main(void) {
heap_t *max_heap = NULL;
int m, n, i;
int command, data;
int old_key, new_key;
scanf("%d %d", &m, &n);
max_heap = init_heap(m);
for (i=0; i<n; i++) {
scanf("%d", &command);
switch (command) {
case 1:
scanf("%d", &data);
insert(max_heap, data);
break;
case 2:
delete_max(max_heap);
break;
case 3:
printf("%d\n", find_max(max_heap));
break;
case 4:
scanf("%d %d", &old_key, &new_key);
update_key(max_heap, old_key,
new_key);
break;
case 5:
bfs(max_heap);
break;
}
}
return 0;
}
