#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long integer_t;

int compare_int(const void *a, const void *b)
{
    return (*(integer_t *)a - *(integer_t *)b);
}

void make_sums(int n,integer_t p[n],integer_t sums[1LL << n]){
    long long int total_sums = 1LL<< n;
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
    integer_t p[] = {
      (integer_t)46410444765ull,
      (integer_t)81036928132ull,
      (integer_t)81366551701ull,
      (integer_t)86397807812ull,
      (integer_t)92985775158ull,
      (integer_t)104137017346ull,
      (integer_t)146189351337ull,
      (integer_t)158136914578ull,
      (integer_t)185321282542ull,
      (integer_t)189092346022ull,
      (integer_t)203741367536ull,
      (integer_t)217410788914ull,
      (integer_t)241308482966ull,
      (integer_t)271438497859ull,
      (integer_t)294968708525ull,
      (integer_t)332090606884ull,
      (integer_t)342937628290ull,
      (integer_t)369315087277ull,
      (integer_t)415906400020ull,
      (integer_t)416548069384ull,
      (integer_t)475075421386ull,
      (integer_t)478028150344ull,
      (integer_t)484089496106ull,
      (integer_t)527482219099ull,
      (integer_t)532716421348ull,
      (integer_t)533684618070ull,
      (integer_t)535504595692ull,
      (integer_t)543526972285ull,
      (integer_t)591322360389ull,
      (integer_t)596895434092ull,
      (integer_t)604879191987ull,
      (integer_t)623263947283ull,
      (integer_t)658279731193ull,
      (integer_t)705071587533ull,
      (integer_t)730242341999ull,
      (integer_t)751801006977ull,
      (integer_t)758969290356ull,
      (integer_t)773032490101ull
    };

    // integer_t p[] = {3,5,11};
    int n = (sizeof(p)/sizeof(integer_t));
    int n1 = n/2;
    int n2 = n-n1;
    long long int t=1LL<<n1;
    integer_t lower[t];
    t=1LL<<n2;
    integer_t upper[t];
    //make_sums(n1,p,lower);
    make_sums(n2,p+n1,upper);
    for(int i = 0;i<t;i++){
        printf("%llu ",upper[i]);
    }
    printf("\n\n%lld",t);
    printf("\n\n%d",n);
    printf("\n\n%lld", sizeof(int));
}