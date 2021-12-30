#ifndef HEAP_H_
#define HEAP_H_

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

void heapifyUp_max(max_heap *h);

void heapifyDown_max(max_heap *h);

int get_child_idx(int idx_parent_max, int direction){return 2*idx_parent_max + 1 + direction;} // 1 - direita 0 ; - esquerda

int get_parent_idx(int idx_child_max){return (idx_child_max - 1)/2;};

int has_child_max(max_heap *h,int idx_parent_max, int direction ){return get_child_idx(idx_parent_max,direction) < h->size ;};

int has_parent_max(max_heap *h,int idx_child_max){return get_parent_idx(idx_child_max) >= 0;}

int child_max(max_heap *h,int idx,int direction){return h->array[get_child_idx(idx,direction)];}

int parent_max(max_heap *h,int idx){return h->array[get_parent_idx(idx)];}

void swap_max(max_heap *h,int idx_1,int idx_2){
    
    int temp = h->array[idx_1];
    h->array[idx_1] = h->array[idx_2];
    h->array[idx_2] = temp;
}

int peek_max(max_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    return h->array[0];
}

int poll_max(max_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    int item = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapifyDown_max(h);
    return item;
}

void add_max(max_heap *h,int item){
    if (h->size == h->capacity) {
        printf("Too much -max heap ");
        return;
    }
    h->array[h->size] = item;
    h->size++;
    heapifyUp_max(h);
}

void heapifyUp_max(max_heap *h){
    int idx = h->size - 1;
    while(has_parent_max(h,idx) && (parent_max(h,idx) < h->array[idx])){
        swap_max(h,get_parent_idx(idx),idx);
        idx = get_parent_idx(idx);
    }
}

void heapifyDown_max(max_heap *h){
    int idx = 0;
    while (has_child_max(h,idx,0)){
        int big_child_max_idx = get_child_idx(idx,0);
        if (has_child_max(h,idx,1) && (child_max(h,idx,1) > child_max(h,idx,0)) ){
            big_child_max_idx = get_child_idx(idx,1);
        }

        if(h->array[idx] > h->array[big_child_max_idx]){
            break;
        } else {
            swap_max(h,idx,big_child_max_idx);
            idx = big_child_max_idx;
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


struct min_heap
{
    int *array;
    int size;
    int capacity;
};

typedef struct min_heap min_heap;

min_heap *Create_min_Heap(int capacity);

void heapifyDown(min_heap *h);

void heapifyUp(min_heap *h);

int has_child(min_heap *h,int idx_parent, int direction ){return get_child_idx(idx_parent,direction) < h->size ;};

int has_parent(min_heap *h,int idx_child){return get_parent_idx(idx_child) >= 0;}

int child(min_heap *h,int idx,int direction){return h->array[get_child_idx(idx,direction)];}

int parent(min_heap *h,int idx){return h->array[get_parent_idx(idx)];}

void swap(min_heap *h,int idx_1,int idx_2){
    
    int temp = h->array[idx_1];
    h->array[idx_1] = h->array[idx_2];
    h->array[idx_2] = temp;
}

int peek(min_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    return h->array[0];
}

int poll(min_heap *h){
    if(h->size == 0){
        return 7;
    }
    int item = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapifyDown(h);
    return item;
}

void add(min_heap *h,int item){
    if (h->size == h->capacity) {
        printf("Too much -min heap ");
        return;
    }
    h->array[h->size] = item;
    h->size++;
    heapifyUp(h);
}

void heapifyUp(min_heap *h){
    int idx = h->size - 1;
    while(has_parent(h,idx) && parent(h,idx) > h->array[idx]){
        swap(h,get_parent_idx(idx),idx);
        idx = get_parent_idx(idx);
    }
}

void heapifyDown(min_heap *h){
    int idx = 0;
    while (has_child(h,idx,0)){
        int small_child_idx = get_child_idx(idx,0);
        if (has_child(h,idx,1) && child(h,idx,1) < child(h,idx,0) ){
            small_child_idx = get_child_idx(idx,1);
        }

        if(h->array[idx] < h->array[small_child_idx]){
            break;
        } else {
            swap(h,idx,small_child_idx);
            idx = small_child_idx;
        }
    }
}

min_heap *Create_min_Heap(int capacity){
    int *arr = (int *) malloc(capacity*sizeof(int));
    if ( arr == NULL){
        printf("Memory Error!");
    }
    min_heap *h = (min_heap *) malloc (sizeof(min_heap));
    h->array = arr;
    h->size = 0;
    h->capacity = capacity;
    return h;
}
#endif