#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int size) {
    heap_t *new_node = malloc(sizeof(heap_t));
    new_node->data = (int*)malloc((size + 1) * sizeof(int));
    new_node->last_index = 0;
    return new_node;
}

void go_up_max(heap_t *root, int index) {
    while (index > 1 && root->data[index] > root->data[index/2]) {
        int temp = root->data[index];
        root->data[index] = root->data[index/2];
        root->data[index/2] = temp;
        index = index / 2;
   }
}

void go_down_max(heap_t *root, int index) {
   int left, right, large;
   while (1) {
        left = 2 * index;
       right = 2 * index + 1;
        large = index;
        if (left <= root->last_index && root->data[left] > root->data[large]) large = left;
        if (right <= root->last_index && root->data[right] > root->data[large]) large = right;
        if (large == index) break;
        int temp = root->data[index];
        root->data[index] = root->data[large];
        root->data[large] = temp;
        index = large;
  }
}

void insert_max(heap_t *root, int value) {
   root->last_index += 1;
    root->data[root->last_index] = value;
    go_up_max(root, root->last_index);
}

int extract_max(heap_t *root) {
    if (root->last_index == 0) return -1;
    int max = root->data[1];
    root->data[1] = root->data[root->last_index--];
    go_down_max(root, 1);
    return max;
}

int peek_max(heap_t *root) {
    if (root->last_index == 0) return -1;
    return root->data[1];
}

void go_up_min(heap_t *root, int index) {
    while (index > 1 && root->data[index] < root->data[index/2]) {
        int temp = root->data[index];
      root->data[index] = root->data[index/2];
     root->data[index/2] = temp;
      index = index / 2;
 }
}

void go_down_min(heap_t *root, int index) {
    int left, right, small;
    while (1) {
        left = 2 * index;
        right = 2 * index + 1;
        small = index;
        if (left <= root->last_index && root->data[left] < root->data[small]) small = left;
        if (right <= root->last_index && root->data[right] < root->data[small]) small = right;
        if (small == index) break;
        int temp = root->data[index];
        root->data[index] = root->data[small];
        root->data[small] = temp;
        index = small;
  }
}

void insert_min(heap_t *root, int value) {
    root->last_index += 1;
    root->data[root->last_index] = value;
    go_up_min(root, root->last_index);
}

int extract_min(heap_t *root) {
    if (root->last_index == 0) return -1;
    int min = root->data[1];
    root->data[1] = root->data[root->last_index--];
    go_down_min(root, 1);
    return min;
}

int peek_min(heap_t *root) {
    if (root->last_index == 0) return -1;
    return root->data[1];
}

void balance_heaps(heap_t *max_heap, heap_t *min_heap) {
    if (max_heap->last_index > min_heap->last_index + 1) {
       int moved = extract_max(max_heap);
        insert_min(min_heap, moved);
  }else if (min_heap->last_index > max_heap->last_index) {
     int moved = extract_min(min_heap);
    insert_max(max_heap, moved);
 }
}

double get_median(heap_t *max_heap, heap_t *min_heap) {
    if ((max_heap->last_index + min_heap->last_index) % 2 == 0) {
      return (peek_max(max_heap) + peek_min(min_heap)) / 2.0;
   }else {
      return peek_max(max_heap);
  }
}

int main(void) {
    int n, val;
    scanf("%d", &n);
   heap_t *max_heap = init_heap(n);
   heap_t *min_heap = init_heap(n);
    for (int i= 0;i<n;i++) {
    scanf("%d", &val);
     if (max_heap->last_index == 0 || val <= peek_max(max_heap)) {
        insert_max(max_heap, val);
     }else {
      insert_min(min_heap, val);
     }
    balance_heaps(max_heap, min_heap);
    printf("%.1f\n", get_median(max_heap, min_heap));
   }}

