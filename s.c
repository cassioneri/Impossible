/*******************************************************************************

 Consider the following situtation (where N > 1 is given):

 Two numbers (not necessarily different) are chosen from the range of positive
 integers greater than 1 and not greater than N. Only the sum of the two numbers
 is given to mathematician S. Only the product of the two is given to
 mathematician P.

 On the telephone S says to P, "I see no way you can determine my sum." An hour
 later P calls him back to say, "I know your sum." Later S calls P again to
 report, "Now I know your product."

 This program plays the role of S. Depending on the number given to S, the
 conversation above can be true or false. In the last case the programs stops.
 On the other hand, P will say exactly as stated above and this program will
 believe.

 Compile with:
 gcc -Wall -Wextra -pedantic -o s -O2 s.c common.c -lm

 For a discussion about this problem see
 http://github.com/cassioneri/Impossible

 Copyright (C) 2006-2014 Cassio Neri.

 This work is licensed under a Creative Commons Attribution-ShareAlike 4.0
 International License. See
 http://creativecommons.org/licenses/by-sa/4.0/

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

/**
 *
 * @brief Main function.
 *
 */
int main(int argc, char* argv[]) {

  char* product;            /* product[i] = 1 iff i is an admissible product  */
  char* sum;                /* sum[i]     = 1 iff i is an admissible sum      */
  int   N = 0;              /* the upper bound for the numbers                */
  int   i, j, k, l;         /* loop indexes                                   */
  int   n_p;                /* counter                                        */
  int   p = 1, s = 1;       /* the product and the sum of the two numbers     */
  int   p_max, s_max;       /* upper bounds for the product and the sum       */
  int   dummy;

  if (argc < 3) {
    fprintf(stderr, "Usage: %s upper-bound sum\n", argv[0]);
    return 1;
  }

  init(argv[1], &N, &p_max, &s_max, &product, &sum);

  s = atoi(argv[2]);
  if (s < 4 || s > s_max) {
    fprintf(stderr, "Invalid sum.\n");
    return 1;
  }

  /***
   *
   * P(0) = { m is a natural number ; 4 <= m <= N * N },
   * S(0) = { m is a natural number ; 4 <= m <= 2N }.
   *
   ***/

  memset(product, 1, p_max + 1);
  memset(sum, 1, s_max + 1);

  /***
   *
   * P(1) = { m in P(0) ; there exists at least two factorizations of m }.
   *
   ***/

  calc_p_1(product, N, &p);

  /***
   *
   * S(1) = { m in S(0) ; for each decomposition (i, j) of m we have ij in
   *                      P(1) }.
   *
   ***/

  calc_s_1(sum, product, N, &dummy);

  if (!sum[s]) {
    printf("S: May be you can determine my sum.\n");
    return 0;
  }

  printf("S: I see no way you can determine my sum.\n");

  /***
   *
   * P(2) = { m in P(1) ; there exists a unique factorization (i, j) of m with
   *                      i + j = s }.
   *
   ***/

  printf("P: I know your sum.\n");

  for (i = 2; i <= (j = s - i); ++i)
    for (k = 2; k <= N; ++k)
      for (l = k; l <= N; ++l)
        if (k * l == i * j && sum[k + l] && product[i * j])
          ++product[i * j];

  n_p = normalize(product, p_max, &p);

  /***
   *
   * S says "Now I know your product" iff #P(2) = 1.
   *
   ****/

  if (n_p != 1) {
    printf("S: Your product is one of the followings numbers:\n");
    print_all(product, p_max);
    return 0;
  }

  printf("S: Now I know your product.\n");
  solve(p, s);

  return 0;
}
