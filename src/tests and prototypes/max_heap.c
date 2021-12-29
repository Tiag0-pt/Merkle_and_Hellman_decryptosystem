#include<stdio.h>
#include<stdlib.h>
#include <errno.h>


struct max_heap
{
    int *array;
    int size;
    int capacity;
};

typedef struct max_heap max_heap;

max_heap *Create_max_heap(int capacity);

void heapifyDown(max_heap *h);

void heapifyUp(max_heap *h);

int get_child_idx(int idx_parent, int direction){return 2*idx_parent + 1 + direction;} // 1 - direita 0 ; - esquerda

int get_parent_idx(int idx_child){return (idx_child - 1)/2;};

int has_child(max_heap *h,int idx_parent, int direction ){return get_child_idx(idx_parent,direction) < h->size ;};

int has_parent(max_heap *h,int idx_child){return get_parent_idx(idx_child) >= 0;}

int child(max_heap *h,int idx,int direction){return h->array[get_child_idx(idx,direction)];}

int parent(max_heap *h,int idx){return h->array[get_parent_idx(idx)];}

void swap(max_heap *h,int idx_1,int idx_2){
    
    int temp = h->array[idx_1];
    h->array[idx_1] = h->array[idx_2];
    h->array[idx_2] = temp;
}

int peek(max_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    return h->array[0];
}

int poll(max_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    int item = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapifyDown(h);
    return item;
}

void add(max_heap *h,int item){
    if (h->size == h->capacity) {
        printf("ilegal operation: max size reached cannot add elements");
        return;
    }
    h->array[h->size] = item;
    h->size++;
    heapifyUp(h);
}

void heapifyUp(max_heap *h){
    int idx = h->size - 1;
    while(has_parent(h,idx) && (parent(h,idx) < h->array[idx])){
        swap(h,get_parent_idx(idx),idx);
        idx = get_parent_idx(idx);
    }
}

void heapifyDown(max_heap *h){
    int idx = 0;
    while (has_child(h,idx,0)){
        int big_child_idx = get_child_idx(idx,0);
        if (has_child(h,idx,1) && (child(h,idx,1) > child(h,idx,0)) ){
            big_child_idx = get_child_idx(idx,1);
        }

        if(h->array[idx] > h->array[big_child_idx]){
            break;
        } else {
            swap(h,idx,big_child_idx);
            idx = big_child_idx;
        }
    }
}

max_heap *Create_max_heap(int capacity){
    int *arr = (int *) malloc(capacity*sizeof(int));
    if ( arr == NULL){
        printf("Memory Error!");
    }
    max_heap *h = (max_heap *) malloc (sizeof(max_heap));
    h->array = arr;
    h->size = 0;
    h->capacity = capacity;
    return h;
}

int main(void){
    int i;
    max_heap h = *Create_max_heap(7);
    max_heap *p_h = &h;
    int arr[] = {1,3,6,11,23,34,2};
    for (i = 0;i<7;i++){
        add(p_h,arr[i]);
    }
    
    for (i = 0;i<7;i++){
        printf("%d parent -> %d\n",p_h->array[i],p_h->array[get_parent_idx(i)]);
    }
}