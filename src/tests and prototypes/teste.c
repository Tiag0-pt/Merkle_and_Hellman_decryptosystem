#include <stdio.h>
#include "../../inc/functions.h"
#include "../../inc/heap.h"

int main(void){
    

    int p[]  = {1,3,7,11,13,19};

    int n = sizeof(p)/sizeof(int);

    max_heap *h = Create_max_heap(n);

   /*  int n1 = n/2;
    int n1a = n1/2;
    int n1b = n1 - n1a;
    
    int n2 = n - n1;
    int n2a = n2/2;
    int n2b = n2 - n2a; */

    for(int i =0;i<n;i++){
          add_max(h,p[i]);
    }

    for(int i =0;i<n;i++){
        printf("%llu ",poll_max(h));
    }


}