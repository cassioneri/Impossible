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

#ifndef COMMON_H_
#define COMMON_H_

/**
 * @brief Initialize several variables and allocated memory.
 * 
 * @param[in]  argv1   argv[1] as given to main.
 * @param[out] N       The upper bound.
 * @param[out] p_max   The upper bound for the product (N * N).
 * @param[out] s_max   The upper bound for the sum (N + N).
 * @param[out] product A poiter to a dynamically allocated array of chars
 *                     representing the set of admissible products. Must be
 *                     freed after usage.
 * @param[out] sum     A poiter to a dynamically allocated array of chars
 *                     representing the set of admissible sums. Must be freed
 *                     after usage.
 */

void init(char* argv1, int* N, int* p_max, int* s_max, char** product,
  char** sum);

/**
 * @brief Print the indexes of all non zero elemets of an array.
 * 
 * @param[in] x The array.
 * @param[in] n The array size.
 */
void print_all(char* x, int n);

/**
 * @brief Count number of non zeros in an array.
 * 
 * @param[in]  x    The array.
 * @param[in]  n    The array size.
 * @param[out] last The index of the last non zero element of x.
 *
 * @return The number of non zeros in the array.
 ***/
int count(char* x, int n, int* last);

/**
 * @brief Compute P(1).
 *
 * P(1) = { m is a natural number ; 4 <= m <= N * N and m has at least two
 *                                  factorizations }.
 * 
 * @param[out] product P(1).
 * @param[in]  N       Defines the bound.
 * @param[out] last    The index of the last non zero element of product.
 */
int calc_p_1(char* product, int N, int* last);

/**
 * @brief Compute S(1).
 *
 * S(1) = { m in S(0) ; for each decomposition (i, j) of m we have ij in P(1) }.
 * 
 * @param[in|out] sum     On entry S(0) on exit S(1).
 * @param[in]     product P(1).
 * @param[in]     N       Defines the bound.
 * @param[out]    last    The index of the last non zero element of sum.
 */
int calc_s_1(char* sum, char* product, int N, int* last);

/**
 * @brief Find and print the two numbers with a given product and sum.
 * 
 * @param[in] p The product.
 * @param[in] s The sum.
 */
void solve(int p, int s);

/**
 * @brief Normalize an array, count the number of non zeros and the get the last
 *        index with a non-zero element.
 * 
 * Each element whose value is 2 is changed to 1.
 * 
 * @param[in]  x    The array.
 * @param[in]  n    The array size.
 * @param[out] last The index of the last non zero element.
 * 
 * @return The number of non-zero entries.
 */
int normalize(char* x, int n, int* last);

#endif /* COMMON_H_ */
