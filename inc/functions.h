
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "functions.h"
#include "elapsed_time.h"
#include "heap.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef unsigned long long integer_t;

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

/*Brute Force*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//


int brute_force_recursive(int n, integer_t p[n], integer_t desired_sum, int idx, integer_t partial_sum, int b[n]){// verifica valida cada bit dos dados encriptados comforme a soma parcial atá chegar á soma desejada
  int i;
  if (partial_sum == desired_sum)
  {
    for (i = idx; i < n; i++)
    {
      b[i] = 0; // mete o resto da chave a zero
    }
    return 1;
  }
  if (idx == n || partial_sum > desired_sum)
  {
    return 0;
  }
  b[idx] = 0;
  int r = brute_force_recursive(n, p, desired_sum, idx + 1, partial_sum /* + p[idx]*b[idx] */, b);
  if (r != 0)
  {
    return r;
  }
  b[idx] = 1;
  r = brute_force_recursive(n, p, desired_sum, idx + 1, partial_sum + p[idx] /* + p[idx]*b[idx] */, b) != 0;
  return r;
}

int brute_force_iterative(int n,integer_t p[n],integer_t desired_sum,int b[n]){
    long long int total_sums = 1LL << n;
    long long int i,j,sum;
    for(i = 0; i<total_sums;i++){
        sum = 0;
        for(j = 0; j<n ;j++){
            if (i & (1LL << j)){

                b[j] = 1;
                sum += p[j]; 
            }
        }

        if(sum == desired_sum){
            return 0;
        }
        memset(b, 0, n*sizeof(int));
    }
    return 1;
}


double applly_brute_force(int n, integer_t p[n], integer_t desired_sum)
{
  double t;
  int b[n];
  int i;
  integer_t sum = 0;
  t = cpu_time();
  if (brute_force_recursive(n, p, desired_sum, 0, sum, b) == 0)
  {
    fprintf(stderr, "MERDA\n");
  }
  // verificação
  for (i = 0; i < n; i++)
  {
    if (b[i] == 1)
    {
      sum += p[i];
    }
    // printf("%d",b[i]);
  }

  if (sum != desired_sum)
  {
    fprintf(stderr, "Merda^2\n");
    exit(1);
  }
  return cpu_time() - t;
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

/* Horowitz and Sahni*/

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

int compare_int(const void *a, const void *b)
{
    if (*(integer_t*)a>*(integer_t*)b) return 1;
    if (*(integer_t*)a<*(integer_t*)b) return -1;
    return 0;
}

void make_sums(int n,integer_t p[n],integer_t *sums){
    integer_t total_sums = 1ULL<< n;
    integer_t i,j,sum;
    for(i = 0; i<total_sums;i++){
        sum = 0;
        for(j = 0; j<n ;j++){
            if (i & (1 << j)){
                sum += p[j]; 
            }
        }

        sums[i] = sum;
    }
    qsort(sums,total_sums,sizeof(integer_t),compare_int);
}


void print_arr(integer_t* arr, integer_t n) {
    for (integer_t i = 0; i < n; i++) {
        printf("%lld ", arr[i]);
    }
}

void hs(int n,integer_t p[n],integer_t desired_sum,int b[n]){

    int n1 = n/2;
    int n2 = n - n1;
    integer_t t=1ULL<<n1;
    integer_t* lower = (integer_t*)malloc(sizeof(integer_t)*t);
    t=1ULL<<n2;
    integer_t* upper = (integer_t*)malloc(sizeof(integer_t)*t);
    integer_t i = 0;
    integer_t j = (1ULL << n2) -1;

    make_sums(n1,p,lower);
    make_sums(n2,p+n1,upper);

    while(1){
         if(upper[j]+lower[i] == desired_sum){
             break;
         } else if (upper[j]+lower[i] < desired_sum)
         {
             i++;
             continue;
         }
         j--;

    }

    brute_force_recursive(n1,p,lower[i],0,0,b);
    brute_force_recursive(n2,p+n1,upper[j],0,0,b+n1);

    free(lower);
    free(upper);
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
        //printf("pair2->%d\n",  upa[ja]);
        add_max(upper_heap, pair);
    }

    pair_sum j;
    pair_sum i; 
    integer_t sum; 


    while(lower_heap->size != 0 && upper_heap->size != 0){
        i = peek(lower_heap);
        j = peek_max(upper_heap);
        sum = i.sum+j.sum;

       /*  printf("sum->%d\n",sum);
        printf("i->%d\n",i.sum);
        printf("j->%d\n",j.sum);
        printf("================\n"); */
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
               /*  printf("here2: %lld\n", j.b-1);
                printf("here3: %lld\n", upb[j.b-1]); */
                pair_sum pair = {j.a, j.b-1, upa[j.a]+upb[j.b-1]};
                add_max(upper_heap, pair);
            }
        }

    }
    if(desired_sum!=sum){
        printf("NOT FOUND!!!!\n");
        return;
    }
    /* printf("v -> %d\n",desired_sum == (j.sum+i.sum));
    //printf("Result -> %lld %lld\n",j.sum,i.sum); */

    brute_force_recursive(n1a,p,lwa[i.a],0,0,b);
    brute_force_recursive(n1b,p+n1a,lwb[i.b],0,0,b+n1a);
    brute_force_recursive(n2a,p+(n1a+n1b),upa[j.a],0,0,b+(n1a+n1b));
    brute_force_recursive(n2a,p+(n1a+n1b+n2a),upb[j.b],0,0,b+(n1a+n1b+n2a));

   /*  for(int k = 0;k<n;k++){
        printf("%d",b[k]);
    }
    printf("\n"); */
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

/*Uteis */

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

void int_to_bin_digit(long long int in, int count, int* out)
{
    unsigned int mask = 1U << (count-1);
    // 100000 ... - cont zeros
    int i;
    for (i = 0; i < count; i++) {
        //100000            //100000
        //101110 &          //011100 
        // = 100000 > 0     // = 000000 = 0
        out[i] = (in & mask) ? 1 : 0; // if (in & mask)!=0 : 1 else 0
        in <<= 1;
    }
}

void put(int n,integer_t *arr,integer_t sum,integer_t idx){
    if(idx<n){
        arr[idx] = sum;
    }
    idx++;
}

void make_sums_recursive(int n, integer_t p[n], integer_t lworup[1 << n], int l ,int r ,integer_t sum, integer_t idx){
    // notas
    // idx tem de ser static, pois se fizer lworup[idx] = sum ao chamar a função com idx+1 dá problemas (ñ faço a minima do que seja)
    // qsort separado
    if(l>r){
        put(1 << n,lworup,sum,idx);
        return;
    }
    make_sums_recursive(n,p,lworup,l+1,r,sum,idx);
    make_sums_recursive(n,p,lworup,l+1,r,sum + p[l],idx);

}





#endif
