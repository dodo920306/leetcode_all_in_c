#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define NUMBER_OF_FRACTION_BITS 23
#define EXPONENT_BIAS 127
#define MASK_OF_THE_MSB_OF_FRACTION 0x00400000

/**
 * The solution comes from https://hackmd.io/@sysprog/c-floating-point.
 * Please consider referring to that before contributing this file.
 */

/* Translate */
typedef union {
    float value;
    uint32_t v_int;
} ieee_float_shape_type;

/* Get a 32 bit int from a float. */
#define EXTRACT_WORDS(ix0, d)                                                               \
    do {                                                                                    \
        ieee_float_shape_type ew_u;                                                         \
        /* First, store the input as a float */                                             \
        ew_u.value = (d);                                                                   \
        /** 
         * Second, treat the content as a uint and store it back.
         * Since it's a union, there will be no change in the content
         * i.e. both types share the same content (bits).
         */                                                                                 \
        (ix0) = ew_u.v_int;                                                                 \
    } while (0) /**
                 * Pack this as a whole to prevent it from getting impacted by the context 
                 * while being pasted directly since it's a macro.
                 */

bool isPerfectSquare(int n);

bool isPerfectSquare(int n)
{
    /**
     * take care of zero and small numbers
     * flip twice to ensure the output is 0 or 1.
     */
    if (n < 4)   return ((n == 1) || (n == 4));

    int32_t ix0, m;
    uint32_t head, mid, tail, square;

    /* x = (1.(fraction of n))b * 2^(exponent of n). */
    float x = n;
    /**
     * The fastest way to translate the float into uint while not changing the content
     * so that the following bitwise operations are available.
     */
    EXTRACT_WORDS(ix0, x);

    /* normalize x */
    m = (ix0 >> NUMBER_OF_FRACTION_BITS); /* m = 23 0s | sign bit 0 | biased exponent */
    if (!m)
        /**
         * subnormal x
         * In this case, there are no 1 in sign bit and biased exponent bits
         * i.e. n is a denormal originally.
         * Thus, n = (0.fraction)b * 2^(-126).
         * Since, ix0 != 0, fraction != 0x0, so the following loop will be finite.
         * Hence, by finding how many 0 are there in the fraction before the first 1,
         * m can be normalized as (1. ...)b * 2^(-...).
         * There are i 0s in the fraction before the first 1.
         * e.g. fraction = 1... => m = 0.
         *      fraction = 01... => m = -1.
         *      fraction = 001... => m = -2.
         */
        for (; !(ix0 & MASK_OF_THE_MSB_OF_FRACTION); m--)
            ix0 <<= 1;
    /**
     * Here, the true exponent of the normalized m is gotten.
     * e.g. m = 0 => m = -127. so m = (1. ...)b * 2^(-127) (denormal).
     * e.g. m = 1 => m = -126. so m = (1. ...)b * 2^(-126) (norma).
     */
    m -= EXPONENT_BIAS; /* unbias exponent */

    m >>= 1; /* m = ceiling(m / 2) */
    /**
     * What't m now?
     * m is the exponent of sqrt(normalized n) (exponent / 2).
     * Thus, 2 ^ m <= sqrt(n) < 2 ^ (m + 1).
     */
     
    /* Hence, binary searching is used here to find the true floor(sqrt(n)). */
    head = 1 << m;       // 2 ^ m
    tail = 1 << (m + 1);  // 2 ^ (m + 1)
    for (uint32_t i = head; i < tail; i++)
        if (i * i == n)  return true;
    return false;
}

int main()
{
    printf("%s\n", isPerfectSquare(8) ? "true" : "false");
    return 0;
}
