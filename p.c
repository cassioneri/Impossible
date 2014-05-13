/*******************************************************************************

 Consider the following situtation (where N > 1 is given):

 Two numbers (not necessarily different) are chosen from the range of positive
 integers greater than 1 and not greater than N. Only the sum of the two numbers
 is given to mathematician S. Only the product of the two is given to
 mathematician P.

 On the telephone S says to P, "I see no way you can determine my sum." An hour
 later P calls him back to say, "I know your sum." Later S calls P again to
 report, "Now I know your product."

 This program plays the role of P. Depending on the number given to P, the
 conversation above can be true or false. In the last case the programs stops.
 On the other hand, S will say exactly as stated above and this program will
 believe.

 Compile with:
 gcc -Wall -Wextra -pedantic -o p -O2 p.c common.c -lm

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
#include <math.h>

#include "common.h"

static void finish(int p, int s, char* product, char* sum) {
  printf("P: I know your sum.\n");
  solve(p, s);
  free(product);
  free(sum);
  exit(0);
}

/**
 *
 * @brief Main function.
 *
 */
int main(int argc, char* argv[]) {

  char* product;            /* product[i] = 1 iff i is an admissible product  */
  char* sum;                /* sum[i]     = 1 iff i is an admissible sum      */
  int   N = 0;              /* the upper bound for the numbers                */
  int   i, j;               /* loop indexes                                   */
  int   n_s;                /* counter                                        */
  int   p = 1, s = 1;       /* the product and the sum of the two numbers     */
  int   p_max, s_max;       /* upper bounds for the product and the sum       */
  int   dummy;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s upper-bound product\n", argv[0]);
    return 1;
  }

  init(argv[1], &N, &p_max, &s_max, &product, &sum);
  
  p = atoi(argv[2]);
  
  if (p < 4 || p > p_max) {
    fprintf(stderr, "Invalid product.\n");
    return 1;
  }

  /***
   *
   * S(0) = { m is a natural number ; 4 <= m <= s_max and there exists a
   *                                    decomposition (i, j) of m with p = ij }.
   * 
   ***/
  
  memset(sum, 0, s_max + 1);
  
  for (i = 2; i <= N; ++i)
    for (j = i; j <= N; ++j)
      if (i * j == p)
        sum[i + j] = 1;

  /***
   *
   * P can find the numbers iff #S(0) = 1.
   * 
   ***/

  n_s = count(sum, s_max, &s);
  if (n_s == 1)
    finish(p, s, product, sum);

  /***
   *
   * P(1) = { m is a natural number ; m 4 <= m <= N * N and m has at least two
   *                                  factorizations }
   *
   ***/

  calc_p_1(product, N, &dummy);
  
  if (!product[p]) {
    fprintf(stderr, "Invalid product (prime number).\n");
    return 1;
  }

  /***
   *
   * S(1) = { m in S(0) ; for each decomposition (i, j) of m we have ij in
   *                      P(1) }.
   *
   ***/

  printf("S: I see no way you can determine my sum.\n");

  n_s = calc_s_1(sum, product, N, &s);

  /***
  *
  *  P says "I know your sum." iff #S(1) = 1.
  *
  ***/

  if (n_s == 0)
    printf("P: The problem has no solution.\n");
  
  else if (n_s == 1)
    finish(p, s, product, sum);
  
  else {
    printf("P: Your sum is one of the following numbers:\n");
    print_all(sum, s_max);
  }

  return 0;
}
