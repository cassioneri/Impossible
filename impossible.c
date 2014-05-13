/*******************************************************************************

 This program try to solve the following problem (where N > 1 is given):

 Two numbers (not necessarily different) are chosen from the range of positive
 integers greater than 1 and not greater than N. Only the sum of the two numbers
 is given to mathematician S. Only the product of the two is given to
 mathematician P.

 On the telephone S says to P, "I see no way you can determine my sum." An hour
 later P calls him back to say, "I know your sum." Later S calls P again to
 report, "Now I know your product."
 What are the two numbers?

 Compile with:
 gcc -Wall -Wextra -pedantic -o impossible -O2 impossible.c common.c -lm

 For a discussion about this problem see
 http://github.com/cassioneri/Impossible

 Copyright (C) 2006-2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/
 
*******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

/**
 * @brief Print up to max(m, 20) indexes of non zero entries of an array.
 * 
 * @param[in] x The array.
 * @param[in] n The array size.
 * @param[in] m Maximum number of indexes to be printed.
 */
static void print(char* x, int n, int m) {

  int i;
  
  if (m < 20) {
    
    if (m == 1)
      printf("  It is: ");
    else  
      printf("  They are: ");
    
    for (i = 4; i <= n && m; ++i)
      if (x[i]) {
        printf("%d ", i);
        --m;
      }
    putchar('\n');
  }
}

/**
 * @brief Compute P(n) given P(n - 1) and S(n - 1).
 * 
 * @param[in|out] product On entry P(n - 1), on exit P(n).
 * @param[in]     sum     S(n).
 * @param[out]    last    The index of the last non zero element of P(n).
 * 
 * @return The number of non-zero entries in P(n).
 */
int calc_p_n(char* product, char* sum, int N, int* last) {
  
  int i, j, count;
  
  for (i = 2; i <= N; ++i)
    for (j = i; j <= N; ++j)
      if (product[i * j] && sum[i + j])
        ++product[i * j];
      
  count = normalize(product, N * N, last);
  
  return count;
}

/**
 * @brief Compute S(n) given S(n - 1) and P(n).
 * 
 * @param[in]     product P(n).
 * @param[in|out] sum     On entry S(n - 1), on exit S(n).
 * @param[out]    last    The index of the last non zero element of S(n).
 * 
 * @return The number of non-zero entries in S(n).
 */
int calc_s_n(char* product, char* sum, int N, int* last) {

  int i, j, count;

  for (i = 2; i <= N; ++i)
    for (j = i; j <= N; ++j)
      if (product[i * j] && sum[i + j])
        ++sum[i + j];
      
  count = normalize(sum, N + N, last);
  
  return count;
}

/**
 *
 * @brief Main function.
 *
 */
int main(int argc, char* argv[]) {
  
  char* product;           /* product[i] = 1 iff i is an admissible product   */
  char* sum;               /* sum[i]     = 1 iff i is an admissible sum       */
  int  N = 0;              /* the upper bound for the numbers                 */
  int  n_p, n_s, n;        /* some counters                                   */
  int  n_p_prev, n_s_prev; /* previous counter values                         */
  int  p = 1, s = 1;       /* the product and the sum of the two numbers      */
  int  p_max, s_max;       /* upper bounds for the product and the sum        */

  if (argc < 2) {
    fprintf(stderr, "Usage: %s upper-bound\n", argv[0]);
    return 1;
  }

  init(argv[1], &N, &p_max, &s_max, &product, &sum);
  
  /***
   *
   * S(0) = { m is a natural number ; 4 <= m <= 2N }.
   *
   ***/
  
  memset(sum, 1, s_max + 1);

  /***
   *
   * P(1) = { m is a natural number ; 4 <= m <= N * N and m has at least two
   *                                  factorizations }
   *
   ***/
  n_p = calc_p_1(product, N, &p);
  printf("  P(1) has %4d element(s).\n", n_p);

  /***
   *
   * S(1) = { m in S(0) ; for each decomposition (i, j) of m we have ij in
   *                      P(1) }.
   *
   ***/

  printf("S: I see no way you can determine my sum.\n");

  n_s = calc_s_1(sum, product, N, &s);
  printf("  S(1) has %4d element(s).\n", n_s);
  print(sum, s_max, n_s);

  /***
   *
   * P(2) = { m in P(1) ; there exist a unique factorization (i, j) of m with
   *                      i + j in S(1) }.
   *
   ***/
  
  printf("P: I know your sum.\n");
  
  n_p = calc_p_n(product, sum, N, &p);
  printf("  P(2) has %4d element(s).\n", n_p);

  /***
   *
   *  S(2) = { m in S(1) ; there exists a unique decomposition (i, j) of m with
   *                       ij in P(2) }.
   *
   ****/

  printf("S: Now I know your product.\n");

  n_s = calc_s_n(product, sum, N, &s);
  printf("  S(2) has %4d element(s).\n", n_s);
  print(sum, s_max, n_s);

  /***
   *
   *  For n = 3, ... , we set
   *
   *  P(n) = { m in P(n-1) ; there exists a unique factorization (i, j) of m
   *                         with i + j in S(n-1)},
   *  S(n) = { m in S(n-1) ; there exists a unique decompostition (i, j) of m
   *                         with ij in P(n)}.
   *
   ***/

  n = 3;

  while (1) {

    n_p_prev = n_p;
    n_s_prev = n_s;

    /***
     *
     * P(n).
     *
     ***/

    if (n_p != 1)
      n_p = calc_p_n(product, sum, N, &p);

    printf("  P(%d) has %4d element(s).\n", n, n_p);

    /***
     *
     *  S(n).
     *
     ***/

    if (n_s != 1)
      n_s = calc_s_n(product, sum, N, &s);

    printf("  S(%d) has %4d element(s).\n", n, n_s);

    /***
     *
     * Verify whether the procces has finsihed...
     *
     ***/

    if (n_p == 1 && n_s == 1) {
      solve(p, s);
      break;
    }
    
    /***
     *
     * ... or has stalled.
     *
     ***/
    
    if (n_p == n_p_prev && n_s == n_s_prev) {
      
      printf("Sorry, the problem is \"literally impossible\".\n");

      printf("Admissible products:\n");
      print_all(product, p_max);

      printf("Admissible sums:\n");
      print_all(sum, s_max);

      break;
    }

    ++n;
  }

  free(sum);
  free(product);
  return 0;
}
