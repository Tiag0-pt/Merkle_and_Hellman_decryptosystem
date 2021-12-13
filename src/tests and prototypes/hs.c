#include <stdio.h>
#include <stdlib.h>
#include "../../inc/elapsed_time.h"

typedef unsigned long long integer_t;

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

/*FUNÇÕES AUXILIARES */

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

int compare_int(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int brute_force(int n, integer_t p[n], integer_t desired_sum, int idx, integer_t partial_sum, int b[n]){// verifica valida cada bit dos dados encriptados comforme a soma parcial atá chegar á soma desejada
  int i;
  if (partial_sum == desired_sum)
  {
    for (i = idx; i < n; i++)
    {
      b[i] = 0; // mete o resto da chave a zero
    }
    return 1;
  }
  if (idx == n)
  {
    return 0;
  }
  b[idx] = 0;
  int r = brute_force(n, p, desired_sum, idx + 1, partial_sum /* + p[idx]*b[idx] */, b);
  if (r != 0)
  {
    return r;
  }
  b[idx] = 1;
  r = brute_force(n, p, desired_sum, idx + 1, partial_sum + p[idx] /* + p[idx]*b[idx] */, b) != 0;
  return r;
}

double applly_brute_force(int n, integer_t p[n], integer_t desired_sum)
{
  double t;
  int b[n];
  int i;
  integer_t sum = 0;
  t = cpu_time();
  if (brute_force(n, p, desired_sum, 0, sum, b) == 0)
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

/* The Real Deal */

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//
int hs(int n, integer_t p[n], integer_t desired_sum, int b[n])
{
    int impar = (n % 2) == 0;
    integer_t upper[1 << (n / 2 + impar)];
    long long int total_sums = 1 << (n / 2);
    long long int i, j, sum_upper, sum_lower;
    integer_t lower[total_sums];

    // lower array

    for (i = 0; i < total_sums; i++)
    {
        sum_lower = 0;
        for (int j = 0; j < (n / 2); j++)
        {
            if ((i & (1 << j)) != 0)
            {
                //Vamos considerar i como um numero binário ex:10010101 e j o index do lower ou upper array
                //O que faremos com a próxima expressão é aplicar uma mascara de bits assim como no int_to_bin_digit,  j and i se for
                // 1 sumamos p[j] senão continuamos,com este algoritmo cada ciclo de i obtemos uma subsoma.
                // exemplo n=4 então totalsums é 4.
                // i = 1    ==     0001   i = 1    ==     0001   i = 1    ==     0001   i = 1    ==     0001
                // j = 0 := 1<<j = 0001 & j = 1 := 1<<j = 0010 & j = 2 := 1<<j = 0100 & j = 2 := 1<<j = 1000 &
                // res     ==      0001   res     ==      0000   res     ==      0000   res     ==      0000
                //
                sum_lower += p[j];
            }
        }
        // to implement
        // if (sum  = desired_sum) b = int_to_bin(i),0 || b = 0,int_to_bin(i) break;
        lower[i] = sum_lower;
    }
    qsort(lower, total_sums, sizeof(integer_t), compare_int);

    // Upper array

    if (!impar)
    {
        for (i = 0; i < total_sums; i++)
        {
            sum_upper = 0;
            for (j = 0; j < (n / 2); j++)
            {
                if ((i & (1 << j)) != 0)
                {

                    sum_upper += p[j + (n / 2)];
                }
            }

            // to implement
            // if (sum  = desired_sum) b = int_to_bin(i),0 || b = 0,int_to_bin(i) break;
            upper[i] = sum_upper;
          
    }
    }else
    {
        total_sums <<= impar;
        for (i = 0; i < total_sums; i++)
        {
            sum_upper = 0;
            for (j = 0; j < (n / 2) + 1; j++)
            {
                if ((i & (1 << j)) != 0)
                {
                    sum_upper += p[j + (n / 2)];
                }
            }
            // to implement
            // if (sum  = desired_sum) b = int_to_bin(i),0 || b = 0,int_to_bin(i) break;
            upper[i] = sum_upper;
        }
    }

    qsort(upper, total_sums, sizeof(integer_t), compare_int);
    i = 0;
    j = total_sums-1;


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
    brute_force(n,p,lower[i],0,0,b);
    brute_force(n,p+(n/2),upper[j],0,0,b+(n/2));
    return 0;

    // debuging notes
    /* long long int + int : ok
       unsigned long long + int : ok
       long long int + unsigned long long */
}

int main(int argc, char *argv[])
{
    integer_t p[] = {1, 3, 5, 7, 11, 13, 29, 31,46};
    int n = sizeof(p) / sizeof(integer_t);
    integer_t sum = 14;
    // 1 + 13
    int b[n];
    hs(n, p, sum, b);
    return 0;
}
