#include <stdio.h>
#include "../../inc/functions.h"
#include "../../inc/heap.h"


typedef unsigned long long integer_t;

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

    min_heap *lower_heap = Create_min_Heap(1LL<<n1b);
    max_heap *upper_heap = Create_max_heap(1LL<<n2b);

    make_sums(n1a,p,lwa);
    make_sums(n1b,p+n1a,lwb);
    make_sums(n2a,p+(n1a+n1b),upa);
    make_sums(n2b,p+(n1a+n1b+n2a),upb);
    
    printf("size lwa %d \n",(n1a));
    printf("size lwb %d \n",(n1b));
    printf("size upa %d \n",(n2a));
    printf("size upb %d \n",(n2b));

    int ia=0;
    int ib=0;
    int ja=(1<<n2b)-1;
    int jb=(1<<n2b)-1;

    

    for(ib=0;ib<(1LL << n1b);ib++){
        //printf("%lld ",lwa[ia]+lwb[ib]);
        add(lower_heap,(lwa[ia]+lwb[ib]));
    }
    ia++;

    
    for(jb=(1<<n2b)-1;jb>-1;jb--){
        //printf("%lld -> %d ",upa[ja]+upb[jb],jb);
        add_max(upper_heap,upa[ja]+upb[jb]);
    }
    ja--;

    

    int j = poll_max(upper_heap);
    int i = poll(lower_heap);

    integer_t sum = i + j;

    long long int j_idx = (1LL << n2) - 1;
    long long int i_idx = 0;


    
    while(sum != desired_sum){
      printf("%llu\n",sum);
      if(upper_heap->size == 0){
        for(jb=(1<<n2b)-1;jb>-1;jb--){
          add_max(upper_heap,upa[ja]+upb[jb]);
        }
        ja--;
        j = poll_max(upper_heap);
        sum = i+j;
        j_idx--;

        continue;
      }

      if(lower_heap->size == 0){
        for(ib=0;ib<(1LL << n1b);ib++){
          add(lower_heap,(lwa[ia]+lwb[ib]));
        }
        ia++;
        i = poll(lower_heap);
        sum = i + j;
        i_idx ++;
        continue;
      } 

      if(sum <  desired_sum){
        j = poll_max(upper_heap);
        sum = i+j;
        j_idx--;
        continue;
      }
      i = poll(lower_heap);
      sum = i+j;
      i_idx++;
    }
    printf("%d %d",j,i);
}

int main(void){
    /* integer_t p[] ={
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
    }; */

    integer_t p[]  = {1,3,7,11,13,19};

    

   

    int n = sizeof(p)/sizeof(integer_t);

    integer_t k[1LL << n];

    make_sums(n,p,k);

    for(int i = 0;i<(1LL << n);i++){
      printf("%llu ",k[i]);
    }

    integer_t desired_sum = 647299; //p[3] + p[n-1]
    int b[n];

    ss(n,p,desired_sum,b);

}