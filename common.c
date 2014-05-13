/*******************************************************************************

 Consider the following situtation (where N > 1 is given):

 Two numbers (not necessarily different) are chosen from the range of positive
 integers greater than 1 and not greater than N. Only the sum of the two numbers
 is given to mathematician S. Only the product of the two is given to
 mathematician P.

 On the telephone S says to P, "I see no way you can determine my sum." An hour
 later P calls him back to say, "I know your sum." Later S calls P again to
 report, "Now I know your product."

 This file provide common functions used by other programs that solve the
 problem.

 For a discussion about this problem see
 http://github.com/cassioneri/Impossible

 Copyright (C) 2006-2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "common.h"

void init(char* argv1, int* N, int* p_max, int* s_max, char** product,
  char** sum) {
  
  *N = atoi(argv1);
  if (*N <= 1) {
    fprintf(stderr, "Invalid upper bound.\n");
    exit(1);
  }

  *p_max = *N * *N;
  *s_max = *N + *N;

  if ((*product = malloc(*p_max + 1)) == NULL) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
  
  if ((*sum = malloc(*s_max + 1)) == NULL) {
    free(product);
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }
}

void print_all(char* x, int n) {
  int i;
  for (i = 4;i <= n; ++i)
    if (x[i])
      printf("%4d ",i);
  putchar('\n');
}

int count(char* x, int n, int* last) {
  int i, m = 0;
  *last = 0;
  for (i = 4; i <= n; ++i)
    if (x[i]) {
      ++m;
      *last = i;
    }
  return m;
}

int calc_p_1(char* product, int N, int* last) {

  int i, j;
  int count = 0;
  int p_max = N * N;
  
  *last = 0;
  memset(product, 0, p_max + 1);
  
  for (i = 2; i <= N; ++i)
    for (j = i; j <= N; ++j)
      ++product[i * j];

  for (i = 4; i <= p_max; ++i) {
    product[i] = (product[i] >= 2);
    if (product[i]) {
      ++count;
      *last = i;
    }
  }
  
  return count;
}

int calc_s_1(char* sum, char* product, int N, int* last) {
  
  /***
   *
   * S(1) = { m is a natural number ; 4 <= m <= 2N and for each decomposition
   *                                  (i, j) of m we have ij in P(1)}.
   * 
   *      = { m is a natural number ; 4 <= m <= 2N } -
   *        { m is a natural number ; 4 <= m <= 2N and there exists a
   *                                  decomposition (i, j) of m with ij not in
   *                                  P(1) }.
   * 
   ***/
  
  int i, j;
  int n_s;
  int s_max = N + N;
  
  for (i = 2; i <= N; ++i)
    for (j = i; j <= N; ++j)
      if (!product[i * j])
        sum[i + j] = 0;
      
  n_s = count(sum, s_max, last);
  return n_s;
}

void solve(int p, int s) {
  
  int i, j;
  
  printf("The product is %d and the sum is %d.\n", p, s);

  /***
   * i and j are roots of
   * (x - i)(x - j) = x * x - (i + j) * x + i * j = x * x - s x + p.
   ***/

    i = (int) sqrt((double) (s * s - 4 * p));
    j = i;

    i = (s - i) / 2;
    j = (s + j) / 2;

    printf("The numbers are %d and %d.\n", i, j);
}

int normalize(char* x, int n, int* last) {
  
  int i;
  int count = 0;
  *last = 0;
  
  for (i = 4; i <= n; ++i)
    if (x[i] == 2) {
      x[i] = 1;
      ++count;
      *last = i;
    }
    else
      x[i] = 0;
    
  return count;
}
