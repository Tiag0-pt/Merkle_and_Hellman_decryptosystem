#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long integer_t;

int compare_int(const void *a, const void *b)
{
    return (*(integer_t *)a - *(integer_t *)b);
}

void make_sums(int n,integer_t p[n],integer_t sums[1 << n]){
    long long int total_sums = 1 << n;
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
    qsort(sums,total_sums,sizeof(integer_t),compare_int);
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
        //printf("%llu ,sum"); - dá na prefeição sem put
        //lworup[idx] = sum;
        return;
    }
    
    make_sums_recursive(n,p,lworup,l+1,r,sum,idx/*+1*/);
    make_sums_recursive(n,p,lworup,l+1,r,sum + p[l],idx/*+1*/);
    

}


int main(void){
    /* integer_t p[] = {(integer_t)5956ull,
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
      (integer_t)82374ull}; */

    integer_t p[] = {3,5,11};
    int n = sizeof(p)/sizeof(integer_t);
    integer_t t = 1 << n ;
    integer_t sums[t];
    static integer_t idx = 0;
    make_sums_recursive(n,p,sums,0,0,0,idx);
    for(int i = 0;i<t;i++){
        printf("%llu ",sums[i]);
    }
    printf("\n%llu",t);
}