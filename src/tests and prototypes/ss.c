#include <stdio.h>
#include "../../inc/functions.h"
#include "../../inc/heap.h"


typedef unsigned long long integer_t;

/*
void refill_lw(long long int a,min_heap *lw_heap, integer_t *lwa , integer_t *lwb ,int size){
  long long int ib;
  for(ib=0;ib<(1LL << size);ib++){
        //printf("%lld ",lwa[ia]+lwb[ib]);
        add(lw_heap,(lwa[a]+lwb[ib]));
  }
  a++;
}
void refill_up(long long int a,max_heap *up_heap, integer_t *upa , integer_t *upb ,int size){
  long long int jb;
  for(jb=(1<<size)-1;jb>-1;jb--){
        //printf("%lld -> %d ",upa[ja]+upb[jb],jb);
        add_max(up_heap,upa[a]+upb[jb]);
  }
  a--;
}
*/


void ss(int n,integer_t p[n],integer_t desired_sum,int b[n]){
    int n1 = n/2;
    int n1a = n1/2;
    int n1b = n1 - n1a;
    
    int n2 = n - n1;
    int n2a = n2/2;
    int n2b = n2 - n2a;

    integer_t *lwa = (integer_t*)malloc(sizeof(integer_t)*(1LL<<n1a));
    integer_t *lwb = (integer_t*)malloc(sizeof(integer_t)*(1LL<<n1b));
    integer_t *upa = (integer_t*)malloc(sizeof(integer_t)*(1LL<<n2a));
    integer_t *upb = (integer_t*)malloc(sizeof(integer_t)*(1LL<<n2b));

    /*
    printf("size of lwa -> %lld\n", (1LL<<n1a));
    printf("size of lwb -> %lld\n", (1LL<<n1b));
    printf("size of upa -> %lld\n", (1LL<<n2a));
    printf("size of upb -> %lld\n", (1LL<<n2b));
    */

    min_heap *lower_heap = Create_min_Heap((1LL<<n1b));
    max_heap *upper_heap = Create_max_heap((1LL<<n2b));

    make_sums(n1a,p,lwa);
    make_sums(n1b,p+n1a,lwb);
    make_sums(n2a,p+(n1a+n1b),upa);
    make_sums(n2b,p+(n1a+n1b+n2a),upb);

    for(int ia=0;ia<(1LL << n1a);ia++){
        //add(Q', (P1, first(P2)))
        pair_sum pair = {ia, 0, lwa[ia]+lwb[0]};
        //printf("pair->%d\n", lwa[ia]+lwb[0]);
        add(lower_heap, pair);
    }
    
    for(int ja=0;ja<(1LL<<n2a);ja++){
        //add(Q'', (P3, first(P4)))
        pair_sum pair = {ja, (1LL<<n2b)-1, upa[ja]+upb[(1LL<<n2b)-1]};
        printf("pair2->%d\n",  upa[ja]);
        add_max(upper_heap, pair);
    }

    pair_sum j;
    pair_sum i; 
    integer_t sum; 


    while(lower_heap->size != 0 && upper_heap->size != 0){
        i = peek(lower_heap);
        j = peek_max(upper_heap);
        sum = i.sum+j.sum;

        printf("sum->%d\n",sum);
        printf("i->%d\n",i.sum);
        printf("j->%d\n",j.sum);
        printf("================\n");
        /*
        // DEBUG
        printf("sum->%d\n",sum);
        printf("ia->%d\n",ia);
        printf("ib->%d\n",i.b);
        printf("min_heap size->%d\n",lower_heap->size);
        printf("max_heap size->%d\n",upper_heap->size);
        printf("================\n");
        */

        if (sum == desired_sum) break;

        if (sum < desired_sum){
            poll(lower_heap);
            if (i.b+1 < (1LL<<n1b)){
                pair_sum pair = {i.a, i.b+1, lwa[i.a]+lwb[i.b+1]};
                add(lower_heap, pair);
            }
        }

        if (sum > desired_sum){
            poll_max(upper_heap);
            if ((j.b-1) != -1){
                printf("here2: %lld\n", j.b-1);
                printf("here3: %lld\n", upb[j.b-1]);
                pair_sum pair = {j.a, j.b-1, upa[j.a]+upb[j.b-1]};
                add_max(upper_heap, pair);
            }
        }

    }
    if(desired_sum!=sum){
        printf("NOT FOUND!!!!\n");
        return;
    }
    printf("Result -> %lld %lld\n",j.sum,i.sum);
}

int main(void){
    /*
    integer_t p[] ={
      (integer_t)5956ull,
      (integer_t)10669ull,
      (integer_t)11912ull,
      (integer_t)21338ull,
      (integer_t)29780ull,
      (integer_t)35423ull,
      (integer_t)47183ull,
      (integer_t)51610ull,
      (integer_t)60973ull,
      (integer_t)62538ull,
      (integer_t)67868ull,
      (integer_t)70135ull,
      (integer_t)75427ull,
      (integer_t)78073ull,
      (integer_t)82374ull
    };
    */

    integer_t p[]  = {1,3,7,11,13,19};

    int n = sizeof(p)/sizeof(integer_t);

    integer_t k[1ull << n];

    make_sums(n,p,k);

    //integer_t desired_sum = 49; //p[3] + p[n-1]
    int b[n];

    //ss(n,p,desired_sum,b);
    for (integer_t i = 0; i < 1ll<<n;i++)
    {
        printf("k[i] ->%lld\n", k[i]);
        ss(n,p,k[i],b);
    }
}
