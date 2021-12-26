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
#include "../inc/elapsed_time.h"
#include "../inc/functions.h"
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
int main(void)
{
  fprintf(stderr,"Program configuration:\n");
  fprintf(stderr,"  min_n ....... %d\n",min_n);
  fprintf(stderr,"  max_n ....... %d\n",max_n);
  fprintf(stderr,"  n_sums ...... %d\n",n_sums);
  fprintf(stderr,"  n_problems .. %d\n",n_problems);
  fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
  //
  // for each n
  //
  double t;
  for(int i = 0;i < n_problems;i++)
  {
    int n = all_subset_sum_problems[i].n; // the value of n
    if(n > max_n)
      continue; // skip large values of n
    integer_t *p = all_subset_sum_problems[i].p; // the weights
    //
    // for each sum
    //
    printf("Linha %d\n",n);
    for(int j = 1;j < n_sums;j++)
    {
      integer_t desired_sum = all_subset_sum_problems[i].sums[j]; // the desired sum
      int b[n]; // array to record the solution
      //brute_force_iterative(n,p,desired_sum,b);
      t = cpu_time();
      hs(n,p,desired_sum,b);
      printf("%f ",cpu_time()-t);
      
    }
    printf("\n");
  
  }
  return 0;
}
