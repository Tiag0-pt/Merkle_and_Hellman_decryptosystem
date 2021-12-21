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

int main(void){
    integer_t p[] = {(integer_t)5956ull,
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
      (integer_t)82374ull};
    int n = sizeof(p)/sizeof(integer_t);
    integer_t t = 1 << n ;
    integer_t sums[t];
    make_sums(n,p,sums);
    for(int i = 0;i<t;i++){
        printf("%llu ",sums[i]);
    }
    printf("\n%llu",t);
}