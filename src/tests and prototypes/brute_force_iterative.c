#include <stdio.h>
#include <stdio.h>
#include <string.h>
typedef unsigned long long integer_t;

int brute_force_iterative(int n,integer_t p[n],integer_t desired_sum,int b[n]){
    long long int total_sums = 1 << n;
    long long int i,j,sum;
    for(i = 0; i<total_sums;i++){
        sum = 0;
        for(j = 0; j<n ;j++){
            if (i & (1 << j)){

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

int main(int argc, char *argv[])
{
    
    integer_t sum;
    integer_t p[] = {
      // p[] -- chave publica
      (integer_t)234ull,
      (integer_t)429ull,
      (integer_t)769ull,
      (integer_t)835ull,
      (integer_t)858ull,
      (integer_t)874ull,
      (integer_t)998ull,
      (integer_t)1200ull,
      (integer_t)1592ull,
      (integer_t)1655ull
    };
    int n = sizeof(p) / sizeof(integer_t);
    int b[10];
    memset(b, 0, n*sizeof(int));

     integer_t desired_sums[] = { 
      // (integer_t) C' // mensagem original
      (integer_t)5963ull, // 0111111100
                          // 0111111100
      (integer_t)5105ull, // 0111011100
                          // 0111011100
      (integer_t)4376ull, // 1100100101
                          // 1100100101
      (integer_t)5339ull, // 1111011100
                          // 1111011100
      (integer_t)7840ull, // 1100111111
                          // 1100111111
      (integer_t)4367ull, // 1011010001
                          // 1011010001  
      (integer_t)5161ull, // 1110010101
                          // 1110010101
      (integer_t)4219ull, // 0100001110
                          // 0100001110
      (integer_t)4430ull, // 1101110100
                          // 1101110100
      (integer_t)1432ull, // 1110000000
                          // 1110000000
      (integer_t)7411ull, // 1000111111
                          // 1000111111
      (integer_t)5319ull, // 0110010011
                          // 0110010011
      (integer_t)3120ull, // 0101101000
                          // 0101101000
      (integer_t)8180ull, // 1010111111
                          // 1010111111
      (integer_t)2356ull, // 1101100000
                          // 1101100000
      (integer_t)4533ull, // 1001011010
                          // 1001011010
      (integer_t)6138ull, // 0111100011
                          // 0111100011
      (integer_t)5174ull, // 1001100011
                          // 1001100011
      (integer_t)3930ull, // 0000111100
                          // 0000111100
      (integer_t)769ull // 0010000000
                        // 0010000000
    };
    

    for (int j =0;j<20;j++){
      sum = desired_sums[j];
      brute_force_iterative(n, p, sum, b);
      printf("\nsoma %d\t",j);
      for(int i = 0;i<n;i++){
        printf("%d",b[i]);
      } 
    }
    return 0;

   /*  // comment here
    sum = 7840ull;
    brute_force_iterative(n, p, sum, b);
    printf("\n\n");
    for(int i = 0;i<n;i++){
        printf("%d",b[i]);
    }
    return 0;
    // to here */
}
