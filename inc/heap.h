#ifndef HEAP_H_
#define HEAP_H_

#include<stdio.h>
#include<stdlib.h>
#include <errno.h>

typedef unsigned long long integer_t;

struct pair_sum 
{
    integer_t a;
    integer_t b;
    integer_t sum;
};

typedef struct pair_sum pair_sum;

struct max_heap
{
    pair_sum *array;
    long long int size;
    long long int capacity;
};



typedef struct max_heap max_heap;

void heapifyUp_max(max_heap *h);

void heapifyDown_max(max_heap *h);

long long int get_child_idx(long long int idx_parent_max, int direction){return 2*idx_parent_max + 1 + direction;} // 1 - direita 0 ; - esquerda

long long int get_parent_idx(long long int idx_child_max){return (idx_child_max - 1)/2;};

int has_child_max(max_heap *h,long long int idx_parent_max, int direction ){return get_child_idx(idx_parent_max,direction) < h->size ;};

int has_parent_max(max_heap *h,long long int idx_child_max){return get_parent_idx(idx_child_max) >= 0;}

integer_t child_max(max_heap *h,long long int idx,int direction){return h->array[get_child_idx(idx,direction)].sum;}

integer_t parent_max(max_heap *h,long long int idx){return h->array[get_parent_idx(idx)].sum;}

void swap_max(max_heap *h,long long int idx_1,long long int idx_2){
    
    pair_sum temp = h->array[idx_1];
    h->array[idx_1] = h->array[idx_2];
    h->array[idx_2] = temp;
}

pair_sum peek_max(max_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    return h->array[0];
}

pair_sum poll_max(max_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    pair_sum item = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapifyDown_max(h);
    return item;
}

void add_max(max_heap *h,pair_sum item){
    if (h->size == h->capacity) {
        printf("Too much -max heap ");
        return;
    }
    h->array[h->size] = item;
    h->size++;
    heapifyUp_max(h);
}

void heapifyUp_max(max_heap *h){
    long long int idx = h->size - 1;
    while(has_parent_max(h,idx) && (parent_max(h,idx) < h->array[idx].sum)){
        swap_max(h,get_parent_idx(idx),idx);
        idx = get_parent_idx(idx);
    }
}

void heapifyDown_max(max_heap *h){
    long long int idx = 0;
    while (has_child_max(h,idx,0)){
        long long int big_child_max_idx = get_child_idx(idx,0);
        if (has_child_max(h,idx,1) && (child_max(h,idx,1) > child_max(h,idx,0)) ){
            big_child_max_idx = get_child_idx(idx,1);
        }

        if(h->array[idx].sum > h->array[big_child_max_idx].sum){
            break;
        } else {
            swap_max(h,idx,big_child_max_idx);
            idx = big_child_max_idx;
        }
    }
}

max_heap *Create_max_heap(long long int capacity){
    pair_sum *arr = (pair_sum*)malloc(capacity*sizeof(pair_sum));
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
    pair_sum *array;
    long long int size;
    long long int capacity;
};

typedef struct min_heap min_heap;

min_heap *Create_min_Heap(long long int capacity);

void heapifyDown(min_heap *h);

void heapifyUp(min_heap *h);

int has_child(min_heap *h,long long int idx_parent, int direction ){return get_child_idx(idx_parent,direction) < h->size ;};

int has_parent(min_heap *h,long long int idx_child){return get_parent_idx(idx_child) >= 0;}

integer_t child(min_heap *h,long long int idx,int direction){return h->array[get_child_idx(idx,direction)].sum;}

integer_t parent(min_heap *h,long long int idx){return h->array[get_parent_idx(idx)].sum;}

void swap(min_heap *h,long long int idx_1,long long int idx_2){
    
    pair_sum temp = h->array[idx_1];
    h->array[idx_1] = h->array[idx_2];
    h->array[idx_2] = temp;
}

pair_sum peek(min_heap *h){
    if(h->size == 0){
        printf("ilegal operation: array empty");
    }
    return h->array[0];
}

pair_sum poll(min_heap *h){
    if(h->size == 0){
        return *(pair_sum*)0;
    }
    pair_sum item = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapifyDown(h);
    return item;
}

void add(min_heap *h,pair_sum item){
    if (h->size == h->capacity) {
        printf("Too much -min heap ");
        return;
    }
    h->array[h->size] = item;
    h->size++;
    heapifyUp(h);
}

void heapifyUp(min_heap *h){
    long long int idx = h->size - 1;
    while(has_parent(h,idx) && parent(h,idx) > h->array[idx].sum){
        swap(h,get_parent_idx(idx),idx);
        idx = get_parent_idx(idx);
    }
}

void heapifyDown(min_heap *h){
    long long int idx = 0;
    while (has_child(h,idx,0)){
        long long int small_child_idx = get_child_idx(idx,0);
        if (has_child(h,idx,1) && child(h,idx,1) < child(h,idx,0) ){
            small_child_idx = get_child_idx(idx,1);
        }

        if(h->array[idx].sum < h->array[small_child_idx].sum){
            break;
        } else {
            swap(h,idx,small_child_idx);
            idx = small_child_idx;
        }
    }
}

min_heap *Create_min_Heap(long long int capacity){
    pair_sum *arr = (pair_sum*)malloc(capacity*sizeof(pair_sum));
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
