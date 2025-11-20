#ifndef MODULE_42_H
#define MODULE_42_H

/**
 * @brief A function to get the greatest common divisor (gcd) of two unsigned integers greater than `0`.
 *        Example: the gcd of `8` and `12` is `4`.
 * 
 * @param a Must be greater than `0`
 * @param b Must be greater than `0`
 * @return `0` on fail else gcd of `a` and `b`
 */
unsigned int gcd(unsigned int a, unsigned int b);

/**
 * @brief A function to get the least common multiple(lcm) of two unsigned integers greater than `0`.
 *        Example: the lcm of `4` and `6` is `12`.
 * 
 * @param a Must be greater than `0`
 * @param b Must be greater than `0`
 * @return `0` on fail else lcm of `a` and `b` 
 */
unsigned int lcm(unsigned int a, unsigned int b);

typedef char (*cmp_char_t)(char, char);
/**
 * @brief A function to sort a string in alphabetical order.
 *        Example:
 *          String: jsaNSHosAlPWnSJq
 *          Sorted String: AaHJjlNnoPqSSssW
 * 
 * @param s Pointer to first `char` in a `'\0'` terminated string
 * @param cmp Pointer to compare function
 * @return Negative on fail else `0`
 */
int strsort(char *s, cmp_char_t cmp);

#endif