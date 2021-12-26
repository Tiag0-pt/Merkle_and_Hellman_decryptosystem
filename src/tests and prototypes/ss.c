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
void ss(int n, integer_t p[n],integer_t b[n],integer_t desired_sum){

    int n1 = n/2;
    int n1a = n1/2;
    int n1b = n1 - n1a;
    
    int n2 = n - n1;
    int n2a = n2/2;
    int n2b = n2 - n2a;

    integer_t lwa[1 << n1a];
    integer_t lwb[1 << n1b];
    integer_t upa[1 << n2a];
    integer_t upb[1 << n2b];

    make_sums(n1a,p,lwa);
    make_sums(n1b,p+n1a,lwb);
    make_sums(n2a,p+(n1a+n1b),upa);
    make_sums(n2b,p+(n1a+n1b+n2a),upb);

    integer_t ia,ib,ja,jb;

    // Notas
    /* esta é a parte inicial que o stor me explicou apartir daqui temos que gerar 
    com uma min-heap o lw[i] e com o max-heap o upper[j]
    - min-heap já está implementado no includes
    */


}