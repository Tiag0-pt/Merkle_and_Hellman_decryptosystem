#include <stdio.h>
#include "../../inc/heap.h"
int main(void){
    int i;
    
    min_heap *p_h = Create_min_Heap(6);
    max_heap *p_h_m = Create_max_heap(6);
    int arr[] = {1,3,6,11,23,34};
    for (i = 0;i<6;i++){
        add(p_h,arr[i]);
        add_max(p_h_m,arr[i]);
    }
    printf("min_heap \n");
    for (i = 0;i<6;i++){
        printf("%d parent -> %d\n",p_h->array[i],p_h->array[get_parent_idx(i)]);
    }
    printf("max_heap \n");
    for (i = 0;i<6;i++){
        printf("%d parent -> %d\n",p_h_m->array[i],p_h_m->array[get_parent_idx(i)]);
    }
}