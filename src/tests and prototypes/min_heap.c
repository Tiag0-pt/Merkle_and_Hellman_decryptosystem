#include<stdio.h>
#include<stdlib.h>
#include <errno.h>


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

int get_child_idx(int idx_parent, int direction){return 2*idx_parent + 1 + direction;} // 1 - direita 0 ; - esquerda

int get_parent_idx(int idx_child){return (idx_child - 1)/2;};

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
        printf("ilegal operation: array empty");
    }
    int item = h->array[0];
    h->array[0] = h->array[h->size - 1];
    h->size--;
    heapifyDown(h);
    return item;
}

void add(min_heap *h,int item){
    if (h->size == h->capacity) {
        printf("ilegal operation: max size reached cannot add elements");
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

int main(void){
    int i;
    
    min_heap *p_h = Create_min_Heap(6);
    int arr[] = {1,3,6,11,23,34};
    for (i = 0;i<6;i++){
        add(p_h,arr[i]);
    }
    
    for (i = 0;i<6;i++){
        printf("%d \n",p_h->array[i]);
    }
}