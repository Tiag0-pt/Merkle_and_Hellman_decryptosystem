
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include "functions.h"


typedef unsigned long long integer_t;

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

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

int hs(int n, int p[n], int desired_sum, int b[n])
{
    int compare_int(const void *a, const void *b)
    {return (*(int *)a - *(int *)b);}

    int impar = 0; // 1 - even ; 0 - uneven
    if (n % 2 != 0)
    {
        impar = 1;
    }
    int upper[1 << (n / 2 + impar)];
    int total_sums = 1 << (n / 2);
    int i, j, sum_upper, sum_lower;
    int lower[total_sums];

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
    qsort(lower, total_sums, sizeof(int), compare_int);

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
    }else{
        total_sums <<= 1;
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

    qsort(upper, total_sums, sizeof(int), compare_int);
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
    return 0;
}


// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

/*FUNÇÕES AUXILIARES */

// --------------------------------------------------------------------------------------------------------------------------------------------------------------//

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

 void int_to_bin_digit(unsigned int in, int count, int* out)
{
    unsigned int mask = 1U << (count-1);
    // 100000 ... - cont zeros
    int i;
    for (i = 0; i < count; i++) {
        //100000            //100000
        //101110 &          //011100
        // = 100000 = 2^6     // = 000000 = 0
        out[i] = (in & mask) ? 1 : 0; // if (in & mask)!=0 : 1 else 0
        in <<= 1;
    }
}

 int compare_int(const void *a, const void *b)
    {return (*(int *)a - *(int *)b);}



#endif