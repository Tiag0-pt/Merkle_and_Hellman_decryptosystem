#include <stdio.h>
#include "../../inc/functions.h"
#include "../../inc/heap.h"

int main(void){
    

    integer_t p[]  = {1,3,7,11,13,19};

    int n = sizeof(p)/sizeof(int);

    min_heap *h = Create_min_Heap(n);

   /*  int n1 = n/2;
    int n1a = n1/2;
    int n1b = n1 - n1a;
    
    int n2 = n - n1;
    int n2a = n2/2;
    int n2b = n2 - n2a; */

    pair_sum pair = {0,3,p[0]+p[3]};
    add(h,pair);
    pair_sum pair2 = {2,5,p[2]+p[5]};
    add(h,pair2);
    pair_sum pair3 = {4,5,p[4]+p[5]};
    add(h,pair3);
    int k = h->size;
    for(int i=0;i<k;i++){
        pair_sum item = poll(h);
        printf("pair = (%llu,%llu) ; sum = %llu ; i-> %d\n",item.a,item.b,item.sum,i);
    }
}