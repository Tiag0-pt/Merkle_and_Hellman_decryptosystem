//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// Place your student numbers and names here
//

#if __STDC_VERSION__ < 199901L
#error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
#define STUDENT_H_FILE "alunos/000000.h"
#endif

//
// include files
//

#include <stdio.h>
#include <stdlib.h>
#include "includes/elapsed_time.h"
#include STUDENT_H_FILE

//
// custom data types
//
// the STUDENT_H_FILE defines the following constants and data types
//
//   #define min_n       24                   --- the smallest n value we will handle
//   #define max_n       57                   --- the largest n value we will handle
//   #define n_sums      20                   --- the number of sums for each n value
//   #define n_problems  (max_n - min_n + 1)  --- the number of n values
//
//   typedef unsigned long long integer_t;    ---  64-bit unsigned integer
//   typedef struct
//   {
//     int n;                                 --- number of elements of the set (for a valid problem, min_n <= n <= max_n)
//     integer_t p[max_n];                    --- the elements of the set, already sorted in increasing order (only the first n elements are used)
//     integer_t sums[n_sums];                --- several sums (problem: for each sum find the corresponding subset)
//   }
//   subset_sum_problem_data_t;               --- weights p[] and sums for a given value of n
//
//   subset_sum_problem_data_t all_subset_sum_problems[n_problems]; --- // the problems
//

//
// place your code here
//
// possible function prototype for a recursive brute-force function:
//   int brute_force(int n,integer_t p[n],integer_t desired_sum,int current_index,integer_t partial_sum,int b[n]);
// it sould return 1 when the solution is found and 0 otherwise
// note, however, that you may get a faster function by reducing the number of function arguments (maybe a single pointer to a struct?)
//

//
// main program
//
int brute_force(int n, integer_t p[n], integer_t desired_sum, int idx, integer_t partial_sum, int b[n])

// verifica valida cada bit dos dados encriptados comforme a soma parcial atá chegar á soma desejada
{
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
  int r=brute_force(n, p, desired_sum, idx + 1, partial_sum /* + p[idx]*b[idx] */, b);
  if (r!=0)
  {
    return r;
  }
  b[idx] = 1;
  r=brute_force(n, p, desired_sum, idx + 1, partial_sum + p[idx] /* + p[idx]*b[idx] */, b)!=0;
  return r;

}

// função auxiliar
double applly_brute_force(int n, integer_t p[n],integer_t  desired_sum)
{
  double t;
  int b[n];
  int i;
  integer_t sum = 0;
  t = cpu_time();
  if (brute_force(n,p,desired_sum,0,sum,b)==0){
    fprintf(stderr,"MERDA\n");

  }
  // verificação
  for (i = 0;i<n; i++){
    if(b[i]==1){
      sum += p[i];
      
    }
    // printf("%d",b[i]);
  }

  if(sum != desired_sum){
      fprintf(stderr,"Merda^2\n");
      exit(1);
    }
   return cpu_time() - t;
}


/* int all_sums_rec(p,n,nivel,partial_sum,desired_sum,mask){
  if(partial_sum== desired_sum){
    return 1;
  }
  else{
    if(all_sums_rec(p,n,nivel+1,partial_sum + p[nivel],desired_sum,(mask << 1)|1)){
      return 1;
    }
    all_sums_rec(p,n,nivel + 1 ),partial_sum,desired_sum,mask << 1 | 0);
  } */
int main(void)
{
  fprintf(stderr, "Program configuration:\n");
  fprintf(stderr, "  min_n ....... %d\n", min_n);
  fprintf(stderr, "  max_n ....... %d\n", max_n);
  fprintf(stderr, "  n_sums ...... %d\n", n_sums);
  fprintf(stderr, "  n_problems .. %d\n", n_problems);
  fprintf(stderr, "  integer_t ... %d bits\n", 8 * (int)sizeof(integer_t));
  //
  // for each n
  //
  int i;
  int j;
  for( i = 0;i < n_problems;i++)
  {
    int n = all_subset_sum_problems[i].n;
     // the value of n
    if(n > max_n)
      break; // skip large values of n
    integer_t *p = all_subset_sum_problems[i].p; // the weights
    //
    // for each sum
    //
    for(j = 0;j < n_sums;j++)
    {
      integer_t desired_sum = all_subset_sum_problems[i].sums[j]; // the desired sum
      double t = applly_brute_force(n,p,desired_sum);
      // printf(" ---> %lf s \n",t); - regular print
      printf("%lf\t",t); // matlab print
    }

    printf("\n"); // matlab print
    

  
}
return 0;
}
