#include <stdio.h>
#include "../../inc/heap.h"
#include "../../inc/functions.h"


int compare_int(const void *a, const void *b)
{
    if (*(int*)a>*(int*)b) return 1;
    if (*(int*)a<*(int*)b) return -1;
    return 0;
}

void make_sums(int n,int p[n],int *sums){
    long long int total_sums = 1ULL<< n;
    long long int i,j,sum;
    for(i = 0; i<total_sums;i++){
        sum = 0;
        for(j = 0; j<n ;j++){
            if (i & (1 << j)){
                sum += p[j]; 
            }
        }

        sums[i] = sum;
    }
    qsort(sums,total_sums,sizeof(int),compare_int);
}

int main(void){
    int i;
    
    min_heap *lower_heap = Create_min_Heap(6);
    max_heap *upper_heap = Create_max_heap(6);
    int p[] = {1,3,6,11,23,34};
    int desired_sum = 23 + 3;
    int n = sizeof(p)/sizeof(int);

    int n1 = n/2;
    int n1a = n1/2;
    int n1b = n1 - n1a;
    
    int n2 = n - n1;
    int n2a = n2/2;
    int n2b = n2 - n2a;

    int lwa = (int*)malloc(sizeof(int)*(1<<n1a));
    int lwb = (int*)malloc(sizeof(int)*(1<<n1b));
    int upa = (int*)malloc(sizeof(int)*(1<<n2a));
    int upb = (int*)malloc(sizeof(int)*(1<<n2b));

    make_sums(n1a,p,lwa);
    make_sums(n1b,p+n1a,lwb);
    make_sums(n2a,p+(n1a+n1b),upa);
    make_sums(n2b,p+(n1a+n1b+n2a),upb);

    int b[n];
    memset(b, 0, n*sizeof(int));

    int l = 0;
    int sum;
    int ia=0;
    int ib=0;
    int ja=(1<<n2b)-1;
    int jb=(1<<n2b)-1;

    for(ib=0;ib<(1LL << n1b);ib++){
        add(lower_heap,lwa[ia]+lwb[ib]);
    }

    for(jb=(1<<n2b)-1;jb>0;jb--){
        add_max(upper_heap,lwa[ja]+lwb[jb]);
    }

    sum = poll(lower_heap) + poll_max(upper_heap);

    // n1a e n2a vão ser sempre iguais logo não há problema com os indices mais pequenos ia e ib e n2 > n1 então n2b > n1b

    while(sum != desired_sum){
        for(l=0 ;l<(1<<n2b)-1 ; l++){
            sum = poll(lower_heap) + poll_max(upper_heap);
            if(sum = desired_sum){
                break;
            }
        }
        if(sum<desired_sum){
            ia++;
            for(ib=0;ib<n1b;ib++){
                add(lower_heap,lwa[ia]+lwb[ib]);
            }
            // como min heap retorna sempre o menor elemento e o array é crescente a posição na heap é igual á ib 
        } else if (sum < desired_sum) {
            ja--;
            for(jb=(1<<n2b)-1;jb>=0;jb--){
                add_max(upper_heap,lwa[ja]+lwb[jb]);
            }
        }
            
            // como max heap retorna sempre o maior elemento e o array é crescente a posição (h) na heap jb =  (1<<n2b) - l
    }

    if(l > ib){
        ib = (1LL << n1b) -1 ;
    }

    jb =  (1<<n2b) - l;

    /* brute_force_recursive(n1a,p,lwa[ia],0,0,b);
    brute_force_recursive(n1b,p+n1a,lwb[ib],0,0,b+n1a);
    brute_force_recursive(n2a,p+(n1a+n1b),upa[ja],0,0,b+(n1a+n1b));
    brute_force_recursive(n2b,p+(n1a+n1b+n2a),upb[jb],0,0,(n1a+n1b+n2a)); */

}

   

    